#!/usr/bin/env bash
###
 # @Author: chenkunlin chenkunlin@leedarson.com
 # @Date: 2024-05-16 15:30:49
 # @LastEditors: chenkunlin chenkunlin@leedarson.com
 # @LastEditTime: 2024-05-20 11:13:05
 # @FilePath: /chenkl/lighting_cbb/tools/cmds/unittest/runner.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 
set -e

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
MY_PWD=${PWD}
RUN_SDK_TESTS=0
NO_CLEAR=0

usage()
{
    echo -e "Usage: $0 [-s|-f <filter>|-n|-h]\n"
}

help()
{
  usage
    echo -e "DESCRIPTION:"
    echo -e "Execute unittests.."
    echo -e
    echo -e "OPTIONS:"
    echo -e "  -s   Include SDK unittests."
    echo -e "  -f   Filter a specific unittest. Specify -s flag if the test is under the SDK."
    echo -e "  -n   Doesnt clean the old build."
    echo -e "  -h   Prints this help\n"
}

while getopts s,f:,h,n opts
do
    # shellcheck disable=SC2213
    case "${opts}" in
        s)  RUN_SDK_TESTS=1;;
        f)  FILTER="$OPTARG";;
        n)  NO_CLEAR=1;;
        h)  help; exit;;
        \?) help; exit;;
    esac
done

if ! basename -- "${PWD}" | grep -Eq "^lighting_[A-Za-z]+"; then
    echo -e "ERROR: This script has to be executed from lighing_cbb"; exit 1;
fi

pushd "${SCRIPT_PATH}"

if [ -d "${SCRIPT_PATH}/build" ]; then
    if [ "${NO_CLEAR}" == 0 ]; then
        rm -rf $SCRIPT_PATH/build
    fi
fi

cmake -DCMAKE_INSTALL_PREFIX=${HOME}/opt \
            -DCMAKE_BUILD_TYPE=Debug \
            -DROOT_DIR="${MY_PWD}" \
            -DRUN_SDK_TESTS="${RUN_SDK_TESTS}" \
            -DFILTER:STRING=$FILTER -B build

make -C build
make CTEST_OUTPUT_ON_FAILURE=TRUE test -C build

popd
