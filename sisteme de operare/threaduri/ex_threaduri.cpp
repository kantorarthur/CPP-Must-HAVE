#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

//vrem sa primim returnat un argthread
//vrem sa dam ca parametru functiei un string care sa fie in nume
//vrem sa dam ca parametru si un array cu care sa se faca
//arr[i] dat ca parametru + i iar asta sa fie in argthread returnat

typedef struct ArgThread
{
    int arr[30];
    char nume[50] = "\0";
    size_t size_of_arr = 30;
};

void* threadFnc(void* argg)
{
    ArgThread* returnul = (ArgThread*)malloc(sizeof(ArgThread));
    ArgThread* arg = (ArgThread*)argg;

    strcat(returnul -> nume, arg -> nume);
    for(size_t i = 0; i < arg -> size_of_arr; ++i)
        returnul -> arr[i] = i + arg -> arr[i];
    return (void*)(ArgThread*)returnul;
}

int main()
{
    ArgThread arg;
    pthread_t thread1 = -1;
    
    for(size_t i{}; i < arg.size_of_arr; ++i)
        arg.arr[i] = 2;
    strcat(arg.nume, "alin");

    pthread_create(&thread1, NULL, threadFnc, &arg); 

    void* prind_return;
    pthread_join(thread1, &prind_return);

    ArgThread* return_convertit = (ArgThread*)prind_return;
    return_convertit -> size_of_arr = 30;

    printf("Numele returnat este: %s\nIar array-ul:\n", return_convertit -> nume);
    for(size_t i = 0; i < return_convertit -> size_of_arr; ++i)
        printf("%d ", return_convertit -> arr[i]);

    free(prind_return);
    return 0;
}
