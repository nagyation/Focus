#include "focus_util.h"



NotifyNotification * notification;


struct notifcation_node{
    struct notification_data * notify_data;
    struct notification_node * next;
};

struct notification_node * head = NULL;
int min_period = -1;

void add_notification(struct notification_data *data)
{
    struct notification_node *t = malloc(sizeof(struct notification_node));
    t->notify_data = data;
    t->next = head;
    head = t;
    
    if(min_period == -1)
	min_period = data->period;
    else
	if(data->period < min_period)
	    min_period = data->period;
}


void _notification_handler()
{
    
}

void init_notification()
{
    notify_init (APP_NAME);
    notification = notify_notification_new ("Remember", "Focus", APP_LOGO);
}

void show_notification(char *title, char *body)
{
    notify_notification_update(notification,title,body,APP_LOGO);
    notify_notification_show();
}

void uninit_notification()
{
    g_object_unref(G_OBJECT(notification));
    notify_uninit();
}
