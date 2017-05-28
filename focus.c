#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MINS 60
int main(int argc,char *argv[]) {
    printf("%d",argc);
    if (argc < 1)
    {
	printf("the arguments should be {Duration} {Text to appear}\n");
	return 0;
    }
    int time = atoi(argv[1]) * MINS;
    char *text ;
    text= argv[2] ? argv[2] : "Focus!";
    notify_init ("Remember!");
    while(1){
	
	NotifyNotification * Hello = notify_notification_new ("Remember", text, "dialog-information");
	notify_notification_show (Hello, NULL);
	g_object_unref(G_OBJECT(Hello));
	
	sleep(time);
    }
    notify_uninit();
}
