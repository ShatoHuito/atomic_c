#include "thread.h"

/*
    10 потоков пишут, 10 потоков читают
    значения atomic_char/atomic_int всегда будут одинаковыми и корректными (10 потоков итерируют 10000 раз значение
    на выходи получаем значение 100000)
    значения gInt и gChar всегда будут не определенного значения
*/

int gInt = 0;
char gChar = 0;
atomic_char aChar = 0;
atomic_int aInt = 0;
int flag_thread_finish = 0;


void writeData()
{
    long i = 0;

    while (i < 10000)
    {
        gChar++;
        gInt++;
        atomic_fetch_add_explicit(&aInt, 1, memory_order_relaxed);
        atomic_fetch_add_explicit(&aChar, 1, memory_order_relaxed);
        i++;
    }
    flag_thread_finish++;
}

void readData()
{
    printf("usual int = %d\n", gInt);
    printf("atomic int = %d\n", atomic_load(&aInt));
    printf("------------------------------\n");

    flag_thread_finish++;
}


t_thread *thread_inicial(int threads_count)
{
    t_thread *thread;

    thread = malloc(sizeof (t_thread) * threads_count);
    if(!thread)
        return (NULL);
    return thread;
}


int main() {
    t_thread *threads;
    int thr_count = 20;
    int i = 0;

    threads = thread_inicial(thr_count);
    while(i < thr_count)
    {
        if(i % 2 == 0) {
            if (pthread_create(&threads[i].thr, NULL, (void *(*)(void *)) writeData, (void *) &threads[i]))
                return 1;
            if (pthread_detach(threads[i].thr))
                return 1;
            i++;
        } else{
            if (pthread_create(&threads[i].thr, NULL, (void *(*)(void *)) readData, (void *) &threads[i]))
                return 1;
            if (pthread_detach(threads[i].thr))
                return 1;
            i++;
        }
    }
    while (flag_thread_finish != thr_count)
        sleep(1);
    printf("usualInt ---- %d\n", gInt);
    printf("usualChar ---- %d\n", gChar);
    printf("atomicInt ---- %d\n", atomic_load(&aInt));
    printf("atomicChar ---- %d\n", atomic_load(&aChar));
    printf("------------------------\n");

    return 0;
}

