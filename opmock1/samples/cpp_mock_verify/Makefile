CPPFLAGS=-O0 -ggdb -DOPMOCK -Wall -Wall -Werror --coverage -I../../support
OBJECTS = main.o header_stub.o tests.o ../../support/opmock.o

all: test
	./test

test: $(OBJECTS)
	g++ -o test $(OBJECTS) --coverage

clean: 
	-rm -f $(OBJECTS)
	-rm -f test
realclean: clean
	-rm -f *stub* *wrap* TEST*.xml *.gc*
gen:
	./generate.sh
