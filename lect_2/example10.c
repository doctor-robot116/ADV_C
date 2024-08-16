/*
 * example10.c
 *
 */


#include <stdio.h>

void print_array(int a[5])
{
    /* ОШИБКА!    Размер массива теряется */
    for(int i=0; i<sizeof(a)/sizeof(int); i++)
        printf("a[%d]=%d ",i,a[i]);
}

int main(void) {
    int a[5] = {1,2,3,4,5};
    print_array(a);
    return 0;
}

