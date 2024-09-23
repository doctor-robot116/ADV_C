/*
 * Алексеев Дмитрий Александрович
 * 
 * Задача 7-3-Найти брата 
 * В программе описано двоичное дерево: 
 * typedef struct tree {
 * datatype key;
 * struct tree *left, *right;
 * struct tree *parent; //ссылка на родителя
 * } tree;
 * 
 * Требуется реализовать функцию, которая по ключу возвращает адрес соседнего элемента - брата.
 * Если такого ключа нет или у узла нет брата, то необходимо вернуть 0.
 * Прототип функции: tree * findBrother(tree *root, int key)
 * Загрузите в качестве ответа только текст функции, строго согласно прототипу: tree * findBrother(tree *root, int key)
 * 
 * Пример №1
 * Данные на входе:		

        10
      /   \
     5     15
    / \   /  \
   3   7 13   18
  /   /
 1   6

Например, для дерева узел с ключом 3
Данные на выходе:	имеет брата 7
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int32_t datatype;

typedef struct tree
{
    datatype key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

// Функция для вставки нового узла в дерево
void insert_t(tree **root, datatype key)
{
    // Если дерево пустое, создается новый узел и становится корнем дерева
    if(!*root)
    {
        *root = (tree *) calloc(1, sizeof(tree));
        (*root)->key = key;
        (*root)->parent = NULL; // У корневого узла нет родителя
    }
    // Если ключ нового узла больше, чем ключ корня, вставка происходит в правое поддерево
    else if((*root)->key < key)
    {
        insert_t(&(*root)->right, key);
        (*root)->right->parent = *root; // Устанавливаем родителя для нового узла
    }
    // Если ключ нового узла меньше, чем ключ корня, вставка происходит в левое поддерево
    else
    {
        insert_t(&(*root)->left, key);
        (*root)->left->parent = *root; // Устанавливаем родителя для нового узла
    }
}


// Функция для поиска брата узла по ключу
tree * findBrother(tree *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->key == key)
    {
        if (root->parent != NULL)
        {
            if (root->parent->left == root)
            {
                return root->parent->right;
            } else
            {
                return root->parent->left;
            }
        }
        else
        {
            return NULL;
        }
    }
    tree *brother = findBrother(root->left, key);
    if (brother != NULL)
    {
        return brother;
    }
    return findBrother(root->right, key);
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


    // Находим брата узла с ключом 18
    tree *brother = findBrother(my_tree, 18);
    if (brother != NULL) {
        printf("Node with key 18 has a Brother with key %d\n", brother->key);
    } else {
        printf("Node with key 18 has no Brother\n");
    }

    return 0;
}
