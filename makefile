# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -Werror -std=c++11 -O2
#CFLAGS = -Wall -std=c++11 -O2

# Name of the output file
OUTFILE = main

# Source files
SOURCES = main.cpp gateStack.cpp memtrace.cpp gates/gate.cpp gates/or.cpp gates/nor.cpp gates/nand.cpp gates/and.cpp gates/value.cpp 

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(addprefix oFiles/, $(notdir $(OBJECTS)))

all: $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJECTS)

oFiles/%.o: %.cpp | oFiles
	$(CC) $(CFLAGS) -c $< -o $@

oFiles/%.o: gates/%.cpp | oFiles
	$(CC) $(CFLAGS) -c $< -o $@

oFiles:
	mkdir -p oFiles

clean:
	del *.txt *.dot main.exe
	cd oFiles && (del /Q *.o 2>NUL)