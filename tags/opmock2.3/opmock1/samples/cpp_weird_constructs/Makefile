CPPFLAGS=-O0 -ggdb -DOPMOCK -Wall
OBJECTS = main.o header.o

all: test
	./test

main.o: header.hpp
header.o: header.hpp

test: $(OBJECTS)
	g++ -o test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f test
