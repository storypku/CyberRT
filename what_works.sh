#!/usr/bin/env bash
set -e

source setup.bash

bazel build //cyber/...
bazel test //cyber/...
bazel build //cyber_py3/...
bazel test $(bazel query //cyber_py3/... except //cyber_py3/test:parameter_test except //cyber_py3/test:cyber_timer_test)
bazel build //examples/...

#
# bazel run //examples/cyber:talker
# bazel run //examples/cyber:listener
# bazel run //examples/cyber:record
# bazel run //examples/cyber:parameter
# bazel run //examples/cyber:service
# cyber_launch start examples/cyber/common_component_example/common.launch
# cyber_launch start examples/cyber/timer_component_example/timer.launch
# bazel run examples/cyber_py3:time
# bazel run examples/cyber_py3:listener
# bazel run examples/cyber_py3:talker
# bazel run //examples/cyber_py3:record
# bazel run //examples/cyber_py3:record_channel_info -- /tmp/test_writer.record
# bazel run //cyber/python/cyber_py3/examples:record_trans -- /tmp/test_writer.record
#
## TODOs, or Road Map of CyberRT
# Stage 1:
# 1. bazel run //examples/cyber_py3:service
# 2. bazel run //examples/cyber_py3:client
# 3. bazel run //examples/cyber_py3:timer # coredump
# 4. bazel run //examples/cyber_py3:parameter # can't terminate
# 5. bazel test //cyber_py3/test:parameter_test # timeout forever
# 6. bazel test //cyber_py3/test:cyber_timer_test # timeout forever
# 7. external projects depending on CyberRT
## Stage 2:
# 1. CyberRT release build
## Stage 3:
# 1. ROS 1/2 Inter-Op
# 2. pybind11 version of cyber_py3
# 3. cyber_visualizer
## Other TODOs:
# 1. Reorg tutorials and docs

