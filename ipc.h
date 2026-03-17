#ifndef IPC_H
#define IPC_H

extern int pipe_fd[2];

extern int shmid;
extern int *shared_data;

void init_pipe();
void init_shared_memory();
void cleanup_shared_memory();

#endif
