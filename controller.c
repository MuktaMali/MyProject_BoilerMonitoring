#include <stdio.h>
#include <unistd.h>
#include "ipc.h"
#include "logger.h"

void start_controller()
{
    int data[4];

    while(1)
    {
        read(pipe_fd[0],data,sizeof(data));

        printf("Temp:%d  Pressure:%d  Water:%d  Gas:%d\n",
               data[0],data[1],data[2],data[3]);

        log_event("Sensor data received");

        if(data[1] > 180)
        {
            printf("WARNING: High Pressure!\n");
            log_event("High pressure detected");
        }

        if(data[0] > 110)
        {
            printf("WARNING: Temperature Critical!\n");
            log_event("Temperature critical");
        }

        if(data[2] < 20)
        {
            printf("WARNING: Water Level Low!\n");
            log_event("Low water level");
        }

        if(data[3] > 3)
        {
            printf("WARNING: Gas Leak!\n");
            log_event("Gas leak detected");
        }
    }
}
