#include <iostream>

#include "cyphal/udp_frame.hpp"

int main() {
  std::cout << "Hello World!" << std::endl;

  // Create an allocator for the data frame
  static constexpr size_t POOL_MEMORY_SIZE = 16 * 1024;
  uint8_t* buffer = new uint8_t[POOL_MEMORY_SIZE];
  ftl::BumpAllocator allocator(buffer, POOL_MEMORY_SIZE);

  // Initialize data frame class with the memory allocator.
  ftl::DataFrame::initialize(allocator);

  cyphal::UdpFrame f(2);

  std::cout << "version: " << (uint32_t)f.version() << std::endl;
}
