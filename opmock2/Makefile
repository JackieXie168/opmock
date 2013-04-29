# to compile with LLVM/CLANG 3.1
# llvm-config must be in your PATH
LLVMCOMPONENTS := cppbackend
RTTIFLAG := -fno-rtti
CXXFLAGS := $(shell ~/dev/llvm31_install/bin/llvm-config --cxxflags) $(RTTIFLAG) -static -g
LLVMLDFLAGS := $(shell ~/dev/llvm31_install/bin/llvm-config --ldflags --libs $(LLVMCOMPONENTS)) -static
#CXXFLAGS := $(shell llvm-config-3.1 --cxxflags) $(RTTIFLAG) -static -g
#LLVMLDFLAGS := $(shell llvm-config-3.1 --ldflags --libs $(LLVMCOMPONENTS)) -static

SOURCES = opmock2.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXES = $(OBJECTS:.o=)

LLVMLIBS=-lLLVMCppBackendCodeGen -lLLVMCppBackendInfo -lLLVMTarget -lLLVMCore -lLLVMMC -lLLVMObject -lLLVMSupport

CLANGLIBS = \
				-lclangFrontendTool\
				-lclangFrontend\
				-lclangDriver\
				-lclangSerialization\
				-lclangCodeGen\
				-lclangParse\
				-lclangSema\
				-lclangStaticAnalyzerFrontend\
				-lclangStaticAnalyzerCheckers\
				-lclangStaticAnalyzerCore\
				-lclangAnalysis\
				-lclangARCMigrate\
				-lclangEdit\
				-lclangAST\
				-lclangLex\
				-lclangBasic\
				$(LLVMLIBS)


#				$(shell llvm-config --libs)
#-lclangRewriteFrontend\
#-lclangRewriteCore\

all: $(OBJECTS) $(EXES)

%: %.o
	$(CXX) -o $@ $< $(CLANGLIBS) $(LLVMLDFLAGS)

clean:
	-rm -f $(EXES) $(OBJECTS) *~
