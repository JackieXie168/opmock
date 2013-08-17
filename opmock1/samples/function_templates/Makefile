CPPFLAGS=-O0 -ggdb -DOPMOCK -Wall
OBJECTS = main.o

all: test
	./test

main.o: header.hpp

test: $(OBJECTS)
	g++ -o test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f test
realclean: clean
	-rm -f *stub*
	-rm -f *wrap*
gen:
	./generate.sh
