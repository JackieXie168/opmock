CPPFLAGS=-O0  -ggdb -Wall -Werror -I../../support
OBJECTS = code.o test.o main.o ../../support/opmock.o dep_stub.o

all: test
	./test

test: $(OBJECTS)
	gcc -o test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f test

realclean: clean
	-rm -f *stub*
	-rm -f TEST*.xml test.h main.c

gen:
	./generate.sh

list:
	../../scripts/refresh_tests.sh test.c

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
