/*
 * example4.c
 *Пример со специальным типом void
 */


#include <stdio.h>

_Bool is_same(void *a, void *b) {
    // *a = *b; // ОШИБКА! void * нельзя разыменовывать
    return a == b; // Можно только сравнивать
}
int main()
{
    int a=5;
    int *pa = &a;
    is_same(&a, pa) ? printf("Same\n") : printf("Different\n");
   
    printf("is_same(&a, pa) = %d\n", is_same(&a, pa)); 
    return 0;
}
