#! /usr/bin/env bash
#
# Copyright (c) 2021 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

set -e

NEBULA_THIRDPARYTY_HOME=/opt/vesoft/third-party/2.0
NEBULA_INTERFACE_HOME=src/interface
SYNC_REMOTE_INTERFACE=0

# Parsing options from arguments
while getopts "t:u" opt; do
    case $opt in
        t)
            NEBULA_THIRDPARYTY_HOME=${OPTARG}
            ;;
        u)
            SYNC_REMOTE_INTERFACE=1
            ;;
        \?)
            echo "Invalid option: -${OPTARG}" >&2
            exit 1
            ;;
        :)
            echo "Option -${OPTARG} requires an argument." >&2
            exit 1
            ;;
    esac
done

if [ $SYNC_REMOTE_INTERFACE -eq 1 ]; then
    for mod in common meta storage graph; do
        wget -P $NEBULA_INTERFACE_HOME https://raw.githubusercontent.com/vesoft-inc/nebula/master/src/interface/$mod.thrift
    done
fi

# Strip nebula source
# for mod in common graph; do
    # sed -i '/cpp_include/d' $mod.thrift
    # sed -i 's/cpp.type = "[^"]\+"//g' $mod.thrift
# done

pushd $NEBULA_INTERFACE_HOME
for mod in common meta storage graph; do
    $NEBULA_THIRDPARYTY_HOME/bin/thrift1 --strict --allow-neg-enum-vals --gen "mstch_cpp2:include_prefix=${include_prefix},stack_arguments" -o . $mod.thrift
done
popd
