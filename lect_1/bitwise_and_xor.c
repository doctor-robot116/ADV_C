#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
    uint32_t a = 60; /* 60 = 0011 1100 */
    uint32_t b = 13; /* 13 = 0000 1101 */
    int32_t c = 0;
    c = a & b; /* 12 = 0000 1100 */
    printf("Line 1 c = %d\n", c);
    c = a | b; /* 61 = 0011 1101 */
    printf("Line 2 c = %d\n", c);
    c = a ^ b; /* 49 = 0011 0001 */
    printf("Line 3 c = %d\n", c);
    c = ~a; /*-61 = 1100 0011 */
    printf("Line 4 c = %d\n", c);
    c = a << 2; /* 240 = 1111 0000 */
    printf("Line 5 c = %d\n", c);
    c = a >> 2; /* 15 = 0000 1111 */
    printf("Line 6 c = %d\n", c);
    return 0;
}