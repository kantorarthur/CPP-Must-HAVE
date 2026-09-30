#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = -1;
    open("ex.txt", O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
    //creez un fisier "ex.txt" in folderul curent cu permisiuni de
    //scriere, citire si executare pt utilizator
    fd = open("ex.txt", O_RDWR);
    //deschid fisierul creat cu permisiuni de scriere si citire
    //receptez id-ul fisierului prin variabila fd

    char text[30];
    strcpy(text, "salut. exemplu");
    write(fd, text, strlen(text));
    //scriu in fisier textul "salut, exemplu"
    close(fd);
}
