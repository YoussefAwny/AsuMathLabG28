CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp i.cpp functions.cpp muldiv.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matrix

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm edit $(OBJECTS)
