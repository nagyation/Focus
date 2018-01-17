#include "notify.h"
#include <libnotify/notify.h>
#include "config.h"
#include <stdlib.h>



NotifyNotification * notification;


void init_notification()
{
    notify_init (APP_NAME);
    notification = notify_notification_new ("Remember", "Focus", APP_LOGO);
}

void show_notification(char *title, char *body)
{
    notify_notification_update(notification,title,body,APP_LOGO);
    notify_notification_show(notification,NULL);
}

void uninit_notification()
{
    g_object_unref(G_OBJECT(notification));
    notify_uninit();
}