#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "trading_pipe"

typedef struct Pair
{
    float asking_price;
    unsigned int desired_quantity;
}Pair;

int main()
{
    int fd = -1;

    fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1)
    {
        perror("Couldn't open the FIFO pipe");
        return -1;
    }

    Pair instrument_arguments;

    ssize_t read_bytes = read(fd, &instrument_arguments, sizeof instrument_arguments);
    if(read_bytes == -1)
    {
        perror("Couldn't read from FIFO");
        return -1;
    }
    else if(read_bytes != sizeof instrument_arguments)
    {
        perror("Incomplete pair received");
        return -1;
    }
    close(fd);


    const float current_price = instrument_arguments.asking_price - 1.0f;
    const unsigned int quantity_in_stock_at_asking_price = 30;

    if(instrument_arguments.asking_price >= current_price)
    {
        if(quantity_in_stock_at_asking_price >= instrument_arguments.desired_quantity)
        {//... buy the instrument
            printf("Completed the order! Bought %d shares at %f price each", instrument_arguments.desired_quantity,
                                                                             instrument_arguments.asking_price);
            return 0;
        }
        else if(quantity_in_stock_at_asking_price > 0)
        { //... complete partial order
            printf("Completed partial order. Bought %d shares at %f price each", instrument_arguments.desired_quantity,
                                                                                instrument_arguments.asking_price);
            return 0;
        }
        else
        {
            printf("There are no shares of the instrument at the desired price at the moment");
            return 0;
        }
    }
    else 
    {
        printf("Current price of the instrument is greater than the asking price");
        return 0;
    }
    free(&instrument_arguments);
    return 0;
}
