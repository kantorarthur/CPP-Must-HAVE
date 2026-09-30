#include <unistd.h>
#include <iostream>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();

    if(pid == -1)
    {
        std::cout << "Nu s-a putut creea copil!\n";
    }
    else if(pid == 0)
    {
        int32_t id_copil = getpid();
        int32_t id_parinte = getppid();
        std::cout << "Acum ruleaza procesul copil!\nID-ul meu este: "
                  << id_copil << "\nIar ID-ul parintelui meu este: "
                  << id_parinte << "\n\n";
    }
    else 
    {
        int32_t id_parinte_absolut = getpid();
        std::cout << "Acum parintele absolut ruleaza.\nID-ul meu este: "
                  << id_parinte_absolut << "\nCopilul pe care l-am creat"
                  " are ID-ul: " << pid << "\n\n";
    }
    return 0;
}
