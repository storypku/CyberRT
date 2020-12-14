#!/usr/bin/env bash

set -e

sudo apt-get update && \
	sudo apt-get install -y --no-install-recommends \
		libasio-dev \
		libtinyxml2-dev \
		libpoco-dev

TOP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

git clone --single-branch --branch release/1.5.0 --depth 1 \
	https://github.com/eProsima/Fast-RTPS.git /tmp/fast-rtps.git

DEST_DIR="/usr/local/fast-rtps"

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

