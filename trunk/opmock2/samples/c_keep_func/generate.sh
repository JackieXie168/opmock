#!/bin/sh
C_HEADERS="-I../../support/gnulibc/include -I../../support/gcc_headers/include"

../../opmock2 -i c_signature.h -o . $C_HEADERS -DHAS_FUNC=1 -q -k function3,function29b,function1a -Dfoo=boo

