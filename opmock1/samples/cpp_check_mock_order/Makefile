CPPFLAGS=-O0 -ggdb -DOPMOCK -Wall -I../../support
OBJECTS = main.o header_stub.o tests.o ../../support/opmock.o

all: test
	./test
test: $(OBJECTS)
	g++ -o test $(OBJECTS)
clean: 
	-rm -f $(OBJECTS)
	-rm -f test
realclean: clean
	-rm -f *stub* *wrap* TEST*.xml
gen:
	./generate.sh
