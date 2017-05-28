#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MINS 60
int main(int argc,char *argv[]) {
    if (argc < 2)
    {
	printf("the arguments should be {Duration} {Text to appear}\n");
	return 0;
    }
    int time = atoi(argv[1]) * MINS;
    char *text ;
    text= argv[2] ? argv[2] : "Focus!";
       while(1){
	notify_init ("Remember!");
	NotifyNotification * notification = notify_notification_new ("Remember", text, "dialog-information");
	notify_notification_show (notification, NULL);
	g_object_unref(G_OBJECT(notification));
	notify_uninit();	
	sleep(time);
    }
   
}
