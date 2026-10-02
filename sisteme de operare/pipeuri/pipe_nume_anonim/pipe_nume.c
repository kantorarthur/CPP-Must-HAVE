#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
//WE ARE CONSIDERING THIS c FILE AS CLIENT(i'm gonna compile as client anyway)

//We have  a client and a server.

//Server is a market exchange.

//Client is a trader

//The client sends:
//buy_price, quantity

//buy_price - Desired price to buy the instrument
//quantity - Quantity of instruments he wants to buy at the desired price

//The server receives the data
//Checks if there is at least 1 instrument(in terms of quantity) at the desired price
//And if it is, he completes the order (or partially completes it, depending on how many there are in stock)
//
// (In a real scenario you would send the ID of the instrument too, but I
//  want to make an fast trivial example, without further implementation of
//  hashtables and stuff :) )

#define FIFO_NAME "trading_pipe"

typedef struct Pair
{
    float asking_price;
    unsigned int desired_quantity;
}Pair;

int main()
{
    int fd = -1;
    mkfifo(FIFO_NAME, 0700);
   // if(mkfifo(FIFO_NAME, 0700))
    //{
      //  perror("Couldn't create the FIFO Pipe");
        //return -1;
    //}
    fd = open(FIFO_NAME, O_RDWR);

    Pair* instrument_arguments = (Pair*)malloc(sizeof(Pair));
    instrument_arguments -> asking_price = 102.5f;
    instrument_arguments -> desired_quantity = 5;
    write(fd, (void*)instrument_arguments, sizeof(Pair));
    //Now we send the informations through the PIPE to the Server.
    close(fd);
    printf("Succesfully placed an order of the desired instrument at "
            "%f ask price and %d desired quantity.\n", instrument_arguments -> asking_price,
                                                      instrument_arguments -> desired_quantity);
    return 0;
}
