CC=gcc
CFLAGS= -c -Wall `pkg-config --cflags libnotify `
LDFLAGS= `pkg-config  --libs libnotify `
SOURCES= focus.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=focus

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

install: all
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -t  $(DESTDIR)$(PREFIX)/bin/ focus

clean:
	rm $(OBJECTS) $(EXECUTABLE)
