CPPFLAGS=-O0  -ggdb -Wall -Werror -I../../support
OBJECTS = main.o test.o ../../support/opmock.o c_signature_stub.o

all: test
	./test

test: $(OBJECTS)
	gcc -o test $(OBJECTS)


clean: 
	-rm -f $(OBJECTS)
	-rm -f test

realclean: clean
	-rm -f *stub*
	-rm -f TEST*.xml
	-rm -f main.c test.h

gen:
	./generate.sh

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
list:
	../../scripts/refresh_tests.sh test.c
	
