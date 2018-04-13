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
#include "log.h"
#include "communication_handler.h"


#define CHECK_ZERO(A,B)   A > 0? A:B
#define CMP_ARG(A,B)  !strncmp(A,B,2)
#define MINS 60
#define HOURS 60 * MINS
#define INF INT_MAX

unsigned int period = 10 * MINS;
unsigned int duration = 0;
char *body= "Focus!";
char *title = "Remember!";

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
  uninit_notification_handler();
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

  if (argc < 2) // checking if no arguments sent
    {
      printf("Default mode\n");
      help_screen();
    }
  
    
  int i,service =0;
	
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
      else if(CMP_ARG(argv[i],"-s"))
      {
	  service = 1;
	  logdbg("-S arguemnt found");
      }
    }

  

  if(service)
  {
      logdbg("Started as a service");
      //recieve Terminate signals from kill
      signal(SIGINT, signal_callback);
      signal(SIGTERM, signal_callback);
    

      //Intializing gtk
      gtk_init(&argc, &argv);
      gtk_window_set_default_icon_name (APP_LOGO);

  
      intiate_tray_icon(title,system_tray_callback);

      
      init_notification();
      init_notification_handler();

      if(init_communication() == -1)
      {
	  logerr("Error init communication");
	  close_program(EXIT_FAILURE);
      }
      while(1) //serve forever
      {
	  int cmd = read_cmd();
	  logdbg("CMD recieved %d",cmd);
	  switch(cmd)
	  {
	  case CMD_ADD:
	      title = read_text();
	      body = read_text();
	      period = read_num();
	      duration = read_num();
	      logdbg("recieved notification : %s , %s , %d , %d",
		     title,body,period,duration);
	      add_new_notification(title, body, period, duration);
	      break;
	  default:
	      logerr("Wrong cmd recieved");
	      break;
	  }
      }
  }
  else
  {
      if(!duration) // if it's zero make it infinity
	  duration = INF;

      printf("%s , %s, %d, %d \n" , title, body,period,duration);
      send_notification(title,body,period,duration);
  }
}
