#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    uint32_t x{35}, y{100}, z{};
    //primul proces copil va face x * y, al 2-lea y - x
    
    pid_t pid1{-1}, pid2{-2};

    pid1 = fork();
    pid2 = fork();

    if(pid1 == 0)
    {
        srand(getpid());
        usleep(random() % 50000);

        z = x * y;
        exit(z);
    }
    if(pid2 == 0)
    {
        srand(getpid());
        usleep(random() % 50000);

        z = y - z;
        exit(z);
    }
    int32_t status_proces_1{}, status_proces_2{};

    waitpid(pid1, &status_proces_1, 0);
    waitpid(pid2, &status_proces_2, 0);

    std::cout << "Procesul 1 a facut x * y, rezultatul este: " << WEXITSTATUS(status_proces_1)
              << "\nProcesul 2 a facut y - x, rezultatul este: " << WEXITSTATUS(status_proces_2);

}
