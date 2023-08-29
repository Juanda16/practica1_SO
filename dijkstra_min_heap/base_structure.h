#ifndef __BASE_STRUCTURE_H__
#define __BASE_STRUCTURE_H__

typedef struct
{
    char id[5];
    Heap distancesTree[20];

} Node;

typedef struct
{
    char id[5];
    int distanceFromParent;

} NodeWithDistance;

// Declare a heap structure
struct Heap
{
    NodeWithDistance *arr;
    int size;
    int capacity;
};

// define the struct Heap name
typedef struct Heap heap;

#endif
