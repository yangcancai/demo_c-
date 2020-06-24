//
// Created by Administrator on 2020/6/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>

typedef struct thread_str{
    int rs;
}thread_str;
int g_tickets = 100;
int g_num = 100;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex_num = PTHREAD_MUTEX_INITIALIZER;
void sell_num(int thread){
    pthread_mutex_lock(&g_mutex_num);
    if (g_num > 0)
        printf("thread%d sell num:%d\n", thread, g_num--);
    pthread_mutex_unlock(&g_mutex_num);
    return;
}
void* thread_proc1(void* arg)
{
    auto* pthread = static_cast<thread_str*>(arg);
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        usleep(10);
        sell_num(1);
        if (g_tickets > 0)
            printf("thread 1 sell tickets:%d\n", g_tickets--);
        else
        {
            pthread_mutex_unlock(&g_mutex);
            break;
        }
        pthread_mutex_unlock(&g_mutex);
    }
    pthread->rs = 1;
    pthread_exit(pthread);
}

void* thread_proc2(void* arg)
{
    auto* pthread = static_cast<thread_str*>(arg);
    while (1)
    {
        pthread_mutex_lock(&g_mutex_num);
        pthread_mutex_lock(&g_mutex);
        if (g_tickets > 0)
            printf("thread 2 sell tickets:%d\n", g_tickets--);
        else
        {
            pthread_mutex_unlock(&g_mutex);
            if (g_num > 0)
                printf("thread%d sell num:%d\n", 2, g_num--);
            pthread_mutex_unlock(&g_mutex_num);
            break;
        }
        pthread_mutex_unlock(&g_mutex);
        if (g_num > 0)
            printf("thread%d sell num:%d\n", 2, g_num--);
        pthread_mutex_unlock(&g_mutex_num);
    }
    pthread->rs = 2;
    pthread_exit(pthread);
}


int main(int argc, char*argv[])
{
    pthread_t tid1, tid2;
    void *ret1, *ret2;
    thread_str t1,t2;
    pthread_create(&tid1, NULL, thread_proc1, &t1);
    pthread_create(&tid2, NULL, thread_proc2, &t2);
    pthread_join(tid1, &ret1);
    pthread_join(tid2, &ret2);
    printf("ret1:%d\n", static_cast<thread_str*>(ret1)->rs);
    printf("ret2:%d\n", static_cast<thread_str*>(ret2)->rs);
    getchar();
    return 0;
}
