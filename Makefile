CC=gcc
CFLAGS= -c -Wall `pkg-config --cflags libnotify gtk+-3.0`
LDFLAGS= -pthread `pkg-config  --libs libnotify gtk+-3.0`
SOURCES= focustray.c focus.c
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
	install -d $(DESTDIR)$(PREFIX)/share/	
	install -d $(DESTDIR)$(PREFIX)/share/focus/
	install -t $(DESTDIR)$(PREFIX)/share/focus resources/focus_icon.png
	install -t  $(DESTDIR)$(PREFIX)/bin/ focus

clean:
	rm $(OBJECTS) $(EXECUTABLE)
