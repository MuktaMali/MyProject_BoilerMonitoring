#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ipc.h"
#include "controller.h"
#include "sensors.h"
#include "logger.h"
#include "signal_handler.h"

int main()
{
    pid_t pid;

    init_pipe();
    init_shared_memory();
    init_logger();
    setup_signal();

    pid = fork();

    if(pid < 0)
    {
        perror("Fork Failed");
        return 1;
    }

    if(pid == 0)
    {
        printf("Sensor process started\n");
        start_sensors();
    }
    else
    {
        printf("Boiler controller started\n");
        start_controller();

        waitpid(pid,NULL,0);
    }

    return 0;
}
