#!/bin/sh
#gcc - -xc -v -E
#will give compilation options and default include path for the gcc compilera

#../../opmock2 -i cpp_signature.hpp -o . -q -cpp -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include -I/usr/include/c++/4.7 

#try to include SGI STL headers instead of GNU headers,
# so that CLANG can parse it properly
#../../opmock2 -i cpp_signature.hpp -o . -q -cpp -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include -I../../support/stl

#../../opmock2 -i cpp_signature.hpp -o . -q -cpp -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include -I/home/pascal/dev/stlport/include/stlport


#dessous marche
#tenter avec remplacement complet des headers
#../../opmock2 -i cpp_signature.hpp -o . -q -cpp -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include -I/home/pascal/dev/opmock/opmock/opmock2/support/gnucpp/include/c++/4.2.4 -I/home/pascal/dev/opmock/opmock/opmock2/support/gnucpp/include/c++/4.2.4/x86_64-linux-gnu


../../opmock2 -i cpp_signature.hpp -o . -q -cpp -I/home/pascal/dev/opmock/opmock/opmock2/support/gnulibc/include \
    -I/home/pascal/dev/opmock/opmock/opmock2/support/gcc_headers/include \
    -I/home/pascal/dev/opmock/opmock/opmock2/support/gnucpp/include/c++/4.2.4 -I/home/pascal/dev/opmock/opmock/opmock2/support/gnucpp/include/c++/4.2.4/x86_64-linux-gnu

