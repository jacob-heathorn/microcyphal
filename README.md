# microcyphal
A lightweight modular cyphal stack targeting deeply embedded systems

# Clean
`rip -c`

# Build
`cmake --workflow --preset native-debug`
`cmake --workflow --preset native-release`

# Run
`rip -r native-debug:hello-world`

# Debug
`rip -d native-debug:hello-world`

# Hello cyphal
```
cmake --workflow --preset native-debug && \
rip -r native-debug:hello-world
```

subscribe in yakut: `y sub +M 2001:uavcan.node.Health`
yakut monitor: `y mon`

# ctest
```
cd /.bin/native-release/
ctest
```
