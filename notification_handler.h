#ifndef  __FOCUS_NOTIFICATION_HANDLER__
#define  __FOCUS_NOTIFICATOIN_HANDLER__


void init_notification_handler();
void add_new_notification(char * title, char * body,
                          int period, int duration);
void pause_notification_handler();
void resume_notification_handler();
void uninit_notification_handler();
#endif
