#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cout << "Numar gresit de argumente!";
        exit(-1);
    }

    if(strcmp(argv[3], "-") == 0)
        exit(atoi(argv[1]) - atoi(argv[2]));
    else if(strcmp(argv[3], "+") == 0)
        exit(atoi(argv[1]) + atoi(argv[2]));
    else
        exit(-1);
}
