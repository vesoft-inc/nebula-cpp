#! /usr/bin/env bash

set -e

NEBULA_THIRDPARYTY_HOME=/opt/vesoft/third-party/2.0

# Parsing options from arguments
while getopts "t:" opt; do
    case $opt in
        t)
            NEBULA_THIRDPARYTY_HOME=${OPTARG}
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

for mod in common meta storage graph; do
    wget https://raw.githubusercontent.com/vesoft-inc/nebula/master/src/interface/$mod.thrift
done

# Strip nebula source
# for mod in common graph; do
    # sed -i '/cpp_include/d' $mod.thrift
    # sed -i 's/cpp.type = "[^"]\+"//g' $mod.thrift
# done

for mod in common meta storage graph; do
    $NEBULA_THIRDPARYTY_HOME/bin/thrift1 --strict --allow-neg-enum-vals --gen "mstch_cpp2:include_prefix=${include_prefix},stack_arguments" -o ./src/interface/ $mod.thrift
done

rm common.thrift graph.thrift meta.thrift storage.thrift
