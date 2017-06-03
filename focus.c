#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#include "focus_tray.h"
#include "focus_config.h"

#define CMP_ZERO(A,B)   A? A:B
#define CMP_STR(A,B)  !strncmp(A,B,2)
#define MINS 60
#define HOURS 60 * MINS


NotifyNotification * notification;
unsigned int period = 10 * MINS;
unsigned int duration = 0;
char *body= "Focus!";
char *title = "Remember!";
int period_counter =0;
pthread_t timer;

static void daemonize(void)
{
    pid_t pid, sid;

    /* already a daemon */
    if ( getppid() == 1 ) return;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* At this point we are executing as the child process */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    /* Redirect standard files to /dev/null */
    freopen( "/dev/null", "r", stdin);
    freopen( "/dev/null", "w", stdout);
    freopen( "/dev/null", "w", stderr);

}

void help_screen(){
    printf("The arguments available are:\n");
    printf("-p {Period Time in mins} default is 10 mins\n"\
	   "-d {Duration in hours for the program to run} default is 0 means forever\n"	\
	   "-t  {Title of notification}\n"			\
	   "-b  {Text body}\n"\
	   "-h to show this screen\n");
}


void close_program(int signal){
    notification = notify_notification_new ("I'm Closing - Focus", "Hope you've done well", APP_LOGO);
    notify_notification_show (notification, NULL);
    g_object_unref(G_OBJECT(notification));
    notify_uninit();	
    exit(signal);
}

static void *start_timer(void *n){

    while(1){
	notification = notify_notification_new (title, body, APP_LOGO);
	notify_notification_show (notification, NULL);
	sleep(period);
	if((period_counter * period) >= duration && duration)
	    close_program(EXIT_SUCCESS);
	if (duration)
	    period_counter ++;
    }
    return 0;
}


void signal_callback(int signal)
{
    close_program(signal);
}

void system_tray_callback(int action)
{
    if (action == QUIT)
	close_program(EXIT_SUCCESS);
    else if(action == CLICKED)
    {
	notification = notify_notification_new ("Stop Clicking on me it hurts :\\ ", "Focus!", APP_LOGO);
	notify_notification_show (notification, NULL);
    }
    else if(action == PAUSE)
    {
	notification = notify_notification_new ("Okay okay ..", "I'll Pause", APP_LOGO);
	notify_notification_show (notification, NULL);
	pthread_cancel(timer);
    }
    else if(action == UNPAUSE)
    {
	int ret = pthread_create( &timer, NULL,&start_timer,NULL );
     if(ret)
     {
	 notification = notify_notification_new ("Sorry", "Couldn't unpause please try again ://", APP_LOGO);
	notify_notification_show (notification, NULL);
	pthread_cancel(timer);
     }
    }
}



int main(int argc,char *argv[]) {
    fflush(stdout); // clearing the buffer

    printf("This is A daeomon process\n");
    if (argc < 2) // checking if no arguments sent
    {
	printf("This is the default mode\n");
	help_screen();
    }
  
    
    int i;
	
    //checking for argumets
    for(i = 1;i < argc ; i++)
    {
	if(CMP_STR(argv[i],"-t"))
	    title = i+1 < argc ? argv[i+1] : title;
	else if (CMP_STR(argv[i],"-b"))
	    body = i+1 < argc ? argv[i+1] : body;
	else if (CMP_STR(argv[i],"-p"))
	    period = CMP_ZERO(atoi(argv[i+1]) * MINS,period);
	else if (CMP_STR(argv[i],"-d"))
	    duration = atoi(argv[i+1]) * HOURS ;
	else if (CMP_STR(argv[i],"-h"))
	{
	    help_screen();
	    exit(EXIT_SUCCESS);
	}
    }
    

    daemonize();

    //recieve Terminate signals from kill
    signal(SIGINT, signal_callback);
    signal(SIGTERM, signal_callback);
    

    //Intializing the notification
   
    gtk_init(&argc, &argv);
    gtk_window_set_default_icon_name (APP_LOGO);
    notify_init (APP_NAME);

    
    int iret1 = pthread_create( &timer, NULL,&start_timer,NULL );
     if(iret1)
     {
         close_program(EXIT_FAILURE);
     }

     create_tray_icon(system_tray_callback);

    
    gtk_main();
}
