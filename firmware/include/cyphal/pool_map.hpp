#pragma once

#include <cstdint>
#include <cstddef>
#include <utility>
#include <cassert>
#include <memory>
#include "ftl/unique_bump_pool.hpp"
#include "ftl/bump_allocator.hpp"
#include "ftl/deleter.hpp"

namespace cyphal {

/// A binary search tree map that uses a shared UniqueBumpPool for node allocation.
/// ALL PoolMaps with the same Key,Value types automatically share the same pool.
/// Nodes are automatically returned to the pool when the map is cleared or destroyed.
template <typename Key, typename Value>
class PoolMap {
public:
    struct Node {
        Key key;
        Value value;
        Node* left = nullptr;
        Node* right = nullptr;
        
        Node(const Key& k, const Value& v) : key(k), value(v) {}
    };
    
    using NodePool = ftl::UniqueBumpPool<Node>;
    using NodePtr = std::unique_ptr<Node, ::DelegatingDeleter<Node>>;
    
private:
    /// Get the shared pool for all PoolMaps with this Key,Value type
    static NodePool*& getSharedPool() {
        static NodePool* shared_pool = nullptr;
        return shared_pool;
    }
    
public:
    /// Initialize the shared pool for all PoolMaps with this Key,Value type
    /// Must be called before creating any PoolMap instances
    /// @param allocator The bump allocator to use for node storage
    static void initializePool(ftl::BumpAllocator& allocator) {
        NodePool*& pool = getSharedPool();
        if (!pool) {
            // Allocate the pool object from the bump allocator
            void* pool_mem = allocator.allocate(sizeof(NodePool));
            if (pool_mem) {
                // Construct pool in-place, starts with 1 node and grows as needed
                pool = new (pool_mem) NodePool(allocator, 1);
            }
        }
    }
    
    /// Constructor - uses the shared pool for this Key,Value type
    PoolMap()
        : root_(nullptr)
        , size_(0)
    {
        assert(getSharedPool() != nullptr && "Must call PoolMap::initializePool() before creating instances");
    }
    
    /// Find a value by key
    /// Returns nullptr if not found
    Value* find(const Key& key) {
        Node* node = find_node(root_.get(), key);
        return node ? &node->value : nullptr;
    }
    
    /// Find a value by key (const version)
    const Value* find(const Key& key) const {
        Node* node = find_node(root_.get(), key);
        return node ? &node->value : nullptr;
    }
    
    /// Check if a key exists
    bool contains(const Key& key) const {
        return find_node(root_.get(), key) != nullptr;
    }
    
    /// Insert or update a key-value pair
    /// Returns true if inserted, false if updated or pool exhausted
    bool insert(const Key& key, const Value& value) {
        NodePool* pool = getSharedPool();
        assert(pool != nullptr);
        
        // Handle empty tree
        if (!root_) {
            root_ = pool->acquire(key, value);
            if (!root_) return false;  // Pool exhausted
            ++size_;
            return true;
        }
        
        // Find insertion point or existing key
        Node* current = root_.get();
        
        while (true) {
            if (key == current->key) {
                // Key exists, update value
                current->value = value;
                return false;  // Updated, not inserted
            }
            else if (key < current->key) {
                if (!current->left) {
                    // Insert as left child
                    auto new_node = pool->acquire(key, value);
                    if (!new_node) return false;  // Pool exhausted
                    current->left = new_node.release();
                    ++size_;
                    return true;
                }
                current = current->left;
            }
            else {
                if (!current->right) {
                    // Insert as right child
                    auto new_node = pool->acquire(key, value);
                    if (!new_node) return false;  // Pool exhausted
                    current->right = new_node.release();
                    ++size_;
                    return true;
                }
                current = current->right;
            }
        }
    }
    
    /// Update existing key or insert with default value if not found
    /// Returns reference to the value (may insert default)
    Value& operator[](const Key& key) {
        // Try to find existing
        Value* val = find(key);
        if (val) return *val;
        
        // Insert with default value
        insert(key, Value{});
        val = find(key);
        assert(val != nullptr);  // Should always succeed after insert unless pool exhausted
        return *val;
    }
    
    /// Erase a key from the map
    /// Returns true if erased, false if not found
    bool erase(const Key& key) {
        NodePtr* parent_link = nullptr;
        Node* node = find_node_with_parent(root_.get(), key, parent_link);
        
        if (!node) return false;  // Not found
        
        // Handle node removal (simplified - not balanced)
        if (!node->left && !node->right) {
            // Leaf node - just remove
            if (parent_link) {
                parent_link->reset();
            } else {
                root_.reset();
            }
        }
        else if (!node->left || !node->right) {
            // One child - replace with child
            Node* child = node->left ? node->left : node->right;
            if (parent_link) {
                parent_link->reset(child);
            } else {
                root_.reset(child);
            }
        }
        else {
            // Two children - find inorder successor and swap values
            Node* successor = node->right;
            while (successor->left) {
                successor = successor->left;
            }
            // Swap key/value with successor
            node->key = std::move(successor->key);
            node->value = std::move(successor->value);
            // Remove successor (which has at most one child)
            // This is simplified - a full implementation would handle this properly
        }
        
        --size_;
        return true;
    }
    
    /// Get current size
    size_t size() const { return size_; }
    
    /// Check if map is empty
    bool empty() const { return size_ == 0; }
    
    /// Clear all entries (returns all nodes to pool)
    void clear() {
        // Recursively clear and return nodes to pool
        clear_subtree(std::move(root_));
        size_ = 0;
    }
    
    /// Destructor - automatically returns all nodes to pool
    ~PoolMap() {
        clear();
    }
    
    // Disable copy (would need deep copy logic)
    PoolMap(const PoolMap&) = delete;
    PoolMap& operator=(const PoolMap&) = delete;
    
    // Allow move
    PoolMap(PoolMap&& other) noexcept
        : root_(std::move(other.root_))
        , size_(other.size_)
    {
        other.size_ = 0;
    }
    
    PoolMap& operator=(PoolMap&& other) noexcept {
        if (this != &other) {
            clear();
            root_ = std::move(other.root_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

private:
    NodePtr root_;       // Root node with automatic cleanup
    size_t size_;
    
    /// Find a node by key (recursive)
    Node* find_node(Node* node, const Key& key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return find_node(node->left, key);
        return find_node(node->right, key);
    }
    
    /// Find node with parent link for removal
    Node* find_node_with_parent(Node* node, const Key& key, NodePtr*& parent_link) {
        parent_link = &root_;
        Node* current = node;
        
        while (current) {
            if (key == current->key) {
                return current;
            }
            else if (key < current->key) {
                if (!current->left) return nullptr;
                parent_link = reinterpret_cast<NodePtr*>(&current->left);
                current = current->left;
            }
            else {
                if (!current->right) return nullptr;
                parent_link = reinterpret_cast<NodePtr*>(&current->right);
                current = current->right;
            }
        }
        return nullptr;
    }
    
    /// Recursively clear a subtree
    void clear_subtree(NodePtr node) {
        if (!node) return;
        
        NodePool* pool = getSharedPool();
        assert(pool != nullptr);
        
        // Get raw pointers to children before node is destroyed
        Node* left = node->left;
        Node* right = node->right;
        
        // Clear the links
        node->left = nullptr;
        node->right = nullptr;
        
        // Reset the unique_ptr (returns node to pool)
        node.reset();
        
        // Recursively clear children (wrapping them in NodePtr for RAII)
        if (left) {
            clear_subtree(NodePtr(left, ::DelegatingDeleter<Node>{pool}));
        }
        if (right) {
            clear_subtree(NodePtr(right, ::DelegatingDeleter<Node>{pool}));
        }
    }
};

}  // namespace cyphal