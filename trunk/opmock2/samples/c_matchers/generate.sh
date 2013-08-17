#!/bin/sh
C_HEADERS="-I../../support/gnulibc/include -I../../support/gcc_headers/include"

../../opmock2 -i dep.h -o . $C_HEADERS -q

