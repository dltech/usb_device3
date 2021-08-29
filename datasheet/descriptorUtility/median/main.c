#include <stdio.h>
#include <stdlib.h>
#include "inttypes.h"

uint32_t median(uint32_t in);

int main()
{
    uint32_t n = 1;
    while( n > 0 )
    {
        scanf("%d",&n);
        printf("out %d\n",median(n));
    }
    printf("Hello world!\n");
    return 0;
}

uint32_t median(uint32_t in)
{
    #define size 3
    static uint32_t wind[size] = {0,0,0};

    for(int8_t i=size-1 ; i>=0 ; --i)
    {
        if( (in > wind[i]) ) {
            for(uint8_t j=0 ; j<i ; ++j) {
                wind[j] = wind[j+1];
            }
            wind[i] = in;
            break;
        } else if(i == 0) {
            for(uint8_t j=(size-1) ; j>0 ; --j) {
                wind[j] = wind[j-1];
            }
            wind[0] = in;
        }
    }
    return wind[size/2];
}
