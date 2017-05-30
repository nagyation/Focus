#include <libnotify/notify.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMP_EMP(A,B)   A? A:B
#define MINS 60

#define APP_NAME "Focus"

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


int main(int argc,char *argv[]) {
    fflush(stdout); // clearing the buffer

    printf("This is A daeomon process\n");
    if (argc < 2) // checking if no arguments sent
    {
	printf("This is the default mode\n");
	printf("The arguments should be  -p {Period Time in mins}  -t  {Title to appear} -b  {Text to appear}\n");
	printf("The default Period is 10 mins\n");
    }
  
    int time = 10 * MINS;
    char *body= "Focus!";
    char *title = "Remember!";
    int i;
  

    daemonize();    
 
    //checking for argumets
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
