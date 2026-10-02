#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


//O sa fac un exemplu foarte trivial:
//
//Serverul creeaza memoria partajata si scrie ceva in ea
//DUpa ce serverul face asta, asteapta o modificare a memoriei partajate
//Dupa ce s-a intamplat o modificare, serverul afiseaza modificarea si 
//dezaloca memoria si isi termina executia

//Clientul citeste informatia scrisa de server in memoria partajata
//Incrementeaza valoarea cu 1 si o scrie in memoria partajata





int main()
{
    int fd = -1;

    fd = shm_open("/mem_partajata", O_RDWR | O_CREAT, 0600);
    if(fd < 0)
    {
        perror("Nu s-a putut creea memoria partajata!");
        return -1;
    }
    
    //Vreau sa scriu un int in memoria partajata, deci o sa ii atribui
    //marime cat pentru un int
    
    ftruncate(fd, sizeof(int));

    volatile int* shared_memory = (volatile int*)mmap(0, sizeof(int), PROT_READ
                                                  | PROT_WRITE
                                                  | PROT_EXEC
                                                  , MAP_SHARED
                                                  , fd
                                                  , 0);
    //Acum am luat adresa de memorie partajata. Voi scrie in ea
    
    if(shared_memory == (void*)-1)
    {
        perror("Nu am putut mapa memoria");
        return -1;
    }
    *shared_memory = 4;//Acum in memoria partajata se afla informatia "int 4".

    while(*shared_memory == 4)
    {
        printf("In memoria partajata se afla: %d. Sunt server si astept sa fie modificate datele din memoria partajata\n", *shared_memory);
        sleep(3);
    } //acum asteptam pana cand client modifica memoria partajata
      
    printf("Sunt server. Datele din memoria partajata au fost modificata. Valoarea ce se afla la adresa de memorie partajata acum este %d\n", *shared_memory);

    munmap((void*)shared_memory, sizeof(int));
    shared_memory = NULL;
    close(fd);
    shm_unlink("/memorie_partajata");
    return 0;
}
