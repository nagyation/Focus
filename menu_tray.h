#ifndef __FOCUS_MENU_TRAY__
#define __FOCUS_MENU_TRAY__

#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <stdlib.h>
#include <string.h>

#define TRAY_CLICKED 0
#define TRAY_QUIT 1
#define TRAY_PAUSE 2
#define TRAY_UNPAUSE 3

void intiate_tray_icon(char*,void (*click_callback)(int));

#endif
