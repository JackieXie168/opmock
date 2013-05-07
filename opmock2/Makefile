# to compile with LLVM/CLANG 3.2
# llvm-config must be in your PATH
LLVMCOMPONENTS := cppbackend
RTTIFLAG := -fno-rtti
#CXXFLAGS := $(shell ~/dev/llvm31_install/bin/llvm-config --cxxflags) $(RTTIFLAG) -static -g
#LLVMLDFLAGS := $(shell ~/dev/llvm31_install/bin/llvm-config --ldflags --libs $(LLVMCOMPONENTS)) -static

#this gets hairy : need to split calls to llvm-config otherwise linking fails
#need also to restrict the number of libraries : the executable is way too large
CXXFLAGS := $(shell ~/dev/llvm32_install/bin/llvm-config --cxxflags) $(RTTIFLAG) -static -g
LLVMLDFLAGS := $(shell ~/dev/llvm32_install/bin/llvm-config --libs all) $(shell ~/dev/llvm32_install/bin/llvm-config --ldflags) -static


#CXXFLAGS := $(shell llvm-config-3.1 --cxxflags) $(RTTIFLAG) -static -g
#LLVMLDFLAGS := $(shell llvm-config-3.1 --ldflags --libs $(LLVMCOMPONENTS)) -static

SOURCES = opmock2.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXES = $(OBJECTS:.o=)


#use LLVMLDFLAGS twice to avoid ld stripping unused symbols too early
#link order found with nm and trial/error!
#note that there's kind of a circular dependency on libclangAST
CLANGLIBS = -lclangAST -lclangBasic -lclangFrontend -lclangParse -lclangLex -lclangSema -lclangSerialization \
			-lclangDriver -lclangBasic -lclangAST -lclangEdit -lclangAnalysis \
$(LLVMLDFLAGS)

all: $(OBJECTS) $(EXES)

%: %.o
	$(CXX) -o $@ $< $(LLVMLDFLAGS) $(CLANGLIBS) 

clean:
	-rm -f $(EXES) $(OBJECTS) *~
