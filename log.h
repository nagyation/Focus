#ifndef __FOCUS_LOG__
#define __FOCUS_LOG__

#include <syslog.h>

#define logerr( ...)  syslog(LOG_ERR | LOG_USER, __VA_ARGS__)
#define logwarn( ...) syslog(LOG_WARN | LOG_USER, __VA_ARGS__)
#define loginfo( ...) syslog(LOG_INFO | LOG_USER, __VA_ARGS__)
#define logdbg( ...)  syslog(LOG_DEBUG | LOG_USER, __VA_ARGS__)

#endif
