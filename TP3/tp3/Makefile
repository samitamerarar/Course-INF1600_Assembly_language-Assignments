CC=gcc
CFLAGS=-g -m32 -g -Wall
RM=rm -f
TARGET=tp3
OBJECTS=tp3.o equals.o transpose.o multiply.o diagonal.o average.o

.PHONY: clean

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.s.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: tp3

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o $(TARGET)
