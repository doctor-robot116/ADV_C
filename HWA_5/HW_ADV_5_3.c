/*
 * Алексеев Дмитрий Александрович
 * 
 * 
 * Задача 5-3-Польская запись
 * Необходимо вычислить выражение написанное в обратной польской записи.
 *  На вход подается строка состоящая из целых, не отрицательных чисел и арифметических символов.
 *  В ответ единственное целое число - результат.
 * 
 * Формат ввода:
 * Строка состоящая из целых чисел и символов '+', '-', '*', '/', ' '. В конце строки символ '.'.
 * Строка корректная. Длина строки не превосходит 1000 символов. Все числа и операции разделены ровно одним пробелом.
 * 
 * Формат вывода:
 * Целое число, результат вычисления выражения.
 * Пример №1
 * Данные на входе:		3 4 +.
 * Данные на выходе:	7
 * Пример №2
 * Данные на входе:		1 2 + 4 × 3 +.
 * Данные на выходе:	15
 * Пример №3
 * Данные на входе:		100 25 + 25 /.
 * Данные на выходе:	5
 * Пример №4
 * Данные на входе:		1 2 3 4 + * +.
 * Данные на выходе:	15
 */


#include <stdio.h>
#include <stdlib.h> // Подключаем стандартную библиотеку для работы с памятью
#include <string.h>

// Определяем тип данных для стека как целое число
typedef int datatype; 

// Прототипы функций
void push(datatype v); // Функция для добавления элемента в стек
datatype pop(void); // Функция для извлечения элемента из стека
int isEmpty(void); // Функция для проверки, пуст ли стек
void operate(char c); // Функция для выполнения операции над элементами стека

// Определяем максимальный размер стека
#define MAX_STACK_SIZE 255

// Объявляем массив для стека
datatype st[MAX_STACK_SIZE]; 
// Объявляем переменную для отслеживания степени заполненности стека
int pst = 0; 

// Функция для добавления элемента в стек
void push(datatype v)
{   
    // Проверяем, не переполнен ли стек
    if(pst >= MAX_STACK_SIZE)
    {
        fprintf(stderr, "Error. Stack overflow\n");
        exit(1); // Завершаем программу с кодом ошибки
    }
    // Добавляем элемент в стек
    st[pst++] = v; 
}

// Функция для извлечения элемента из стека
datatype pop()
{
    // Проверяем, не пуст ли стек
    if(pst <= 0)
    {
        fprintf(stderr, "Error. Stack underflow\n");
        exit(1); // Завершаем программу с кодом ошибки
    }
    // Извлекаем элемент из стека
    return st[--pst]; 
}

// Функция для проверки, пуст ли стек
int isEmpty()
{   
    // Возвращаем true, если стек пуст, иначе false
    return (pst <= 0); 
}

// Функция для выполнения операции над элементами стека
void operate(char c)
{   
    // Извлекаем два элемента из стека
    datatype arg1 = pop(), arg2 = pop();

    // Выполняем операцию в зависимости от символа `c`
    switch(c)
    {
        case '+':
            push(arg1 + arg2); // Сложение
            break;
        case '-':
            push(arg1 - arg2); // Вычитание
            break;
        case '*':
            push(arg1 * arg2); // Умножение
            break;
        case '/':
            // Проверка на деление на ноль
            if (arg1 == 0) 
            {
                fprintf(stderr, "Error. Division by zero.\n");
                exit(1); // Завершаем программу с кодом ошибки
            }
            push(arg2 / arg1); // Деление
            break;
    }
}

// Функция для проверки, является ли символ цифрой
_Bool isDigit(char c)
{   
    return ((c >= '0') && (c <= '9')); // Возвращаем true, если символ цифра
}

// Функция для проверки, является ли символ оператором
_Bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/'; // Возвращаем true, если символ оператор
}

// Основная функция
int main(void)
{
    char c; // Переменная для хранения символа
    printf("Input inverse string: "); // Выводим приглашение для ввода строки
    char str[1000]; // Объявляем массив для хранения строки
    int len = 0; // Переменная для хранения длины строки

    // Считываем строку с клавиатуры
    while((c = getchar()) != '\n')
        str[len++] = c; 
    str[len] = 0; // Добовляем нулевой символ в конец строки

    // Перебираем символы в строке
    for(int i = 0; i < len; i++)
    {
        // Проверяем, является ли символ цифрой
        if(isDigit(str[i]))
        {
            datatype number; // Переменная для хранения числа
            // Считываем число из строки
            for(number = 0; isDigit(str[i]); i++)
                number = number * 10 + str[i] - '0';
            // Добавляем число в стек
            push(number);
        }
        // Проверяем, является ли символ оператором
        else if (isOperator(str[i])) 
        {
            // Выполняем операцию над элементами стека
            operate(str[i]); 
        }
    }

    // Выводим результат вычисления
    printf("answer = %d\n", pop()); 
    return 0; // Завершаем программу
}

