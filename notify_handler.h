#ifndef  __FOCUS_NOTIFY_HANDLER__
#define  __FOCUS_NOTIFY_HANDLER__


struct notification_data{
    char * title;
    char * body;
    int duration;
    int period;
    int cperiod;
};


void init_notification_handler();
void add_new_notification(struct notification_data* data);
struct notification_data * new_notification_data(char * title,
						 char * body, int period, int duration);
void pause_notification_handler();
void resume_notification_handler();
#endif
