#!/usr/bin/env bash

set -e

TOP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

sudo apt-get update && \
    sudo apt-get install -y --no-install-recommends \
        ncurses-dev \
        uuid-dev \
        libasio-dev \
        libtinyxml2-dev \
        libpoco-dev

DEST_DIR="/usr/local/fast-rtps"
if [[ -d "${DEST_DIR}" ]]; then
    echo "Previous fast-rtps installation found and will be used."
else
    git clone --single-branch --branch release/1.5.0 --depth 1 \
        https://github.com/eProsima/Fast-RTPS.git /tmp/fast-rtps.git
    pushd /tmp/fast-rtps.git
        git submodule update --init
        patch -p1 < ${TOP_DIR}/FastRTPS_1.5.0.patch
        mkdir -p build && cd build
        cmake -DEPROSIMA_BUILD=ON \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_INSTALL_PREFIX=${DEST_DIR} ..
        make -j$(nproc)
        sudo make install
    popd
    rm -fr /tmp/fast-rtps.git
fi


