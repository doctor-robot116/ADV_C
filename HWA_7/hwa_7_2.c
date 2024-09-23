/*
 * Алексеев Дмитрий Александрович
 *
 * Задача 7-2-Вид сверху
 * В программе описана структура для хранения двоичного дерева:
 * typedef struct tree {
 * datatype key;
 * struct tree *left, *right;
 * } tree;
 *
 * Необходимо реализовать функцию, которая печатает вид дерева сверху.
 * Функция должна строго соответствовать прототипу: void btUpView(tree *root)
 * В качестве ответа загрузите только одну функцию void btUpView(tree *root)
 *
 * Пример №1
 *
 * Данные на входе:

       10
      /   \
     5     15
    / \   /  \
   3   7 13   18
  /   /
 1   6



Данные на выходе:	1 3 5 10 15 18

*
*/


#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int32_t datatype;

typedef struct tree
{
    datatype key;
    struct tree *left, *right;
} tree;


void insert_t(tree **root, datatype key)  // Функция для вставки нового узла в дерево
{
    if(!*root)   // Если дерево пустое, создается новый узел и становится корнем дерева
    {
        *root = (tree *) calloc(1, sizeof(tree));
        (*root)->key = key;
    }
    else if((*root)->key < key) // Если ключ нового узла больше, чем ключ корня, вставка происходит в правое поддерево
    {
        insert_t(&(*root)->right, key);
    }
    
    else  // Если ключ нового узла меньше, чем ключ корня, вставка происходит в левое поддерево
    {
        insert_t(&(*root)->left, key);
    }
}

void go_left(tree *root) // Функция для рекурсивного обхода левого поддерева, печатая ключи узлов
{
    if(root->left)  // Если у узла есть левое поддерево, рекурсивно обходим его
    {
        go_left(root->left);
    }
    printf("%d ", root->key);
}

void go_right(tree *root)  // Функция для рекурсивного обхода правого поддерева, печатая ключи узлов
{
    printf("%d ", root->key); // Если у узла есть правое поддерево, рекурсивно обходим его левое поддерево
    if(root->right)
    {
        go_left(root->right);
    }
}

void btUpView(tree *root)  // Функция для печати дерева сверху
{
    if (root == NULL)
    {
        return;
    }
    go_left(root);  // Рекурсивно обходим левое поддерево
    if(root->right)  // Если у узла есть правое поддерево, рекурсивно обходим его
    {
        go_right(root->right);
    }
    printf("\n");
}

int main()
{
    tree *my_tree = NULL;
    insert_t(&my_tree, 10);
    insert_t(&my_tree, 5);
    insert_t(&my_tree, 15);
    insert_t(&my_tree, 3);
    insert_t(&my_tree, 7);
    insert_t(&my_tree, 13);
    insert_t(&my_tree, 18);
    insert_t(&my_tree, 1);
    insert_t(&my_tree, 6);
    btUpView(my_tree);
}
