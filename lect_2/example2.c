/*
 *example2.c
 */


#include <stdio.h>

int main(int argc, char **argv)
{
    //1ый пример
    int *p = NULL; // 0 -  не указывает ни на что
    /*ОШИБКА! попытка разыменовать нулевой указатель */
    //if( *p )
    if(p && *p) //правильно - ленивая логика
        printf("True\n");
    return 0;
}

