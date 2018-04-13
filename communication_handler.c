#include "communication_handler.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "log.h"

#define FOCUS_PIPE "/tmp/focus"
#define CMD_SIZE  sizeof(char)

int fd;
int dump_fd;
int init_communication()
{
    if(mkfifo(FOCUS_PIPE,S_IRUSR | S_IWUSR) == -1)
    {
	if(errno != EEXIST)
	{
	    logerr("Error making fifo");
	    return -1;
	}
    }
    
    fd = open(FOCUS_PIPE,O_RDONLY);
    if(fd == -1)
    {
	logerr("Error opening fifo");
	return fd;
    }
    dump_fd = open(FOCUS_PIPE,O_WRONLY); // to never see EOF
    return 0;  
}

cmd_t read_cmd()
{
    char cmd;
    
    if(read(fd,&cmd,CMD_SIZE) == -1)
    {
	logerr("Error reading cmd");
	return -1;
    }
    return cmd;
}

char * read_text()
{
    int len;
    char *t;
    read(fd,&len,sizeof(int));
    t = malloc(len+1);
    read(fd,t,len);
    t[len] = '\0';
    return t;
}

int read_num()
{
    int t;
    read(fd,&t,sizeof(int));
    return t;
}

int send_notification(char *title,char * body, int period, int duration)
{
    int fd;
    fd = open(FOCUS_PIPE,O_WRONLY);

    if(fd == -1)
    {
	logerr("Can't opened fifo for write");
	return fd;
    }

    int data = CMD_ADD;
    write(fd, &data,sizeof(cmd_t));

    data= strlen(title);
    write(fd, &data,sizeof(int));
    write(fd, title, strlen(title));

    data= strlen(body);
    write(fd, &data, sizeof(int));
    write(fd, body, strlen(body));

    write(fd, &period, sizeof(int));
    write(fd, &duration, sizeof(int));

    close(fd);
    return 0;
}
