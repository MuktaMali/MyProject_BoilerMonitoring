#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "ipc.h"

int pipe_fd[2];

int shmid;
int *shared_data;

void init_pipe()
{
    if(pipe(pipe_fd) == -1)
    {
        perror("Pipe failed");
    }
}

void init_shared_memory()
{
    shmid = shmget(1234, sizeof(int)*4, 0666 | IPC_CREAT);

    if(shmid < 0)
    {
        perror("Shared memory error");
    }

    shared_data = (int*) shmat(shmid,NULL,0);
}

void cleanup_shared_memory()
{
    shmdt(shared_data);
    shmctl(shmid,IPC_RMID,NULL);
}
