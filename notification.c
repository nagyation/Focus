#include "notification.h"
#include <libnotify/notify.h>
#include "config.h"
#include <stdlib.h>
#include "log.h"
#include <gsound.h>
#include <glib.h>

NotifyNotification * notification;
GSoundContext *gsound = NULL;

void init_notification()
{
    notify_init (APP_NAME);
    notification = notify_notification_new ("Remember", "Focus", APP_LOGO);
}

void show_notification(char *title, char *body)
{

    notify_notification_update(notification,title,body,APP_LOGO);
    notify_notification_show(notification,NULL);

    if(!gsound)
      gsound = gsound_context_new(NULL, NULL);

    if (!gsound) {
      logerr("Error while trying to play notification");
      return;
    }

    gsound_context_play_simple(gsound, NULL,NULL,
                               GSOUND_ATTR_MEDIA_FILENAME, NOTIFICATION_SOUND,
                               NULL);
}

void uninit_notification()
{
    g_object_unref(G_OBJECT(notification));
    notify_uninit();
}
