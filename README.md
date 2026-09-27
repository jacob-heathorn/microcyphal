# microcyphal

A lightweight Cyphal/UDP stack for embedded systems.

This repository implements a lightweight Cyphal/UDP stack for embedded systems, following the [Cyphal Specification](https://opencyphal.org/specification). Cyphal is an open communication protocol designed for aerospace and robotic applications.

See https://github.com/jacob-heathorn/mimxrt1170evk for a demo on the NXP MIMXRT1170-EVK

# Setup Instructions
This has only been tested in Ubuntu 24.04.

1) Clone this repository: `git clone https://github.com/jacob-heathorn/microcyphal.git`
2) Install bazelisk: `npm i -g @bazel/bazelisk` (or `apt install bazelisk`).
   It fetches the bazel version pinned in `.bazelversion`.
3) Install gordion: `pipx install gordion`
4) Materialize the gordion dependencies: `gor -u`

# Test
`bazel test //...`

# Build
`bazel build //...`

# DSDL types
`//firmware:uavcan` generates C++ types for the `uavcan` namespace of the pinned
`public_regulated_data_types` with nunavut, as a build action. Add another
namespace with `dsdl_cc_library` from `bazel/dsdl.bzl`.

# Dependencies
forge is managed by gordion: `gordion.yaml` pins it, `gor -u` checks it out, and `tools/bazel`
points bazel at that checkout on every command. public_regulated_data_types is an archive bazel
fetches itself, pinned in `MODULE.bazel`; nunavut and pydsdl come from PyPI via
`bazel/requirements.txt`.

# Setup cyphal tools and wireshark
```bash
sudo apt update
sudo apt install wireshark

# Copy lua script 
# from: https://github.com/OpenCyphal/wireshark_plugins/tree/main
# to: /usr/lib/x86_64-linux-gnu/wireshark/plugins

# Instal yakut
pipx install 'yakut[transport-udp]'

# Add to .bashrc
export CYPHAL_PATH="$HOME/path/to/public_regulated_data_types:$CYPHAL_PATH"
export UAVCAN__UDP__IFACE="192.0.2.2"
export UAVCAN__NODE__ID=42
```

# Cyphal pub/sub

```bash
# See previous section for setup.

# Monitor all Cyphal/UDP traffic
yakut mon

# Run publisher
bazel run //test/native:hello-publisher

# Run subscriber
bazel run //test/native:hello-subscriber

# Or subscribe specifically to heartbeat messages
export UAVCAN__UDP__IFACE=192.0.2.100
export UAVCAN__NODE__ID=1000
yakut sub uavcan.node.heartbeat
```

## Coding Style Guidance

This project follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with these specific modifications:

### Naming Conventions
- **Method names**: Use lowerCamelCase (e.g., `publishMessage()`, `getNodeId()`)
- **Regular/standalone functions**: Use UpperCamelCase (e.g., `WriteU16LE()`, `ReadU32BE()`)
- **Member variables**: Use snake_case (e.g., `node_id_`, `transfer_count_`)
- **Accessors/mutators**: May be named like variables
  - Example: `int count()` and `void set_count(int count)`
- **Indenting**: 2 spaces

### Comments
- Use `//` for single-line comments instead of `/* */` style comments
- Follow Google style guide recommendations for documentation comments

## References

- [Cyphal Specification](https://opencyphal.org/specification) - The official protocol specification this implementation follows
- [OpenCyphal Forum](https://forum.opencyphal.org/) - Community discussions and support
- [DSDL Reference](https://github.com/OpenCyphal/public_regulated_data_types) - Standard data type definitions

# Copyright & Licensing

Copyright (c) 2025 Jacob Heathorn

This project is released under the **Academic Use License** (see [LICENSE](./LICENSE)).
For **commercial licensing**, please contact: <jacob.heathorn@gmail.com>.