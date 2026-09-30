#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 

//Cerinta:
//
//Avem mai multe thread-uri care impart acelasi lacat.
//Toate lucreaza cu un cont bancar. Contul bancar nu are voie sa aiba niciodata
//balanta mai mica de 0.
//
//Thread_1_3 vrea sa scoata bani.
//Daca acesta nu poate sa scoata bani(din cauza ca balanta e prea mica), va astepta pana cand se depoziteaza bani
//
//Thread_2_4 se ocupa de functia de depozit.
//Acesta trebuie sa introduca bani cand este nevoie.

//Se vor primi ca argumente: Lacatul, variabila conditionala si balanta contului
//(toate argumentele sunt comune intre thread-uri, adica exista doar o variabila
//care tine toate argumentele astea in main)

#define WITHDRAW_AMOUNT 4
#define DEPOSIT_AMOUNT 6
typedef struct ArgFunc
{
    pthread_mutex_t* lacat;
    pthread_cond_t* conditie;
    int balanta;

}ArgFunc;

void* withdraw_func(void* arg)
{
    ArgFunc* argumente = (ArgFunc*)arg;
   
    usleep(1000);
    pthread_mutex_lock(argumente -> lacat); //thread-ul care vrea sa faca withdraw
                                            //incearca sa intre in zona critica de
                                            //withdraw
    while(argumente -> balanta < WITHDRAW_AMOUNT)
    {
        printf("Sunt THREAD si astept sa se depoziteze bani ca sa fac withdraw\n");
        pthread_cond_wait(argumente -> conditie, argumente -> lacat);
    }

    if(argumente -> balanta >= WITHDRAW_AMOUNT)
    {
        argumente -> balanta -= WITHDRAW_AMOUNT;
        printf("Sunt THREAD si am scos %d bani din balanta. Mai sunt in balanta %d bani\n", WITHDRAW_AMOUNT, argumente -> balanta);
    }

    pthread_mutex_unlock(argumente -> lacat);
    return NULL;
}

void* deposit_func(void* arg)
{
    ArgFunc* argumente = (ArgFunc*)arg;

    usleep(1000);
    pthread_mutex_lock(argumente -> lacat);
    printf("Sunt THREAD si am intrat sa depozitez %d bani in contul in care sunt acum %d bani\n", DEPOSIT_AMOUNT, argumente -> balanta);

    argumente -> balanta += DEPOSIT_AMOUNT;
    if(argumente -> balanta >= 2 * WITHDRAW_AMOUNT)
        pthread_cond_broadcast(argumente -> conditie); //daca balanta e mult mai mare inseamna ca pot sa scoata mai multe thread-uri daca e nevoie
    else if(argumente -> balanta >= WITHDRAW_AMOUNT)
        pthread_cond_signal(argumente -> conditie);

    pthread_mutex_unlock(argumente -> lacat);

    return NULL;    
}

int main()
{
    pthread_mutex_t lacat = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t conditie = PTHREAD_COND_INITIALIZER;
    
    ArgFunc argumente;
    argumente.lacat = &lacat;
    argumente.conditie = &conditie;
    argumente.balanta = 2;

    pthread_t threads[7];

    for(unsigned short i = 0; i < 7; ++i)
        if(i == 0 || i == 3 || i == 4)
            pthread_create(&threads[i], NULL, withdraw_func, &argumente);
        else
            pthread_create(&threads[i], NULL, deposit_func, &argumente);
    for(unsigned short i = 0; i < 7; ++i)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lacat);
    pthread_cond_destroy(&conditie);
    return 0;
}
