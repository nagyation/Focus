#ifndef __FOCUS_UTIL__
#define __FOCUS_UTIL__


#include <libnotify/notify.h>
#include "focus_config.h"
#include <stdlib.h>

struct notifcation_data{
    char * title;
    char * body;
    int duration;
    int period;
};

void init_notification();
void show_notification(char * title, char *body);
void uninit_notification();

#endif
