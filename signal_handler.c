#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "logger.h"
#include "ipc.h"

void shutdown_handler(int sig)
{
    printf("\nEmergency Shutdown Triggered\n");

    log_event("System shutdown via signal");

    cleanup_shared_memory();
    close_logger();

    exit(0);
}

void setup_signal()
{
    signal(SIGINT,shutdown_handler);
}
