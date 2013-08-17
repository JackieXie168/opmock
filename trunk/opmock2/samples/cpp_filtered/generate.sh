#!/bin/sh

../../opmock2 -i header.h -o . -q -cpp -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnulibc/include \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gcc_headers/include \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnucpp/include/c++/4.2.4 -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnucpp/include/c++/4.2.4/x86_64-linux-gnu \
-k space1::Class1::ldpNHResRoute_Walk,OTDRProxy::OTDRConfigurationItf::ConfigLine,one::two::Three::funcOverload \
-std=c++98


