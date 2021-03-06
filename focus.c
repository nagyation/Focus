#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <limits.h>
#include "menu_tray.h"
#include "config.h"
#include "notification.h"
#include "notification_handler.h"

#define CHECK_ZERO(A,B)   A > 0? A:B
#define CMP_ARG(A,B)  !strncmp(A,B,2)
#define MINS 60
#define HOURS 60 * MINS
#define INF INT_MAX
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
  show_notification ("I'm Closing - Focus", "Hope you've done well");
  uninit_notification();
  exit(signal);
}


void signal_callback(int signal)
{
  close_program(signal);
}

void system_tray_callback(int action)
{
  if (action == TRAY_QUIT)
    close_program(EXIT_SUCCESS);
  else if(action == TRAY_CLICKED)
    {
      
      show_notification ("Stop Clicking on me it hurts :\\ ", "Focus!");
    }
  else if(action == TRAY_PAUSE)
    {
      show_notification("Okay okay ..", "I'll Pause");
      pause_notification_handler();
    }
  else if(action == TRAY_UNPAUSE)
    {
      show_notification("Hello, I'm back", "Resumed");
      resume_notification_handler();
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
      if(CMP_ARG(argv[i],"-t"))
        title = i+1 < argc ? argv[i+1] : title;
      else if (CMP_ARG(argv[i],"-b"))
        body = i+1 < argc ? argv[i+1] : body;
      else if (CMP_ARG(argv[i],"-p"))
        period = CHECK_ZERO((atoi(argv[i+1]) * MINS),period);
      else if (CMP_ARG(argv[i],"-d"))
        duration = atoi(argv[i+1]) * HOURS;
      else if (CMP_ARG(argv[i],"-h"))
        {
          help_screen();
          exit(EXIT_SUCCESS);
        }
    }

  if(!duration) // if it's zero make it infinity
    duration = INF;

  daemonize();

  //recieve Terminate signals from kill
  signal(SIGINT, signal_callback);
  signal(SIGTERM, signal_callback);
    

  //Intializing gtk
  gtk_init(&argc, &argv);
  gtk_window_set_default_icon_name (APP_LOGO);
    
  init_notification();
  init_notification_handler();

  add_new_notification(title, body, period, duration);

  intiate_tray_icon(title,system_tray_callback);
    
  gtk_main();
  uninit_notification();
  uninit_notification_handler();
}
