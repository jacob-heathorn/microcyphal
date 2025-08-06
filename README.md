# microcyphal

A lightweight Cyphal/UDP stack for embedded systems.

This repository implements a lightweight Cyphal/UDP stack for embedded systems, following the [Cyphal Specification](https://opencyphal.org/specification). Cyphal is an open communication protocol designed for aerospace and robotic applications.


# Setup Instructions

1) Clone this repository: `git clone https://github.com/jacob-heathorn/forge.git`
2) Install direnv:
  * `sudo apt install direnv`
  * Add the following to your .bashrc: `eval "$(direnv hook bash)"`
  * Open a new terminal and change directory to here.
  * `direnv allow .`
3) Install nix:
  * `sh <(curl -L https://nixos.org/nix/install) --daemon`
4) Install the workspace recommended VSCode extensions.
5) Create the dev environment: `nox -s dev`

# Repository tests
`nox`

# Clean
`rip -c`

# Build
`cmake --workflow --preset native-debug`
`cmake --workflow --preset native-release`

# Run
`rip -r native-debug:hello-world`

# Debug
`rip -d native-debug:hello-world`

# ctest
```
cd /.bin/native-release/
ctest
```

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
export UAVCAN__UDP__IFACE="192.2.2.2"
export UAVCAN__NODE__ID=42
```

# Run hello-world with yakut and wireshark

```bash
# See previous section for setup.

# Monitor all Cyphal/UDP traffic
yakut mon

cmake --workflow --preset cm4-debug && cmake --workflow --preset cm7-debug && \
rip -d0 cm7-debug:hello-cyphal && \
rip -f0 cm7-debug:hello-cyphal -s

# Or subscribe specifically to heartbeat messages
export UAVCAN__UDP__IFACE=192.2.2.100
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