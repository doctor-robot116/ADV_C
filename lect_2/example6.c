/*
 * example6.c
 * Пример реализации функции strcpy
 */

#include <stdio.h>

char *strcpy(char *dst, const char *src )
{
    char *d = dst;
    while ((*dst++ = *src++));
    return d;
}

int main()
{
    char a[]="Hello!", b[7];
    strcpy(b,a);
    printf("b = %s\n",b);
    return 0;
}



