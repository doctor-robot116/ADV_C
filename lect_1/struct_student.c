/*
Структуры. Провдвинутый Си.
 */

#include <stdio.h>
#include <stdint.h>


struct student {
    int id;
    char name[20];
    int group;
}
;
void func(struct student record)
{
    printf(" Id is: %d \n", record.id);
    printf(" Name is: %s \n", record.name);
    printf(" Group is: %d \n", record.group);
}

void pfunc(struct student *record)
{
    printf(" Id is: %d \n", record->id);
    printf(" Name is: %s \n", record->name);
    printf(" Group is: %d \n", record->group);
}

int main(void)
{
    struct student record = {1, "Vasiliy", 102};
    func(record);
    pfunc(&record);
    return 0;

}
