#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
//vreau sa scrie doua threaduri in mod sincronizat intr-un fisier
//semaforul o sa fie dat argument functiei in struct
//pe langa sem o sa primeasca un string pe care trebuie sa-l scrie in fisier
//si inca un argument primit de functie o sa fie fd fisierului in care trb
//sa scrie
struct ThreadArg
{
    sem_t* semafor; 
    char string_de_scris[30];
    int fd;
};


void* threadFnc(void* arg)
{
    struct ThreadArg* argument_primit = (struct ThreadArg*)arg;
    
    sem_t* semafor_primit = argument_primit -> semafor;
    while(sem_wait(semafor_primit)) //cand sem_wait intra in zona critica returneaza 0 si nu mai e valid arg din while
    {
        printf("Sunt thread si astept sa intru in zona critica\n");
        fflush(stdout);
    }
    //aici s-a intrat in zona critica
    printf("Sunt thread si am intrat in zona critica. Yeey!\n");

    write(argument_primit -> fd, argument_primit -> string_de_scris, strlen(argument_primit -> string_de_scris));
    printf("Sunt thread si am scris %s in fisier\n", argument_primit -> string_de_scris);

    sem_post(semafor_primit);
    return 0;
}

int main()
{

    int fd = -1;
    open("ex_sem.txt", O_CREAT, 0644); //creez ex_sem.txt
    fd = open("ex_sem.txt", O_RDWR); //deschid ex_sem.txt cu write si read perm
    
    sem_t* semafor = sem_open("/semafor1", O_CREAT | O_EXCL, 0644, 1);

    pthread_t t1 = -1, t2 = -1;

    struct ThreadArg arg_t1;
    strcpy(arg_t1.string_de_scris, "sunt thread 1\n");
    arg_t1.fd = fd;
    arg_t1.semafor = semafor;

    struct ThreadArg arg_t2;
    strcpy(arg_t2.string_de_scris, "sunt thread 2\n");
    arg_t2.fd = fd;
    arg_t2.semafor = semafor;

    pthread_create(&t1, NULL, threadFnc, &arg_t1);
    pthread_create(&t2, NULL, threadFnc, &arg_t2);

    pthread_join(t2, NULL);
    pthread_join(t1, NULL);
    close(fd);
    sem_unlink("/semafor1");
    sem_close(semafor);

    return 0;

}
