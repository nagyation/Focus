#ifndef  __FOCUS_COMMUNICATION_HANDLER__
#define  __FOCUS_COMMUNICATION_HANDLER__


#define CMD_ADD 0

typedef unsigned char cmd_t;

int init_communication();
cmd_t read_cmd();
char * read_text();
int read_num();
int send_notification(char *, char *, int, int);

#endif
