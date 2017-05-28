#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CMP_EMP(A,B)   A? A:B
#define MINS 60

#define APP_NAME "Focus"

int main(int argc,char *argv[]) {
    
    int time = 10 * MINS;
    char *body= "Focus!";
    char *title = "Remember!";

    if (argc < 4)
    {
	printf("The arguments should be  {Period Time in mins}   {Title to appear}  {Text to appear}\n");
    return 0;
    }
    if (argc > 4)
    {
	printf("Wrong numbers of arguments\n");
    return 0;
    }
	time = atoi(argv[1]) *MINS;
	title = argv[2];
	body = argv[3];

    notify_init (APP_NAME);
    NotifyNotification * notification = notify_notification_new (title, body, "dialog-information");

    while(1){
	notify_notification_show (notification, NULL);
	sleep(time);
    }

    g_object_unref(G_OBJECT(notification));
    notify_uninit();	
 
}
