#include "notification_handler.h"
#include "notification.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "log.h"
#include "string.h"

void _notification_handler(int);
void _update_period_list(int time);
int _get_min_period();
void _free_list();

struct notification_data{
    char * title;
    char * body;
    int duration;
    int period;
    int cperiod;
};

struct notification_node{
  struct notification_data * notify_data;
  struct notification_node * next;
};


struct notification_node * head = NULL;

int last_period;

void init_notification_handler()
{
  last_period =0;
  signal(SIGALRM, _notification_handler);
}

void add_new_notification(char * title, char * body,
                          int period, int duration)
{
  struct notification_node *t = malloc(sizeof(struct notification_node));
  t->notify_data = &(struct notification_data) {
    .title = title,
    .body = body,
    .period = period,
    .duration = duration
  };
  t->next = head;
  t->notify_data->cperiod =0;
  loginfo("Adding New notification\n");
  _update_period_list(alarm(0)); //get the last alarm duration took
  head = t;
  logdbg("Min period is %d\n", _get_min_period());
  alarm(_get_min_period()); // set the new alarm with the min period
}

void pause_notification_handler()
{
  last_period = alarm(0); // save the last_period and pause
}

void resume_notification_handler()
{
  if(!last_period)
    alarm(last_period);
}

void uninit_notification_handler()
{
  _free_list();
}

void _free_list()
{
  struct notification_node *tmp;
  while(head != NULL)
    {
      tmp = head;
      head = head->next;
      free(tmp);
    }
  
}
void _remove_notification(struct notification_node *p)
{
  struct notification_node *t;
  char ex[] = " -- Finished";

  if(p == head)
    t = p;
  else
    t = p->next;
  
  char *title = malloc(strlen(t->notify_data->title) + strlen(ex) + 1);
  strcpy(title,t->notify_data->title);
  strcat(title,ex);
  show_notification(title,t->notify_data->body);
  loginfo("Stopped Task\n");
    
  if(p == head)
    head =NULL;
  else
    p->next = p->next->next;
  free(t);
  free(title);
}

void _update_period_list(int time)
{

  struct notification_node *trail,*t = head;
  trail = head;
  while(t !=NULL)
    {
      t->notify_data->duration -= time;
      loginfo("time spent in alarm is %d\n", time);
      t->notify_data->cperiod +=time;
      logdbg("cperiod = %d\n",t->notify_data->cperiod);
      if(t->notify_data->cperiod
         >=
         t->notify_data->period)
        {
          show_notification(t->notify_data->title,
                            t->notify_data->body);
          t->notify_data->cperiod = 0;
        }
      logdbg("Duration left %d \n",t->notify_data->duration);
      if(!t->notify_data->duration)
        _remove_notification(trail);
	
      trail =t;
      t = t->next;
    }
}

int _get_min_period()
{
  if(!head)
    return 0;
  struct notification_node *t = head;
  int min_period = head->notify_data->period;
  while(t !=NULL)
    {
      if(min_period >= t->notify_data->period)
        min_period =
          t->notify_data->period < t->notify_data->duration? t->notify_data->period : t->notify_data->duration;
      t = t->next;
    }
  return min_period;
}

void _notification_handler(int signal)
{
  _update_period_list(_get_min_period());
  alarm(_get_min_period());
}

