#! /usr/bin/env bash

TOP_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd -P)"
export CYBER_PATH=${TOP_DIR}

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/fast-rtps/lib
# Prevent multiple entries of my_path in PATH
function add_to_path() {
    if [ -z "$1" ]; then
        return
    fi
    local my_path="$1"
    if [ -n "${PATH##*${my_path}}" ] && [ -n "${PATH##*${my_path}:*}" ]; then
        export PATH=$PATH:${my_path}
    fi
}

add_to_path "${TOP_DIR}/bazel-bin/cyber_py3/tools"
add_to_path "${TOP_DIR}/bazel-bin/cyber/mainboard"

export PYTHONPATH=${TOP_DIR}/bazel-bin:$PYTHONPATH

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
