#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "pq.h"

#define MAX_NODES 20
#define MAX_NODE_LENGHT 20

char *nodes[MAX_NODES]; //[MAX_NODE_LENGHT];
int number_of_nodes = 0;
int adj[MAX_NODES][MAX_NODES];

void relax(PQ *pq, int distance[20][20],
           unsigned int u, unsigned int v, unsigned int w, unsigned int n);
void print_pq(PQ *pq);

void run_dijkstra(int adj_matrix[20][20], int distance[20][20], int s, int n);
char *trimwhitespace(char *str)
{
    char *end;
    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0) // All spaces?
        return str;
    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    // Write new null terminator character
    end[1] = '\0';
    return str;
}

// Returns -1 if node is not present
int get_index_of_node(char *node_to_check)
{
    int value = -1;
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (0 == (strcmp(nodes[i], node_to_check)))
        {
            value = i;
            break;
        }
    }
    printf("Index: %d\n", value);
    return value;
}

void print_adj()
{
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int j = 0; j < number_of_nodes; j++)
        {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    // PQ *pq = pq_create(MAX_NODES, 1);
    // int i;
    // double priority;

    // printf("\nCapacity of pq: %d\n\n", pq_capacity(pq));

    // for (int i = 0; i < MAX_NODES; i++)
    // {
    //     pq_insert(pq, i, INT_MAX);
    // }

    // pq_change_priority(pq, 0, 0);

    // Getting a pointer to the opened file and check possible error
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("The file doesn't exist");
        exit(EXIT_FAILURE);
    }

    size_t len = 0; // This is ised to have an indication of how many characters we want to read using the  getline() function (Read documentation)
    ssize_t read;   // This is used to store the returned value. the double ss means signed size (To indicate error typically returning -1)
    char *line = NULL;
    char *s = NULL;
    int read_line = 0;
    int is_directed = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (read_line == 0)
        {
            s = line;
            // This while is to replace the \n by \0 to have a proper comparison using strcmp
            while (*s != '\n')
            {
                ++s;
            }
            *s = '\0';
            if (0 == (strcmp("true", line)))
            {
                is_directed = 1;
            }
        }
        else
        {

            char *end_str;
            char *token = strtok_r(line, ";", &end_str);

            while (token != NULL)
            {

                int i = 0;
                int source = -1;
                int destination = -1;
                int weight = -1;
                char *end_token;
                char *token_inner = strtok_r(token, ",", &end_token);

                while (token_inner != NULL && i < 3)
                {
                    if (i == 0)
                    {
                        token_inner = trimwhitespace(token_inner);
                        token_inner += 1;
                        source = get_index_of_node(token_inner);
                        if (source == -1)
                        {
                            source = number_of_nodes;
                            nodes[source] = malloc(sizeof(char) * (strlen(token_inner) + 1));
                            strcpy(nodes[source], token_inner);
                            number_of_nodes++;
                        }
                    }
                    else if (i == 1)
                    {
                        token_inner = trimwhitespace(token_inner);
                        destination = get_index_of_node(token_inner);
                        if (destination == -1)
                        {
                            destination = number_of_nodes;
                            nodes[destination] = malloc(sizeof(char) * (strlen(token_inner) + 1));
                            strcpy(nodes[destination], token_inner);
                            number_of_nodes++;
                        }
                    }
                    else if (i == 2)
                    {
                        token_inner = trimwhitespace(token_inner);
                        s = token_inner;
                        // This while is to erase the the character ) and replace it by \n in order of no affect the atoi cast!
                        while (*s != ')')
                        {
                            ++s;
                        }
                        *s = '\0';
                        weight = atoi(token_inner);
                    }
                    else
                    {
                        printf("Parsing error. Not possible four values for edege\n");
                    }
                    i++;
                    token_inner = strtok_r(NULL, ",", &end_token);
                }
                adj[source][destination] = weight;
                if (is_directed == 0)
                {
                    adj[destination][source] = weight;
                }
                token = strtok_r(NULL, ";", &end_str);
            }
        }
        read_line++;
    }
    print_adj();
    run_dijkstra(adj, adj, 0, number_of_nodes);

    // // print the priority queue
    // for (i = 0; i < pq_capacity(pq); i++)
    // {
    //     if (pq_contains(pq, i))
    //     {
    //         pq_get_priority(pq, i, &priority);
    //         printf("<---> [%9lf] <-> ID: %d\n", priority, i);
    //     }
    // }

    // printf("\nSize of pq: %d\n", pq_size(pq));

    // pq_free(pq);
}

void run_dijkstra(int adj_matrix[20][20], int distance[20][20], int s, int n)
{

    unsigned int heap[n][2];
    unsigned int S[n]; // vertices processed
    unsigned int notVisited[n];

    PQ *pq = pq_create(MAX_NODES, 1);
    int i;
    double priority;

    printf("\nCapacity of pq: %d\n\n", pq_capacity(pq));

    for (int i = 0; i < MAX_NODES; i++)
    {
        pq_insert(pq, i, INT_MAX);
    }

    pq_change_priority(pq, 0, 0);

    // print the priority queue
    print_pq(pq);

    printf("\nSize of pq: %d\n", pq_size(pq));

    for (size_t i = 0; i < n; i++)
    {
        notVisited[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        distance[i][0] = 0xFFFFFFFF;
        distance[i][1] = 0xFFFFFFFF;
        // heap[i][0] = 0xFFFFFFFF;
        // heap[i][1] = i;
        S[i] = 0;
    }
    distance[s][0] = 0;
    distance[s][1] = 0;
    // heap[s][0] = 0;

    // unsigned int heap_size = n;

    // build_min_heap(heap, heap_size);

    while (pq_size(pq) > 0) // quote !=0 pq
    {
        int id = -1;
        pq_delete_top(pq, &id, &priority);
        // unsigned int min_val = heap_extract_min(heap, heap_size, &u); //min from heap

        if (id == -1)
        {
            printf("unexpected case\n");
            break;
        }
        S[id] = 1;
        // heap_size--;
        if (priority == (unsigned int)-1)
        {
            break;
        }
        else
        {
            for (unsigned int v = 0; v < n; v++)
            {
                unsigned int w = adj_matrix[id][v];
                if (w != (unsigned int)-1 && S[v] != 1)
                {
                    relax(pq, distance, id, v, w, n);
                }
            }
        }

        print_pq(pq);
    }

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
}

void relax(PQ *pq, int distance[20][20],
           unsigned int u, unsigned int v, unsigned int w, unsigned int n)
{

    unsigned int weight = distance[u][0] + w;

    if (distance[v][0] > weight)
    {
        distance[v][0] = weight;
        distance[v][1] = u;
        pq_change_priority(pq, v, weight);
        // heap_decrease_key(heap, v, weight, n);
    }
}

void print_pq(PQ *pq)
{
    for (int i = 0; i < pq_capacity(pq); i++)
    {
        if (pq_contains(pq, i))
        {
            double priority;
            pq_get_priority(pq, i, &priority);
            printf("<---> [%9lf] <-> ID: %d\n", priority, i);
        }
    }
}
