#!/bin/sh

export SWIG_FEATURES="$SWIG_FEATURES -I./inc1 -I./inc2 -I./inc3"
$HOME/dev/opmock_install/opmock.sh --input-file header.h --output-path . --use-cpp yes
