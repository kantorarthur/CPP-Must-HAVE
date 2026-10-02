#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

//Clientul trebuie sa citeasca informatia din memoria partajata
//Sa o incrementeze cu 1 si dupa sa scrie noua informatie in memoria partajata



int main()
{
    int fd = -1;

    fd = shm_open("/mem_partajata", O_RDWR | O_CREAT, 0600);

    volatile int* memorie_partajata = (volatile int*)mmap(0, sizeof(int),
                                                            PROT_READ
                                                            | PROT_WRITE
                                                            | PROT_EXEC
                                                            , MAP_SHARED
                                                            , fd
                                                            , 0);
    if(memorie_partajata == (void*)-1)
    {
        perror("Nu s-a putut mapa memoria");
        return -1;
    }

    *memorie_partajata += 1;
    printf("Sunt client si am modificat informatia din memoria partajata\n");
    //Acum am modificat informatia din adresa cu +1

    shm_unlink("/mem_partajata");
    close(fd);
    memorie_partajata = NULL;
    return 0;
}
