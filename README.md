# microcyphal

A lightweight, header-only [Cyphal/UDP](https://opencyphal.org/specification) stack for embedded
systems. See [mimxrt1170evk](https://github.com/jacob-heathorn/mimxrt1170evk) for a demo on the NXP
MIMXRT1170-EVK.

## Setup

Tested on Ubuntu 24.04.

1. Install bazelisk (`npm i -g @bazel/bazelisk`) and gordion (`pipx install gordion`).
2. Run `gor -u` to check out forge.

## Test

```
bazel test //...
```

## Run a demo

Give the host's ethernet interface `192.168.144.50/24`, then:

```
bazel run //apps:hello_publisher      # send heartbeats
bazel run //apps:hello_subscriber     # print the heartbeats received
```

## Debug and release

Add `-c dbg` or `-c opt` to any command for a debug or release build:

```
bazel test -c opt //...
```

## License

Copyright (c) 2025 Jacob Heathorn. Released under the **Academic Use License**, see
[LICENSE](./LICENSE). For commercial licensing contact <jacob.heathorn@gmail.com>.
