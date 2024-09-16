/*
 * Алексеев Дмитрий Александрович
 * HWA_2_1.c
 *
 * Задача 2-1-Максимальный блок
 *
 * Описана структура данных
 *
 * typedef struct list {
 *              void *address;
 *              size_t size;
 *              char comment[64];
 *              struct list *next;
 * } list;
 *
 * Требуется реализовать только одну функцию, которая в данном списке находит адрес блока памяти занимающий больше всего места.
 * Адрес хранится в поле address, поле size - соответствующий размер данного блока. Если список пустой, то функция должна возвращать NULL.
 * Если есть несколько таких блоков, то вернуть адрес любого из них.
 * Прототип функции:
 * void * findMaxBlock(list *head)
 */



#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

// Определение структуры для хранения информации об использованной памяти
typedef struct list
{
    void *address;  // Адрес выделенного блока памяти
    size_t size;     // Размер выделенного блока памяти
    char comment[64]; // Комментарий, описывающий блок памяти
    struct list *next; // Указатель на следующий элемент списка
} list;

// Глобальная переменная для хранения списка выделенной памяти
list *memlist = NULL;

// Функция для добавления нового блока памяти в список
void insert(list **head, void *address, size_t size, char *comment)
{
    // Выделяем память для нового элемента списка
    list *tmp = (list *) malloc(sizeof(list));
    // Устанавливаем указатель next для нового элемента на текущий head
    tmp->next = *head;
    // Заполняем поля нового элемента
    tmp->address = address;
    tmp->size = size;
    sprintf(tmp->comment, "%s", comment); // Копируем комментарий
    // Обновляем head, делая новый элемент первым в списке
    *head = tmp;
}

// Функция для удаления блока памяти из списка
_Bool delete(list **head, void *address)
{
    // Проверяем, не пуст ли список
    if (*head == NULL)
    {
        return 0; // Список пуст, элемент не найден
    }
    list *del = NULL; // Указатель на удаляемый элемент
    // Проверяем, нужно ли удалить первый элемент
    if ((*head)->address == address)
    {
        del = *head;
        *head = (*head)->next; // Перемещаем head на следующий элемент
        free(del); // Освобождаем память, выделенную для удаленного элемента
        return 1; // Удаление прошло успешно
    }
    // Итерация по списку, чтобы найти элемент для удаления
    list *tmp = *head;
    while (tmp->next)
    {
        if (tmp->next->address == address)
        {
            del = tmp->next; // Нашли элемент для удаления
            tmp->next = del->next; // Обходим удаляемый элемент
            free(del); // Освобождаем память, выделенную для удаленного элемента
            return 1; // Удаление прошло успешно
        }
        tmp = tmp->next; // Переходим к следующему элементу
    }
    // Элемент не найден
    return 0;
}

// Функция для печати списка выделенной памяти
void printList(list *head)
{
    if (head == NULL)
    {
        printf("No memory leak detect\n"); // Если список пуст, то утечек памяти не обнаружено
    }
    while (head)
    {
        printf("%s\n", head->comment); // Печатаем комментарий для каждого элемента
        head = head->next; // Переходим к следующему элементу
    }
}

// Модифицированная функция malloc, которая добавляет информацию в список
void *my_malloc(size_t size, const char *file, int line, const char *func)
{
    void *ptr = malloc(size); // Выделяем память с помощью стандартной malloc
    char coment[64] = {0}; // Создаем строку для комментария
    sprintf(coment, "Allocated = %s, %i, %s, %p[%lli]", file, line, func, ptr, size); // Формируем комментарий
    insert(&memlist, ptr, size, coment); // Добавляем информацию в список
    return ptr; // Возвращаем адрес выделенной памяти
}

// Модифицированная функция free, которая удаляет информацию из списка
void my_free(void *ptr, const char *file, int line, const char *func)
{
    delete(&memlist, ptr); // Удаляем информацию из списка
    free(ptr); // Освобождаем память с помощью стандартной free
}

// Переопределение макросов malloc и free для использования модифицированных функций
#define malloc(X) my_malloc((X), __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free((X), __FILE__, __LINE__, __FUNCTION__)

// Функция для поиска блока с максимальным размером
void * findMaxBlock(list *head)
{
    size_t mx_size = 0; // Инициализируем максимальный размер 0
    void *address = 0; // Инициализируем адрес 0
    while (head)
    {
        if (head->size > mx_size)
        {
            mx_size = head->size; // Обновляем максимальный размер
            address = head->address; // Обновляем адрес максимального блока
        }
        head = head->next; // Переходим к следующему элементу
    }
    if (address)
    {
        printf("%p\n", address); // Выводим адрес максимального блока
    } else {
        printf("memory is not allocated\n"); // Если список пуст, выводим сообщение
    }
    return address;
}

int main(void)
{
    // Выделяем память с помощью модифицированного malloc
    int *p = malloc(sizeof(int) * 10);
    int *ar = malloc(sizeof(int) * 30);
    int *ar2 = malloc(sizeof(int) * 100);
    int *ar3 = malloc(sizeof(int) * 40);
    printList(memlist); // Печатаем список выделенной памяти
    findMaxBlock(memlist); // Ищем максимальный блок
    free(p);
    free(ar);
    free(ar2);
    findMaxBlock(memlist); // Ищем максимальный блок
    free(ar3);
    findMaxBlock(memlist); // Ищем максимальный блок

    return 0;
}
