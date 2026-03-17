#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "ipc.h"

pthread_mutex_t lock;

void* sensor_thread(void *arg)
{
    int id = *(int*)arg;

    while(1)
    {
        pthread_mutex_lock(&lock);

        int data[4];

        data[0] = rand()%50 + 70;    // temperature
        data[1] = rand()%100 + 100;  // pressure
        data[2] = rand()%100;        // water level
        data[3] = rand()%5;          // gas

        shared_data[0] = data[0];
        shared_data[1] = data[1];
        shared_data[2] = data[2];
        shared_data[3] = data[3];

        write(pipe_fd[1],data,sizeof(data));

        pthread_mutex_unlock(&lock);

        sleep(1);
    }
}

void start_sensors()
{
    pthread_t t1,t2,t3,t4;

    int id1=1,id2=2,id3=3,id4=4;

    srand(time(NULL));

    pthread_mutex_init(&lock,NULL);

    pthread_create(&t1,NULL,sensor_thread,&id1);
    pthread_create(&t2,NULL,sensor_thread,&id2);
    pthread_create(&t3,NULL,sensor_thread,&id3);
    pthread_create(&t4,NULL,sensor_thread,&id4);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
}
