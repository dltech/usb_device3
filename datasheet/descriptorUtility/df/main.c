#include <stdio.h>
#include <stdlib.h>
#include "inttypes.h"

#define DELAYCLKS   100000
#define SOUNDMAX    16

void init4811(uint8_t volume);
void setVolume(uint8_t volume);
void delay4811(void);
void upDn(uint8_t n, uint8_t up);

int main()
{
init4811(8);
    return 0;
}
volatile uint8_t volumeGl = 0;




void delay4811()
{
    volatile uint32_t cnt = DELAYCLKS;
    while(cnt-- > 0);
}

void upDn(uint8_t n, uint8_t up)
{
    if(n > SOUNDMAX) n = SOUNDMAX;

    if( up ) {
        printf("-");
    } else {
        printf("_");
    }
    for(uint8_t i=0 ; i<n; ++i) {
        printf("a");
        delay4811();
        printf("A");
        delay4811();
    }
    printf("_a");
}


void init4811(uint8_t volume)
{
    printf("_a");
    volumeGl = 16;
    setVolume(0);
    volumeGl = 0;
    setVolume(volume);
}


void setVolume(uint8_t volume)
{
    if(volume == volumeGl) return;

    if(volumeGl < volume) {
        upDn(volume - volumeGl, 1);
    } else {
        upDn(volumeGl - volume, 0);
    }
}
