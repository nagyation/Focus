#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CMP_EMP(A,B)   A? A:B
#define MINS 60

#define APP_NAME "Focus"

int main(int argc,char *argv[]) {
    if (argc < 2)
    {
	printf("This is the default without arguments\n");
	printf("The arguments should be  {Period Time in mins}   {Title to appear}  {Text to appear}\n");
	printf("Defailt period time is 10 mins\n");
    }
    int time ;
    char *body= "Focus!";
    char *title = "Remember!";
    if(argc-1 == 2)
	title = argv[2];
    if(argc-1 == 3)
	body = argv[3];
    if(argc-1 == 1)
	time = (CMP_EMP(atoi(argv[1]), 10)) * MINS;
    
    notify_init (APP_NAME);
    NotifyNotification * notification = notify_notification_new (title, body, "dialog-information");

    while(1){
	notify_notification_show (notification, NULL);
	sleep(time);
    }

    g_object_unref(G_OBJECT(notification));
    notify_uninit();	
 
}
