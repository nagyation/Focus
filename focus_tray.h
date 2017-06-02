#ifndef __FOCUS_TRAY__
#define __FOCUS_TRAY__

#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <stdlib.h>

#define CLICKED 0
#define QUIT 1
#define PAUSE 2
#define UNPAUSE 3

void create_tray_icon(void (*click_callback)(int));

#endif
