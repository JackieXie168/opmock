#!/bin/sh

$HOME/dev/opmock_install/opmock.sh --input-file header.h \
    --output-path . --use-cpp yes --keep-only space1::Class1::ldpNHResRoute_Walk,OTDRProxy::OTDRConfigurationItf::ConfigLine,one::two::Three::funcOverload

#--no-mock yes
