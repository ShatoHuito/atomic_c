//
// Created by Golduck Brittany on 12/14/21.
//

#ifndef UNTITLED_THREAD_H
#define UNTITLED_THREAD_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_thread
{
    pthread_t thr;
}               t_thread;


#endif //UNTITLED_THREAD_H
