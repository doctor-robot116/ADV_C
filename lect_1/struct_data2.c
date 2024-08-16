/*Пример с ошибкой
*/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

struct date
{
    uint16_t day : 5;  // значение от 0 до 31 (в двоичной системе 31 - это 11111(т. е. 5 бит))
    uint8_t month : 4; // значение 0 до 15
    // uint16_t year;      //: 7 если ограничиться с 2000 по 2127
    uint16_t year; // если ограничиться с 2000 по 2127
};

int main()
{
    struct date dt = {31, 12, 2021};
    dt.month = 16;
    printf("Date is %u/%u/%u", dt.day, dt.month, dt.year);
    return 0;
}