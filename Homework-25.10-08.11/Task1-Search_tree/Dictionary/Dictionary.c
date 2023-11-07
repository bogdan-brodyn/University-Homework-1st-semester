#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Dictionary.h"

typedef struct Node
{
    int key;
    char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct Dictionary
{
    Node* root;
};

static Node* getNext(const Node* const currentElement, const int key)
{
    if (currentElement->key < key)
    {
        return currentElement->rightChild;
    }
    if (currentElement->key > key)
    {
        return currentElement->leftChild;
    }
    return currentElement;
}

static Node* createNode(const int key, const char* const value)
{
    Node* const newElement = (Node* const)calloc(1, sizeof(Node));
    if (newElement == NULL)
    {
        return NULL;
    }
    newElement->key = key;
    const size_t valueSize = strlen(value) + 1;
    newElement->value = (char*)malloc(valueSize * sizeof(char));
    if (newElement->value == NULL)
    {
        free(newElement);
        return NULL;
    }
    strcpy_s(newElement->value, valueSize, value);
    return newElement;
}

static void deleteNode(Node** node)
{
    if (node == NULL)
    {
        return;
    }
    free((*node)->value);
    free(*node);
    *node = NULL;
}

static void copyNode(Node* destination, Node* source)
{
    free(destination->value);
    destination->key = source->key;
    destination->value = source->value;
    free(source);
}

DictionaryErrorCode add(Dictionary** const dictionary, 
    const int key, const char* const value)
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

    for (Node* currentElement = (*dictionary)->root; ; 
        currentElement = getNext(currentElement, key))
    {
        if (currentElement->key == key)
        {
            copyNode(currentElement, newElement);
            break;
        }
        if (currentElement->key < key && currentElement->rightChild == NULL)
        {
            currentElement->rightChild = newElement;
            break;
        }
        if (currentElement->key > key && currentElement->leftChild == NULL)
        {
            currentElement->leftChild = newElement;
            break;
        }
    }
    return dictionaryDefaultErrorCode;
}

DictionaryErrorCode get(const Dictionary* const dictionary, 
    const int key, char** const value)
{
    if (dictionary == NULL || value == NULL)
    {
        return dictionaryNullPointer;
    }
    for (Node* currentElement = dictionary->root; currentElement != NULL;
        currentElement = getNext(currentElement, key))
    {
        if (currentElement->key == key)
        {
            *value = currentElement->value;
            return dictionaryDefaultErrorCode;
        }
    }
    return dictionaryNonExistentKey;
}

bool isContained(const Dictionary* const dictionary, const int key)
{
    if (dictionary == NULL)
    {
        return false;
    }
    for (Node* currentElement = dictionary->root; currentElement != NULL;
        currentElement = getNext(currentElement, key))
    {
        if (currentElement->key == key)
        {
            return true;
        }
    }
    return false;
}

static void setParentNode(Dictionary* const dictionary,
    const Node* const node, Node* const parent, const Node* const nodeReplacement)
{
    if (dictionary->root == node)
    {
        dictionary->root = nodeReplacement;
    }
    else if (parent->key < node->key)
    {
        parent->rightChild = nodeReplacement;
    }
    else
    {
        parent->leftChild = nodeReplacement;
    }
}

static void movePointers(Dictionary* const dictionary, 
    const Node* const node, Node* const parent)
{
    if (node->leftChild == NULL && node->rightChild == NULL)
    {
        setParentNode(dictionary, node, parent, NULL);
    }
    else if (node->leftChild != NULL && node->rightChild == NULL)
    {
        setParentNode(dictionary, node, parent, node->leftChild);
    }
    else if (node->leftChild == NULL && node->rightChild != NULL)
    {
        setParentNode(dictionary, node, parent, node->rightChild);
    }
}

void removeKey(Dictionary* const dictionary, const int key)
{
    if (dictionary == NULL || !isContained(dictionary, key))
    {
        return;
    }
    Node* parent = dictionary->root;
    for (; getNext(parent, key)->key != key; parent = getNext(parent, key));
    Node* nodeToRemove = getNext(parent, key);
    if (nodeToRemove->leftChild != NULL && nodeToRemove->rightChild != NULL)
    {
        Node* tempParent = nodeToRemove;
        Node* nodeToEmplace = tempParent->rightChild;
        for (; nodeToEmplace->leftChild != NULL; 
            tempParent = nodeToEmplace, nodeToEmplace = nodeToEmplace->leftChild);
        movePointers(dictionary, nodeToEmplace, tempParent);
        copyNode(nodeToRemove, nodeToEmplace);
    }
    else
    {
        movePointers(dictionary, nodeToRemove, parent);
        deleteNode(&nodeToRemove);
    }
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
