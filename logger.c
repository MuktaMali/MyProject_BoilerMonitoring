#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "logger.h"

int log_fd;

void init_logger()
{
    log_fd = open("logs/boiler.log",O_CREAT|O_RDWR|O_APPEND,0644);
}

void log_event(const char *msg)
{
    write(log_fd,msg,strlen(msg));
    write(log_fd,"\n",1);
}

void close_logger()
{
    lseek(log_fd,0,SEEK_SET);
    close(log_fd);
}
