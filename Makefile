CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp matrix_functions.cpp functions.cpp DetandInverse.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matrix

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm edit $(OBJECTS)
