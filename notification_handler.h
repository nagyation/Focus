#ifndef  __FOCUS_NOTIFICATION_HANDLER__
#define  __FOCUS_NOTIFICATOIN_HANDLER__


struct notification_data{
    char * title;
    char * body;
    int duration;
    int period;
    int cperiod;
};


void init_notification_handler();
void add_new_notification(struct notification_data* data);
void pause_notification_handler();
void resume_notification_handler();
void uninit_notification_handler();
#endif
