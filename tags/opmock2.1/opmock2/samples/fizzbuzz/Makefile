CPPFLAGS=-O0  -ggdb -I../../support
OBJECTS = fizzbuzz.o fizzbuzz_test.o main.o ../../support/opmock.o


all: fizzbuzzTest
	./fizzbuzz_test

fizzbuzzTest: $(OBJECTS)
	gcc -o fizzbuzz_test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f fizzbuzz_test *.xml

realclean: clean

coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
