CPPFLAGS=-O0  -ggdb --coverage -I../../support
OBJECTS = fizzbuzz.o fizzbuzz_test.o main.o ../../support/opmock.o


all: fizzbuzzTest
	./fizzbuzz_test


fizzbuzz.o: fizzbuzz.h
fizzbuzz_test.o: fizzbuzz.h fizzbuzz_test.h
opmock.o: opmock.h
main.o: fizzbuzz.h fizzbuzz_test.h


fizzbuzzTest: $(OBJECTS)
	gcc -o fizzbuzz_test --coverage $(OBJECTS)


clean: 
	-rm -f $(OBJECTS)
	-rm -f fizzbuzz_test
	-rm -f *.gcda
	-rm -f *.gcno
	-rm -f app.info
	-rm -rf coverage_report TEST*.xml

realclean: clean


coverage:
	lcov --directory ./ --capture --output-file app.info
	genhtml -o coverage_report app.info
