# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

- **Clean**: `rip -c` - Removes the .bin build folder
- **Build Debug**: `cmake --workflow --preset native-debug`
- **Build Release**: `cmake --workflow --preset native-release` 
- **Run Application**: `rip -r native-debug:hello-world`
- **Debug Application**: `rip -d native-debug:hello-world`
- **Quick Build & Run**: `cmake --workflow --preset native-debug && rip -r native-debug:hello-world`

## Testing

- **Run Tests**: `cd .bin/native-release/ && ctest`

## Architecture Overview

This is a lightweight Cyphal/UDP stack for embedded systems with the following key components:

### Core Architecture
- **Publisher Pattern**: `cyphal::UdpPublisher<MessageT>` template class handles Cyphal message publishing
- **Frame Handling**: `cyphal::UdpFrame` manages UDP frame construction with proper Cyphal headers and CRCs
- **Socket Abstraction**: Uses `ftl` library for cross-platform UDP socket operations
- **Memory Management**: Uses bump allocator pattern for embedded-friendly memory allocation

### Message System
- Auto-generated UAVCAN message types from DSDL definitions in `firmware/include/cpp14/` and `cpp17/`
- Messages follow the pattern `uavcan::node::MessageType_X_Y` (e.g., `Heartbeat_1_0`, `Health_1_0`)
- Serialization handled by nunavut support library

### Key Implementation Details
- Single-frame transfers only (no multi-frame support yet)
- UDP multicast addressing: `239.0.(subject_id >> 8).(subject_id & 0xFF):9382`
- CRC validation for both headers (CRC-16-CCITT) and payloads (CRC-32C)
- Transfer IDs auto-increment per publisher instance

### Project Structure
- `firmware/` - Core Cyphal implementation and generated message types
- `test/native/` - Native platform tests and examples
- `scripts/` - Build tooling (rip.py) and packaging
- `cmake/` - Build configuration that defers to external Forge framework

## Development Notes

- The project depends on an external "Forge" framework (defined in gordion.yaml)
- Build system uses CMake presets that include configurations from `$FORGE_ROOT`
- Current error handling uses basic `std::cout`/`std::cerr` - no structured logging framework
- Memory allocation uses `ftl::BumpAllocator` for embedded compatibility
- All C++ code targets C++17 standard with extensions disabled for portability