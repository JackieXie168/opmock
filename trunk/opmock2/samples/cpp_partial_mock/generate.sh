#!/bin/sh

#skip some functions for code generation

../../opmock2 -i header.h -o . -q -cpp -s space1::Class1::Class1,nn4::nn5::function1 \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnulibc/include \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gcc_headers/include \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnucpp/include/c++/4.2.4 \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnucpp/include/c++/4.2.4/x86_64-linux-gnu \
	-std=c++98

#-std=c89 -x c for C code

