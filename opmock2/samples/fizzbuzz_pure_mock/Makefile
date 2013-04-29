CPPFLAGS=-O0  -ggdb -Wall -Werror -I../../support
OBJECTS = fizzbuzz.o fizzbuzz_test.o main.o ../../support/opmock.o sound_stub.o

all: fizzbuzzTest
	./fizzbuzz_test

fizzbuzzTest: $(OBJECTS)
	gcc -o fizzbuzz_test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f fizzbuzz_test

realclean: clean
	-rm -f *stub*
	-rm -f TEST*.xml

gen:
	./generate.sh

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
