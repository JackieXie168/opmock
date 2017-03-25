This is the README.txt file.

Licence
======= 
This software is covered by the GPL V3 or higher.

How to compile
==============
These are the instructions to compile on Linux/Unix, to be run from a shell.
You need llvm 3.9.1 and clang 3.9.1 to compile opmock 2. Opmock 2 is compiled
as a static executable, so you don't need more than the binary at runtime.
To compile llvm/clang you need a decent compiler. Gcc 4.1.x is known to produce
corrupted executables. Gcc 4.3 and up seems ok.

Building LLVM + Clang (https://clang.llvm.org/get_started.html)
---------------------

cd $HOME
wget http://releases.llvm.org/3.9.1/llvm-3.9.1.src.tar.xz
tar -Jxf llvm-3.9.1.src.tar.xz
cd llvm-3.9.1.src/tools
wget http://releases.llvm.org/3.9.1/cfe-3.9.1.src.tar.xz
tar -Jxf cfe-3.9.1.src.tar.xz
mv cfe-3.9.1.src clang
cd ../..
mkdir build
cd build
cmake -G "Unix Makefiles" ../llvm-3.9.1.src/ -DCMAKE_INSTALL_PREFIX=../llvm-3.9.1.install
make -j4
make install


Building opmock 2
-----------------
1) make sure the llvm 3.9.1 install is in your path

export PATH=$HOME/llvm-3.9.1.install/bin:$PATH

2) get opmock 2 sources from Subversion

svn checkout svn://svn.code.sf.net/p/opmock/code/ opmock-code
cd opmock-code/trunk/opmock2
make clean
make
# if you want a smaller executable
strip opmock2

The resulting opmock2 executable can be copied where you want.

Contributors
============
Pascal Ognibene (pognibene at gmail dot com) is the author of Opmock.
Richard Jorgensen made some welcome modifications to make opmock compatible with llvm/clang > 3.9.1.
Kudos Richard!

Thanks
======
Many thanks go to Richard M. Stallman for being one of the few to fight for freedom.
Many thanks as well to the Clang and LLVM teams for their libraries and tools.
