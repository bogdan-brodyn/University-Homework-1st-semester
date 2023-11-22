#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Dictionary.h"

typedef struct Node
{
    char* key;
    char* value;
    unsigned char height;
    struct Node* left;
    struct Node* right;
} Node;

struct Dictionary
{
    Node* root;
};

static unsigned char height(Node* node)
{
    return node != NULL ? node->height : 0;
}

static char difference(Node* node)
{
    return height(node->left) - height(node->right);
}

static void fixHeight(Node* node)
{
    node->height = max(height(node->left), height(node->right)) + 1;
}

static Node* rotateLeft(Node* a)
{
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

static Node* rotateRight(Node* a)
{
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

static Node* bigRotateLeft(Node* a)
{
    a->right = rotateRight(a->right);
    return rotateLeft(a);
}

static Node* bigRotateRight(Node* a)
{
    a->left = rotateLeft(a->left);
    return rotateRight(a);
}

static Node* balance(Node* node)
{
    fixHeight(node);
    if (difference(node) == -2)
    {
        return difference(node->right) == 1 ?
            bigRotateLeft(node) : rotateLeft(node);
    }
    else if (difference(node) == 2)
    {
        return difference(node->left) == -1 ?
            bigRotateRight(node) : rotateRight(node);
    }
    return node;
}

static char compare(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return string1[i] - string2[i];
        }
    }
    return 0;
}

static Node* getNext(const Node* const currentElement, const char* const key)
{
    const char compareResult = compare(currentElement->key, key);
    if (compareResult < 0)
    {
        return currentElement->right;
    }
    if (compareResult > 0)
    {
        return currentElement->left;
    }
    return currentElement;
}

static Node* createNode(const char* const key, const char* const value)
{
    Node* const newElement = (Node* const)calloc(1, sizeof(Node));
    if (newElement == NULL)
    {
        return NULL;
    }
    newElement->height = 1;
    const size_t keySize = strlen(key) + 1;
    const size_t valueSize = strlen(value) + 1;
    newElement->key = (char*)malloc(keySize * sizeof(char));
    newElement->value = (char*)malloc(valueSize * sizeof(char));
    if (newElement->key == NULL || newElement->value == NULL)
    {
        free(newElement->key);
        free(newElement->value);
        free(newElement);
        return NULL;
    }
    strcpy_s(newElement->key, keySize, key);
    strcpy_s(newElement->value, valueSize, value);
    return newElement;
}

static void deleteNode(Node** node)
{
    if (node == NULL)
    {
        return;
    }
    free((*node)->key);
    free((*node)->value);
    free(*node);
    *node = NULL;
}

static void copyNode(Node* destination, Node* source)
{
    free(destination->key);
    free(destination->value);
    destination->key = source->key;
    destination->value = source->value;
    free(source);
}

Node* insertKey(Node* node, Node* nodeToInsert)
{
    if (node == NULL)
    {
        return nodeToInsert;
    }
    const char compareResult = compare(node->key, nodeToInsert->key);
    if (compareResult == 0)
    {
        copyNode(node, nodeToInsert);
    }
    else if (compareResult < 0)
    {
        node->right = insertKey(node->right, nodeToInsert);
    }
    else
    {
        node->left = insertKey(node->left, nodeToInsert);
    }
    return balance(node);
}

DictionaryErrorCode add(Dictionary** const dictionary, 
    const char* const key, const char* const value)
{
    if (dictionary == NULL)
    {
        return dictionaryNullPointer;
    }

    Node* const newElement = createNode(key, value);
    if (newElement == NULL)
    {
        return dictionaryMemoryLack;
    }

    if (*dictionary == NULL)
    {
        *dictionary = (Dictionary* const)calloc(1, sizeof(Dictionary));
        if (*dictionary == NULL)
        {
            deleteNode(&newElement);
            return dictionaryMemoryLack;
        }
        (*dictionary)->root = newElement;
        return dictionaryDefaultErrorCode;
    }

    (*dictionary)->root = insertKey((*dictionary)->root, newElement);
    return dictionaryDefaultErrorCode;
}

DictionaryErrorCode get(const Dictionary* const dictionary, 
    const char* const key, char** const value)
{
    if (dictionary == NULL || value == NULL)
    {
        return dictionaryNullPointer;
    }
    for (Node* currentElement = dictionary->root; currentElement != NULL;
        currentElement = getNext(currentElement, key))
    {
        if (compare(currentElement->key, key) == 0)
        {
            *value = currentElement->value;
            return dictionaryDefaultErrorCode;
        }
    }
    return dictionaryNonExistentKey;
}

bool isContained(const Dictionary* const dictionary, const char* const key)
{
    if (dictionary == NULL)
    {
        return false;
    }
    for (Node* currentElement = dictionary->root; currentElement != NULL;
        currentElement = getNext(currentElement, key))
    {
        if (compare(currentElement->key, key) == 0)
        {
            return true;
        }
    }
    return false;
}

static Node* findMinKey(Node* node)
{
    return node->left != NULL ? findMinKey(node->left) : node;
}

static Node* removeMinKey(Node* node)
{
    if (node->left == NULL)
    {
        return node->right;
    }
    node->left = removeMinKey(node->left);
    return balance(node);
}

static Node* removeKeyRecursive(Node* node, const char* const key)
{
    if (node == NULL)
    {
        return NULL;
    }
    const char compareResult = compare(node->key, key);
    if (compareResult < 0)
    {
        node->right = removeKeyRecursive(node->right, key);
    }
    else if (compareResult > 0)
    {
        node->left = removeKeyRecursive(node->left, key);
    }
    else
    {
        if (node->right == NULL)
        {
            return node->left;
        }
        Node* min = findMinKey(node->right);
        min->right = removeMinKey(node->right);
        min->left = node->left;
        deleteNode(&node);
        return balance(min);
    }
    return balance(node);
}

void removeKey(Dictionary* const dictionary, const char* const key)
{
    dictionary->root = removeKeyRecursive(dictionary->root, key);
}

void deleteDictionary(Dictionary** const dictionary)
{
    if (dictionary == NULL || *dictionary == NULL)
    {
        return;
    }
    while ((*dictionary)->root != NULL)
    {
        removeKey(*dictionary, (*dictionary)->root->key);
    }
    free(*dictionary);
    *dictionary = NULL;
}

static bool checkBallanceRecursive(const Node* const node)
{
    if (node == NULL)
    {
        return true;
    }
    return checkBallanceRecursive(node->left)
    && checkBallanceRecursive(node->right)
    && -1 <= difference(node) && difference(node) <= 1;
}

bool checkBalance(const Dictionary* const dictionary)
{
    return checkBallanceRecursive(dictionary->root);
}

static size_t getSearchTreeHeightRecursive(const Node* const node)
{
    if (node == NULL)
    {
        return 0;
    }
    return max(getSearchTreeHeightRecursive(node->left),
        getSearchTreeHeightRecursive(node->right)) + 1;
}

size_t getSearchTreeHeight(const Dictionary* const dictionary)
{
    return getSearchTreeHeightRecursive(dictionary->root);
}
