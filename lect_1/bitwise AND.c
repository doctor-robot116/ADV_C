#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
int main(void)
{
    int32_t x = 17;
    (x & 1) ? printf("Odd") : printf("Even");
}