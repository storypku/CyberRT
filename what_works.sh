#!/usr/bin/env bash
set -e

source setup.bash

bazel build //cyber/...
bazel test //cyber/...
bazel build //cyber_py3/...
bazel test //cyber_py3/...
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
## TODOs
# 0.1 bazle run //examples/cyber_py3:service
# 0.2 bazle run //examples/cyber_py3:client
# 0.3 bazel run //examples/cyber_py3:timer # coredump
# 0.4 bazel run //examples/cyber_py3:parameter # can't terminate
# 1) cyber_visualizer
# 2) cyber release build
# 3) Reorg tutorials and docs
# 4) ROS 1/2 Inter-Op

