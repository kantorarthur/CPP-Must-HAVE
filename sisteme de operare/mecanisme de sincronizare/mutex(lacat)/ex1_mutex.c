#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
//vrem sa scriem un program care porneste 4 thread-uri
//care executa aceeasi functie
//in fiecare thread avem o regiune comuna care se poate executa
//in paralel, respectiv o regiune critica
//care nu are voie sa se execute in paralel
//in ambele regiuni se va apela sleep(1)


void* thread_fnc(void* arg)
{
    pthread_mutex_t* lock = (pthread_mutex_t*)arg;
    
    //regiunea comuna
    //toate threadurile intra de odata si dorm o secunda de la sec 0 -> sec 1
    sleep(1);
    pthread_mutex_lock(lock);
    //regiunea critica
    //aici va intra pe rand: thread1 doarme o sec de la sec 1 -> sec 2
    sleep(1);
    pthread_mutex_unlock(lock);
    //acum thread 1 da drumu la mutex, intra thread2 doarme 1 sec de la
    //                                              sec 2 -> sec 3 si tot asa
    return NULL;
}

int main()
{
    pthread_t pids[4];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    for(int i = 0; i < 4; ++i)
        pthread_create(&pids[i], NULL, thread_fnc, &lock);
    for(int i = 0; i < 4; ++i)
        pthread_join(pids[i], NULL);
    
    pthread_mutex_destroy(&lock);
    return 0;
    
}




