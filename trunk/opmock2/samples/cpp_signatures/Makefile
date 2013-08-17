CPPFLAGS=-O0  -ggdb -Wall -Werror -I../../support
OBJECTS = main.o test.o ../../support/opmock.o cpp_signature_stub.o

all: test
	./test

test: $(OBJECTS)
	g++ -o test $(OBJECTS)


clean: 
	-rm -f $(OBJECTS)
	-rm -f test

realclean: clean
	-rm -f *stub*
	-rm -f TEST*.xml
	-rm -f main.cpp test.h

gen:
	./generate.sh

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
list:
	../../scripts/refresh_tests.sh test.cpp;mv main.c main.cpp
	
