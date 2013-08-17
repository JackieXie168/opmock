#!/bin/sh

$HOME/dev/opmock_install/opmock.sh --input-file header.h \
    --output-path . --use-impl no --use-cpp yes --skip-funct space1::Class1::funcToRemove,space1::Class1::funcToRemoveTwo
