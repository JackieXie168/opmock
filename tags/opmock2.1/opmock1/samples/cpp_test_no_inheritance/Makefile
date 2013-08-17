CPPFLAGS=-O0 -ggdb -DOPMOCK -Wall -I../../support
OBJECTS = main.o header_stub.o ../../support/opmock.o

all: test
	./test

main.o: header_stub.hpp
header_stub.o: header_stub.hpp

test: $(OBJECTS)
	g++ -o test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f test

realclean: clean
	-rm -f *stub*
	-rm -f *wrap* *.gc* TEST*.xml
gen:
	./generate.sh
