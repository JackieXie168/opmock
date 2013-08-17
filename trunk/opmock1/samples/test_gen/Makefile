CPPFLAGS=-O0  -ggdb --coverage -Wall -Werror -I../../support
OBJECTS = fizzbuzz.o fizzbuzz_test.o fizzbuzz_test2.o main.o ../../support/opmock.o sound_stub.o

all: fizzbuzzTest
	./fizzbuzz_test

fizzbuzz.o: fizzbuzz.h
opmock.o: opmock.h
main.o: fizzbuzz.h
sound_stub.o: sound_stub.h


fizzbuzzTest: $(OBJECTS)
	gcc -o fizzbuzz_test --coverage $(OBJECTS)


clean: 
	-rm -f $(OBJECTS)
	-rm -f fizzbuzz_test
	-rm -f *.gcda
	-rm -f *.gcno
	-rm -f app.info
	-rm -rf coverage_report

realclean: clean
	-rm -f *stub*
	-rm -f *wrap* *.gc* TEST*.xml
	-rm -f fizzbuzz_test.h fizzbuzz_test2.h main.c

gen:
	./generate.sh

testgen:
	../../scripts/refresh_tests.sh fizzbuzz_test.c fizzbuzz_test2.c

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
