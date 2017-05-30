CC=gcc
CFLAGS= -c -Wall `pkg-config --cflags libnotify `
LDFLAGS= `pkg-config  --libs libnotify `
SOURCES= focus.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=focus

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm $(OBJECTS) $(EXECUTABLE)
