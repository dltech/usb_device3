#include <stdio.h>
#include <stdlib.h>
#include "../../tl_replacement/lib/display.h"

int main()
{
    uint32_t mv[3];
    dsprintf(mv,"eee");
    printf("%x %x %x\n", mv[0], mv[1], mv[2]);
    return 0;
}
