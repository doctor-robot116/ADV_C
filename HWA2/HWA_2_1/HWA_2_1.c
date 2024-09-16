/*
 * �������� ������� �������������
 * HWA_2_1.c
 *
 * ������ 2-1-������������ ����
 *
 * ������� ��������� ������
 *
 * typedef struct list {
 *              void *address;
 *              size_t size;
 *              char comment[64];
 *              struct list *next;
 * } list;
 *
 * ��������� ����������� ������ ���� �������, ������� � ������ ������ ������� ����� ����� ������ ���������� ������ ����� �����.
 * ����� �������� � ���� address, ���� size - ��������������� ������ ������� �����. ���� ������ ������, �� ������� ������ ���������� NULL.
 * ���� ���� ��������� ����� ������, �� ������� ����� ������ �� ���.
 * �������� �������:
 * void * findMaxBlock(list *head)
 */



#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

// ����������� ��������� ��� �������� ���������� �� �������������� ������
typedef struct list
{
    void *address;  // ����� ����������� ����� ������
    size_t size;     // ������ ����������� ����� ������
    char comment[64]; // �����������, ����������� ���� ������
    struct list *next; // ��������� �� ��������� ������� ������
} list;

// ���������� ���������� ��� �������� ������ ���������� ������
list *memlist = NULL;

// ������� ��� ���������� ������ ����� ������ � ������
void insert(list **head, void *address, size_t size, char *comment)
{
    // �������� ������ ��� ������ �������� ������
    list *tmp = (list *) malloc(sizeof(list));
    // ������������� ��������� next ��� ������ �������� �� ������� head
    tmp->next = *head;
    // ��������� ���� ������ ��������
    tmp->address = address;
    tmp->size = size;
    sprintf(tmp->comment, "%s", comment); // �������� �����������
    // ��������� head, ����� ����� ������� ������ � ������
    *head = tmp;
}

// ������� ��� �������� ����� ������ �� ������
_Bool delete(list **head, void *address)
{
    // ���������, �� ���� �� ������
    if (*head == NULL)
    {
        return 0; // ������ ����, ������� �� ������
    }
    list *del = NULL; // ��������� �� ��������� �������
    // ���������, ����� �� ������� ������ �������
    if ((*head)->address == address)
    {
        del = *head;
        *head = (*head)->next; // ���������� head �� ��������� �������
        free(del); // ����������� ������, ���������� ��� ���������� ��������
        return 1; // �������� ������ �������
    }
    // �������� �� ������, ����� ����� ������� ��� ��������
    list *tmp = *head;
    while (tmp->next)
    {
        if (tmp->next->address == address)
        {
            del = tmp->next; // ����� ������� ��� ��������
            tmp->next = del->next; // ������� ��������� �������
            free(del); // ����������� ������, ���������� ��� ���������� ��������
            return 1; // �������� ������ �������
        }
        tmp = tmp->next; // ��������� � ���������� ��������
    }
    // ������� �� ������
    return 0;
}

// ������� ��� ������ ������ ���������� ������
void printList(list *head)
{
    if (head == NULL)
    {
        printf("No memory leak detect\n"); // ���� ������ ����, �� ������ ������ �� ����������
    }
    while (head)
    {
        printf("%s\n", head->comment); // �������� ����������� ��� ������� ��������
        head = head->next; // ��������� � ���������� ��������
    }
}

// ���������������� ������� malloc, ������� ��������� ���������� � ������
void *my_malloc(size_t size, const char *file, int line, const char *func)
{
    void *ptr = malloc(size); // �������� ������ � ������� ����������� malloc
    char coment[64] = {0}; // ������� ������ ��� �����������
    sprintf(coment, "Allocated = %s, %i, %s, %p[%lli]", file, line, func, ptr, size); // ��������� �����������
    insert(&memlist, ptr, size, coment); // ��������� ���������� � ������
    return ptr; // ���������� ����� ���������� ������
}

// ���������������� ������� free, ������� ������� ���������� �� ������
void my_free(void *ptr, const char *file, int line, const char *func)
{
    delete(&memlist, ptr); // ������� ���������� �� ������
    free(ptr); // ����������� ������ � ������� ����������� free
}

// ��������������� �������� malloc � free ��� ������������� ���������������� �������
#define malloc(X) my_malloc((X), __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free((X), __FILE__, __LINE__, __FUNCTION__)

// ������� ��� ������ ����� � ������������ ��������
void * findMaxBlock(list *head)
{
    size_t mx_size = 0; // �������������� ������������ ������ 0
    void *address = 0; // �������������� ����� 0
    while (head)
    {
        if (head->size > mx_size)
        {
            mx_size = head->size; // ��������� ������������ ������
            address = head->address; // ��������� ����� ������������� �����
        }
        head = head->next; // ��������� � ���������� ��������
    }
    if (address)
    {
        printf("%p\n", address); // ������� ����� ������������� �����
    } else {
        printf("memory is not allocated\n"); // ���� ������ ����, ������� ���������
    }
    return address;
}

int main(void)
{
    // �������� ������ � ������� ����������������� malloc
    int *p = malloc(sizeof(int) * 10);
    int *ar = malloc(sizeof(int) * 30);
    int *ar2 = malloc(sizeof(int) * 100);
    int *ar3 = malloc(sizeof(int) * 40);
    printList(memlist); // �������� ������ ���������� ������
    findMaxBlock(memlist); // ���� ������������ ����
    free(p);
    free(ar);
    free(ar2);
    findMaxBlock(memlist); // ���� ������������ ����
    free(ar3);
    findMaxBlock(memlist); // ���� ������������ ����

    return 0;
}
