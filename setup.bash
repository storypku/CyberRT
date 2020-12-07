#! /usr/bin/env bash

TOP_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -P)"
export CYBER_PATH=${TOP_DIR}

# export PYTHONPATH=${bazel_bin_path}/cyber_py3/internal:${PYTHONPATH}

export CYBER_DOMAIN_ID=80
export CYBER_IP=127.0.0.1

export GLOG_log_dir="${TOP_DIR}/data/log"

export GLOG_alsologtostderr=1
export GLOG_colorlogtostderr=1
export GLOG_minloglevel=0

export sysmo_start=0

# for DEBUG log
#export GLOG_v=4

source ${TOP_DIR}/tools/cyber_completions.bash
