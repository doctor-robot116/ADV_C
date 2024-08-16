/*
 *example3.c
 */


#include <stdio.h>

int main(int argc, char **argv)
{
    //2-ой пример
    /* Нет ошибки */
    int *p = NULL;
    if( p == &(*p) )
        printf("True\n");

    return 0;
}
