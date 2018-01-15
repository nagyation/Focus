#include "focus_notifyhandler.h"
#include "focus_notify.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "log.h"
#include "string.h"

void _notification_handler(int);
void update_period_list(int time);
int get_min_period();


struct notification_node{
    struct notification_data * notify_data;
    struct notification_node * next;
};


struct notification_node * head = NULL;



void init_notification_handler()
{
    signal(SIGALRM, _notification_handler);
}

struct notification_data * new_notification_data(char * title,
						 char * body, int period, int duration)
{
    struct notification_data * d = malloc(sizeof(struct notification_data));
    d->title = title;
    d->body = body;
    d->period = period;
    d->duration = duration;
    return d;
}

void add_new_notification(struct notification_data* data)
{
    struct notification_node *t = malloc(sizeof(struct notification_node));
    t->notify_data = data;
    t->next = head;
    t->notify_data->cperiod =0;
    print_log("Adding New notification\n");
    update_period_list(alarm(0)); //get the last alarm duration took
    head = t;
    print_log("Getting min period and setting alarm\n");
    printf("Min period is %d\n", get_min_period());
    alarm(get_min_period()); // set the new alarm with the min period
}

void remove_notification(struct notification_node *p)
{
    struct notification_node *t;
    char ex[] = " -- Finished";

    if(p == head)
	t = p;
    else
	t = p->next;
  
    char *title = malloc(strlen(t->notify_data->title) + strlen(ex) + 1);
    strcpy(title,t->notify_data->title);
    printf("%s\n",title);
    strcat(title,ex);
    printf("%s\n",title);
    show_notification(title,t->notify_data->body);
    printf("Exited\n");
    
    if(p == head)
	head =NULL;
    else
	p->next = p->next->next;
    free(t);
}

void update_period_list(int time)
{

    struct notification_node *trail,*t = head;
    trail = head;
    while(t !=NULL)
    {
	t->notify_data->duration -= time;
	printf("time spent in alarm is %d\n", time);
	t->notify_data->cperiod +=time;
	printf("cperiod = %d\n",t->notify_data->cperiod);
	if(t->notify_data->cperiod
	   >=
	   t->notify_data->period)
	{
	    show_notification(t->notify_data->title,
			      t->notify_data->body);
	    t->notify_data->cperiod = 0;
	}
	printf("Duration left %d \n",t->notify_data->duration);
	if(!t->notify_data->duration)
	    remove_notification(trail);
	
	trail =t;
	t = t->next;
    }
}

int get_min_period()
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
    printf("%d\n",head->notify_data->period);
    return min_period;
}

void _notification_handler(int signal)
{
    update_period_list(get_min_period());
    alarm(get_min_period());
}

