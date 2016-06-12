CC=g++
CFLAGS=
LDFLAGS=-lusb-1.0

all: make bin/g810-led

make:
	mkdir bin

bin/g810-led: src/main.cpp src/classes/*
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)