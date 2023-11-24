#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Dictionary.h"
#include "String.h"

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

static unsigned char height(const Node* const node)
{
    return node != NULL ? node->height : 0;
}

static char difference(const Node* const node)
{
    return height(node->left) - height(node->right);
}

static void fixHeight(Node* const node)
{
    node->height = max(height(node->left), height(node->right)) + 1;
}

static Node* rotateLeft(Node* const a)
{
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

static Node* rotateRight(Node* const a)
{
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

static Node* bigRotateLeft(Node* const a)
{
    a->right = rotateRight(a->right);
    return rotateLeft(a);
}

static Node* bigRotateRight(Node* const a)
{
    a->left = rotateLeft(a->left);
    return rotateRight(a);
}

static Node* balance(Node* const node)
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
    newElement->key = getStringCopy(key);
    newElement->value = getStringCopy(value);
    if (newElement->key == NULL || newElement->value == NULL)
    {
        free(newElement->key);
        free(newElement->value);
        free(newElement);
        return NULL;
    }
    return newElement;
}

static void deleteNode(Node** const node)
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

static void moveNodeData(Node* const destination, const Node* const source)
{
    free(destination->key);
    free(destination->value);
    destination->key = source->key;
    destination->value = source->value;
    free(source);
}

static Node* insertKey(Node* const node, const Node* const nodeToInsert)
{
    if (node == NULL)
    {
        return nodeToInsert;
    }
    const char compareResult = compare(node->key, nodeToInsert->key);
    if (compareResult == 0)
    {
        moveNodeData(node, nodeToInsert);
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
    const char* const key, const char** const value)
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
    char* value = NULL;
    DictionaryErrorCode searchResult = get(dictionary, key, &value);
    return searchResult == dictionaryDefaultErrorCode;
}

static Node* findMinKey(const Node* const node)
{
    return node->left != NULL ? findMinKey(node->left) : node;
}

static Node* removeMinKey(Node* const node)
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
        Node* left = node->left;
        Node* right = node->right;
        deleteNode(&node);
        if (right == NULL)
        {
            return left;
        }
        Node* min = findMinKey(right);
        min->right = removeMinKey(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

void removeKey(Dictionary* const dictionary, const char* const key)
{
    dictionary->root = removeKeyRecursive(dictionary->root, key);
}

static Node* deleteMinKeyWithNoBalance(Node* const node)
{
    if (node->left == NULL)
    {
        Node* temp = node->right;
        deleteNode(&node);
        return temp;
    }
    node->left = deleteMinKeyWithNoBalance(node->left);
    return node;
}

void deleteDictionary(Dictionary** const dictionary)
{
    if (dictionary == NULL || *dictionary == NULL)
    {
        return;
    }
    while ((*dictionary)->root != NULL)
    {
        (*dictionary)->root = deleteMinKeyWithNoBalance((*dictionary)->root);
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
