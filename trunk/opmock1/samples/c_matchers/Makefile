CPPFLAGS=-O0  -ggdb --coverage -Wall -Werror -I../../support
OBJECTS = code.o test.o main.o ../../support/opmock.o dep_stub.o

all: test
	./test

test: $(OBJECTS)
	gcc -o test --coverage $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f test
	-rm -f *.gcda
	-rm -f *.gcno
	-rm -f app.info
	-rm -rf coverage_report

realclean: clean
	-rm -f *stub*
	-rm -f *wrap* *.gc* TEST*.xml test.h main.c

gen:
	./generate.sh

refresh:
	../../scripts/refresh_tests.sh test.c

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
