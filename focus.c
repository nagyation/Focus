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
	printf("This is the default mode\n");
	printf("The arguments should be  {Period Time in mins}   {Title to appear}  {Text to appear}\n");
	printf("The default Period is 10 mins\n");
    }

    int time = 10 * MINS;
    char *body= "Focus!";
    char *title = "Remember!";
    int i;
   
    for(i = 1;i < argc ; i++)
    {
	if(!strncmp(argv[i],"-t",2))
	    title = CMP_EMP(argv[i+1],"Remember!");
	else if (!strncmp(argv[i],"-b",2))
	    body = CMP_EMP(argv[i+1], "Focus!");
	else if (!strncmp(argv[i],"-p",2))
	    time = atoi(argv[i+1])*MINS;
    }
    
    notify_init (APP_NAME);
    NotifyNotification * notification = notify_notification_new (title, body, "dialog-information");

    while(1){
	notify_notification_show (notification, NULL);
	sleep(time);
    }

    g_object_unref(G_OBJECT(notification));
    notify_uninit();	
 
}
