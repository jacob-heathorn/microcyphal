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

- **Build & Run Tests**: `cmake --workflow --preset native-debug && cd .bin/native-debug && ctest --verbose`
- **Run Tests Only**: `cd .bin/native-debug && ctest --verbose`
- **Run Failed Tests**: `cd .bin/native-debug && ctest --rerun-failed --output-on-failure`
- **Run Specific Test**: `cd .bin/native-debug && ctest -R ut-cyphal --verbose`

## Architecture Overview

This is a lightweight Cyphal/UDP stack for embedded systems with the following key components:

### Core Architecture
- **Publisher Pattern**: `cyphal::UdpPublisher<MessageT>` template class handles Cyphal message publishing
- **Frame Handling**: `cyphal::UdpFrame` manages UDP frame construction with proper Cyphal headers and CRCs
- **Socket Abstraction**: Uses `ftl` library for cross-platform UDP socket operations
- **Memory Management**: Uses bump allocator pattern for embedded-friendly memory allocation

### Message System
- Auto-generated UAVCAN message types from DSDL definitions using Nunavut
- Generated types are placed in `.bin/<preset>/generated/cpp<standard>/` (e.g., `.bin/native-debug/generated/cpp17/`)
- Messages follow the pattern `uavcan::node::MessageType_X_Y` (e.g., `Heartbeat_1_0`, `Health_1_0`)
- Serialization handled by nunavut support library
- Uses environment variables from .envrc: `NUNAVUT_ROOT`, `PYDSDL_ROOT`, `PUBLIC_REGULATED_DATA_TYPES_ROOT`

### Key Implementation Details
- Single-frame transfers only (no multi-frame support yet)
- UDP multicast addressing: `239.0.(subject_id >> 8).(subject_id & 0xFF):9382`
- CRC validation for both headers (CRC-16-CCITT) and payloads (CRC-32C)
- Transfer IDs auto-increment per publisher instance

### Project Structure
- `firmware/` - Core Cyphal implementation
- `test/native/` - Native platform tests and examples
- `scripts/` - Build tooling (rip.py) and packaging
- `cmake/` - Build configuration including:
  - `utilities.cmake` - Provides `add_microcyphal_library()` function for DSDL code generation
  - Platform-specific configurations that defer to external Forge framework

## Development Notes

- The project depends on external repositories managed by gordion (defined in gordion.yaml):
  - Forge framework for build infrastructure
  - Nunavut for DSDL code generation
  - PyDSDL for DSDL parsing
  - OpenCyphal public_regulated_data_types for standard message definitions
- Build system uses CMake presets that include configurations from `$FORGE_ROOT`
- DSDL code generation is handled by `add_microcyphal_library()` function which:
  - Automatically finds all `.dsdl` files in the specified namespace
  - Generates C++ code matching the project's C++ standard
  - Creates CMake targets for linking
- Current error handling uses basic `std::cout`/`std::cerr` - no structured logging framework
- Memory allocation uses `ftl::BumpAllocator` for embedded compatibility
- All C++ code targets C++17 standard with extensions disabled for portability