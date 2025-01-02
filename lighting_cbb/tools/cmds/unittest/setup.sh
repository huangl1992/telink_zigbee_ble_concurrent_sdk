#!/usr/bin/env bash
###
 # @Author: chenkunlin chenkunlin@leedarson.com
 # @Date: 2024-05-16 11:21:43
 # @LastEditors: chenkunlin chenkunlin@leedarson.com
 # @LastEditTime: 2024-05-20 11:17:17
 # @FilePath: /chenkl/lighting_cbb/setup.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 

set -e

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
CMOCKA_PATH="${SCRIPT_PATH}/../../../thirdparty/cmocka/"

pushd $SCRIPT_PATH

mkdir -p "${HOME}/opt"

if [ -d "${CMOCKA_PATH}/build" ]; then
    rm -rf $CMOCKA_PATH/build
fi

cmake -DCMAKE_INSTALL_PREFIX=${HOME}/opt -DCMAKE_BUILD_TYPE=Debug -S $CMOCKA_PATH -B $CMOCKA_PATH/build

make -C $CMOCKA_PATH/build
make install -C $CMOCKA_PATH/build

apt-get update && apt-get install -y pkg-config cmake libcmocka0 libcmocka-dev

popd

