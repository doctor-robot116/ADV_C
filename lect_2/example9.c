/*
 * example9.c
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
    int len = strlen("Hello");
    char* str1 = malloc(len + 1);
    strcpy(str1, "Hello");
    char* str2 = malloc(len + 1);
    strcpy(str2, "Hello");
    if (str1 == str2)
    {
        printf("Strings are equal\n");
    }
    else
    {
        printf("Strings are NOT equal\n");
    }
    if (strcmp(str1,str2) == 0)
    {
        printf("Strings are equal\n");
    }
    return 0;
}

