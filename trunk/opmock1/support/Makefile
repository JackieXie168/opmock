CPPFLAGS=-O0 -ggdb
OBJECTS = opmock.o main.o

all: test
	./test

opmock.o: opmock.h
main.o: opmock.h

test: $(OBJECTS)
	gcc -o test $(OBJECTS)

clean: 
	-rm -f $(OBJECTS)
	-rm -f test