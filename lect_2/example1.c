/*
 * example1.c
 */


#include <stdio.h>

int main(void)
{
    float f = 2.0;
    int *p;
    p = (int*)&f; //добавили (int*) - приведение к типу
    printf("*p = %x\n", *p);
    *p = (127+3)<<23; //кладем в f 2^3
    printf("f = %f\n", f);
    return 0;
}

