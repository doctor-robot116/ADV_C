#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
    uint8_t u = 0xF5; //беззнаковый тип  0b1111 0101
    // u = u >> 1;
    u >>= 1; //сдвиг вправо на 1 бит        
    printf("u = %" PRIx8 "\n", u);    //   0b0111 1010(1)

    int8_t u1 = 0xF5; //знаковый тип        0b1111 0101
    u1 >>= 1; //сдвиг вправо на 1 бит
    printf("u = %" PRIx8 "\n", u1);  //   0b1111 1010

}