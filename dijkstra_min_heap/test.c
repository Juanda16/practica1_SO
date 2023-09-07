#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main(int argc, char *argv[])
{
    PQ *pq = pq_create(15, 1);
    int i;
    double priority;

    printf("\nCapacity of pq: %d\n\n", pq_capacity(pq));

    pq_insert(pq, 0, 7);
    pq_insert(pq, 1, 11);
    pq_insert(pq, 2, 50);
    pq_insert(pq, 3, 12); // changed
    pq_insert(pq, 4, 33);
    pq_insert(pq, 5, 51);
    pq_insert(pq, 6, 55);
    pq_insert(pq, 7, 21);
    pq_insert(pq, 8, 55);
    pq_insert(pq, 9, 80);
    pq_insert(pq, 10, 34);
    pq_insert(pq, 11, 25);

    pq_change_priority(pq, 3, 53);
    pq_remove_by_id(pq, 3);
    pq_remove_by_id(pq, 2);

    // print the priority queue
    for (i = 0; i < pq_capacity(pq); i++)
    {
        if (pq_contains(pq, i))
        {
            pq_get_priority(pq, i, &priority);
            printf("<---> [%9lf] <-> ID: %d\n", priority, i);
        }
    }

    printf("\nSize of pq: %d\n", pq_size(pq));

    pq_free(pq);

    return 0;
}