#include <stdio.h>

extern int *ar;

int main(void)
{
    ar[3] = 123;
    return 0;
}
