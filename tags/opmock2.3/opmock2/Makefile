# Put llvm-config in you path or add full path below (trailing / required)
LLVM_BIN := 
LLVM_CONFIG_CMD := $(LLVM_BIN)llvm-config

RTTIFLAG := -fno-rtti

#this gets hairy : need to split calls to llvm-config otherwise linking fails
#need also to restrict the number of libraries : the executable is way too large
CXXFLAGS := $(shell $(LLVM_CONFIG_CMD) --cxxflags) $(RTTIFLAG) -static
LDFLAGS := $(shell $(LLVM_CONFIG_CMD) --ldflags) -static
LLVMLIBS = $(shell $(LLVM_CONFIG_CMD) --libs all) $(shell $(LLVM_CONFIG_CMD) --system-libs)

SOURCES = opmock2.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXES = $(OBJECTS:.o=)

#link order found with nm and trial/error!
CLANGLIBS = -lclangFrontend -lclangParse -lclangSema -lclangSerialization -lclangDriver \
	    -lclangAST -lclangBasic -lclangAnalysis -lclangEdit -lclangLex

debug: CXXFLAGS += -g
debug: all

release: CXXFLAGS += -ffunction-sections -fdata-sections
release: LDFLAGS += -gc-sections -s
release: all

all: $(OBJECTS) $(EXES)

%: %.o
	$(CXX) -o $@ $< $(LDFLAGS) $(CLANGLIBS) $(LLVMLIBS)

clean:
	-rm -f $(EXES) $(OBJECTS) *~
