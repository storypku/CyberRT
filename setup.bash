#! /usr/bin/env bash

TOP_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -P)"
source ${TOP_DIR}/tools/common.bashrc

export CYBER_PATH=${TOP_DIR}

BAZEL_BIN_DIR="${TOP_DIR}/bazel-bin"

pathprepend ${BAZEL_BIN_DIR}/cyber_py3/tools
pathprepend ${BAZEL_BIN_DIR}/cyber/mainboard
pathprepend ${BAZEL_BIN_DIR}/cyber/tools/cyber_recorder
pathprepend ${BAZEL_BIN_DIR}/cyber/tools/cyber_monitor

pathprepend /usr/local/fast-rtps/lib LD_LIBRARY_PATH

# TODO(storypku):
#   Revisit for external projects that depend on CyberRT
pathprepend ${BAZEL_BIN_DIR} PYTHONPATH
pathprepend ${BAZEL_BIN_DIR}/cyber_py3/internal PYTHONPATH

export CYBER_DOMAIN_ID=80
export CYBER_IP=127.0.0.1

export GLOG_log_dir="${TOP_DIR}/data/log"
export GLOG_alsologtostderr=1
export GLOG_colorlogtostderr=1
export GLOG_minloglevel=0

# for DEBUG log
#export GLOG_v=4

export sysmo_start=0

source ${TOP_DIR}/tools/cyber_completions.bash

unset BAZEL_BIN_DIR TOP_DIR
