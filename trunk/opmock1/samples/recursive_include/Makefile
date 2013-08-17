CPPFLAGS=-O0 -ggdb -DOPMOCK -Wall -Werror -I./inc1 -I./inc2 -I./inc3 -I../../support
OBJECTS = main.o header_stub.o ../../support/opmock.o

all: test
	./test

#main.o: header_stub.hpp
#header_stub.o: header_stub.hpp
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
