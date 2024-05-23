# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -DMEMTRACE -std=c++11

# Name of the output file
OUTFILE = main

# Source files
SOURCES = main.cpp gate.cpp or.cpp and.cpp value.cpp memtrace.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	del -f *.o *.dot main.exe tabla.txt