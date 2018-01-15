#ifndef __FOCUS_LOG__
#define __FOCUS_LOG__

#include <stdio.h>

void print_log(char *text)
{
    FILE *f = fopen("/home/nagy/workspace/Focus/log.txt","a");
    fprintf(f,text);
    fclose(f);
}

#endif
