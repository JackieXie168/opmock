This is the README.txt file.

Licence
======= 
This software is covered by the GPL V3 or higher.

How to compile
==============
These are the instructions to compile on Linux/Unix, to be run from a shell.
You need llvm 3.1 and clang 3.1 to compile opmock 2. Opmock 2 is compiled
as a static executable, so you don't need more than the binary at runtime.
To compile llvm/clang you need a decent compiler. Gcc 4.1.x is known to produce
corrupted executables. Gcc 4.3 and up seems ok.

Building LLVM + Clang
---------------------

cd $HOME
mkdir llvm31
cd llvm31
wget http://llvm.org/releases/3.1/llvm-3.1.src.tar.gz
tar xzf llvm-3.1.src.tar.gz
mv llvm-3.1.src llvm
cd llvm/tools
wget http://llvm.org/releases/3.1/clang-3.1.src.tar.gz
tar xzf clang-3.1.src.tar.gz
mv clang-3.1 clang
cd ../..
mkdir build
cd build
../llvm/configure --prefix=../llvm31_install
make -j4 ENABLE_OPTIMIZED=1 DISABLE_ASSERTIONS=1
make install ENABLE_OPTIMIZED=1 DISABLE_ASSERTIONS=1

Building opmock 2
-----------------
1) make sure the llvm 3.1 install is in your path

export PATH=$HOME/llvm31/llvm31_install/bin:$PATH

2) get opmock 2 sources from Subversion

svn checkout svn://svn.code.sf.net/p/opmock/code/ opmock-code
cd opmock-code/opmock2
make clean
make

The resulting opmock2 executable can be copied where you want.

Thanks
======
Many thanks go to Richard M. Stallman for being one of the few to fight for freedom.
Many thanks as well to the Clang and LLVM teams for their libraries and tools.
