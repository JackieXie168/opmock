#!/bin/sh
#gcc - -xc -v -E
#will give compilation options and default include path for the gcc compilera

../../opmock2 -i cpp_signature.hpp -o . -q -cpp -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnulibc/include \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gcc_headers/include \
    -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnucpp/include/c++/4.2.4 -I/home/pascal/dev/opmock/opmock-code/opmock2/support/gnucpp/include/c++/4.2.4/x86_64-linux-gnu

