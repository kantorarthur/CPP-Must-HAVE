#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  //  while(true)
    //{
//mentionare: puteam sa fac si cum cere cerinta cu citire de la tastatura
//si era mult mai simplu, asa citesc din linia de comanda
//de asemenea, nu prea pot sa fac cu while true daca citesc din linia de comanda
//daca citeam de la tastatura puteam sa fac cu while true
        if(argc != 4)
        {
            std::cout << "Nu ati transmis argumentele potrivite!";
            return -1;
        }

        pid_t pid{-1};
        pid = fork();

        //in argv[0] se afla numele fisierului, argv[1] primul numar, argv[2] al 2-lea
        //argv[3] tipul operatiei
        if(pid == 0)
            execl("./server", argv[0], argv[1], argv[2], argv[3], NULL);

        int32_t rezultat_operatie_server{};
        wait(&rezultat_operatie_server);
        std::cout << "Rezultatul operatiei efectuate de programul server este: "
            << WEXITSTATUS(rezultat_operatie_server) << '\n';
    //}

}
