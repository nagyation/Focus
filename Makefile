CC=gcc
CFLAGS= -c -Wall `pkg-config --cflags libnotify gtk+-3.0 appindicator3-0.1`
LDFLAGS= -pthread `pkg-config  --libs libnotify gtk+-3.0 appindicator3-0.1 gsound glib-2.0`
SOURCES= menu_tray.c focus.c notification.c notification_handler.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=focus

ifeq ($(datadir),)
    datadir := /usr/share
endif
icon_dir = $(datadir)/icons/hicolor
sound_dir = $(datadir)/sounds/focus/
gtk_update_icon_cache = gtk-update-icon-cache -f -t $(icon_dir)
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS)  -o $@

.c.o:
	$(CC) $< $(CFLAGS)  -o $@

install: all
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -t $(DESTDIR)$(PREFIX)/bin/ $(EXECUTABLE)	
	install -t $(icon_dir)/scalable/apps/ icons/focus-icon.svg
	install -d $(sound_dir)
	install -t $(sound_dir)  sounds/to-the-point.ogg
	$(gtk_update_icon_cache);

clean:
	rm $(OBJECTS) $(EXECUTABLE)
