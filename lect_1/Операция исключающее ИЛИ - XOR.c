
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int find_odd_element(int32_t arr[], size_t n)
{
    int32_t res = 0;
    for (size_t i = 0; i < n; i++)
        res ^= arr[i];
    return res;
}
int main(void)
{
    int32_t arr[] = {17, 17, 24, 97, 24, 24, 24};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    printf("The element is %" PRId32, find_odd_element(arr, n));
    return 0;
}
