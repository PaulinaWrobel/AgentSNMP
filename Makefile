CC=g++
CFLAGS =-c 
LDFLAGS=
SOURCES=SNMPServer.cpp SNMPDeserializer.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent-snmp

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o