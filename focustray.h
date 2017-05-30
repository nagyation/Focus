#ifndef __SYS_TRAY__
#define __SYS_TRAY__

#include <gtk/gtk.h>
#define CLICKED 0
#define QUIT 1
GtkStatusIcon *create_tray_icon(void (*click_callback)(int));

#endif
