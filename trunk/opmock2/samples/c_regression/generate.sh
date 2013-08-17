#!/bin/sh
C_HEADERS="-I../../support/gnulibc/include -I../../support/gcc_headers/include"

../../opmock2 -i sound.h -o . -q $C_HEADERS

