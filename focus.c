#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMP_ZERO(A,B)   A? A:B
#define CMP_STR(A,B)  !strncmp(A,B,2)
#define MINS 60
#define HOURS 60*MINS

#define APP_NAME "Focus"

NotifyNotification * notification;

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
	   "-d {Duration in hours for the program to run} default is 2 hours\n"	\
	   "-t  {Title of notification}\n"			\
	   "-b  {Text body}\n"\
	   "-h to show this screen\n");
}


void close_program(int signal){
    notification = notify_notification_new ("I'm Closing - Focus", "Hope you've done well", "dialog-information");
    notify_notification_show (notification, NULL);
    g_object_unref(G_OBJECT(notification));
    notify_uninit();	
    exit(signal);
}


void signal_callback(int signal)
{
    close_program(signal);
}


int main(int argc,char *argv[]) {
    fflush(stdout); // clearing the buffer

    printf("This is A daeomon process\n");
    if (argc < 2) // checking if no arguments sent
    {
	printf("This is the default mode\n");
	help_screen();
    }
  
    int time = 10 * MINS;
    int duration = 2 *HOURS;
    char *body= "Focus!";
    char *title = "Remember!";
    int i;
  
 
    //checking for argumets
    for(i = 1;i < argc ; i++)
    {
	if(CMP_STR(argv[i],"-t"))
	    title = i+1 < argc ? argv[i+1] : title;
	else if (CMP_STR(argv[i],"-b"))
	    body = i+1 < argc ? argv[i+1] : body;
	else if (CMP_STR(argv[i],"-p"))
	    time = CMP_ZERO(atoi(argv[i+1])*MINS,time);
	else if (CMP_STR(argv[i],"-d"))
	    duration = CMP_ZERO(atoi(argv[i+1])*HOURS,duration) ;
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
    notify_init (APP_NAME);
    notification = notify_notification_new (title, body, "dialog-information");

    int counter =0;

    while(1){
	notify_notification_show (notification, NULL);
	sleep(time);
	if((counter * time)/MINS >= duration/HOURS)
	    break;
	counter ++;
    }
    
    close_program(EXIT_SUCCESS);
}
