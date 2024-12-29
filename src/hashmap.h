#ifndef HASHMAP_H
#define HASHMAP_H

#include "rprintf.h"
#include "serial.h"
#include "string.h"

#define TABLE_SIZE 10
#define MAX_NODES 10

typedef struct Node {
        char key[32];
        int val;
        struct Node *next;
} Node;

typedef struct HashMap {
        Node *table[TABLE_SIZE];
        Node nodes[MAX_NODES];
        Node *freeList;
} HashMap;

void init_hashmap(HashMap *map);
unsigned int hash(const char *key);
Node *allocateNode(HashMap *map, const char *key, int val);
void addEntry(HashMap *map, const char *key, int val);
int getValue(HashMap *map, const char *key);
int containsKey(const HashMap *map, const char *key);
void freeNode(HashMap *map, Node *node);
void printMapFreeList(const HashMap *map);
void printHashMap(const HashMap *map);

#endif
