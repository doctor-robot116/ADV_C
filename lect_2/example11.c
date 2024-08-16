/*
 * example11.c
 *
 *
 */


#include <stdio.h>

void print_array(int a[], int size)
{
    /* Так можно */
    for( int i=0; i<size; i++ )
        printf("a[%d]=%d ",i,a[i]);
}

int main(void)
{
    int a[5] = {1,2,3,4,5};
    print_array(a, 5);
    /*  Так тоже можно */
    for(int i=0; i<sizeof(a)/sizeof(int); i++)
    {
        printf("a[%d]=%d ",i,a[i]);
    }
    return 0;
}


