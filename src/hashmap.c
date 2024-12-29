#include "hashmap.h"
#include "rprintf.h"
#include "serial.h"
#include "string.h"

void init_hashmap(HashMap *map) {
	
	// set all table entries to null
	for (int i = 0; i < TABLE_SIZE; i++) map->table[i] = NULL;
	
	// Allocate memory for each node and set up the free list
	for (int i = 0; i < MAX_NODES; i++) {
		map->nodes[i].key[0] = '\0';
		map->nodes[i].val = 0;
		map->nodes[i].next = (i < MAX_NODES - 1) ? &map->nodes[i + 1] : NULL;
	}	

	// set the free list of nodes to the address of nodes[0]
	map->freeList = &map->nodes[0];

}

unsigned int hash(const char *key) {
	unsigned int hash = 0;
	while (*key) {
		hash = (hash * 31) + *key;
		key++;
	}
	return hash % TABLE_SIZE;
}

Node *allocateNode(HashMap *map, const char *key, int val) {

	// no available nodes
	if (map->freeList == NULL) {
		esp_printf(putc, "Free list is empty\n");
		return NULL;
	}

	// update the freeList
	Node *node = map->freeList;
	map->freeList = map->freeList->next;

	strCopy(node->key, key, sizeof(node->key) - 1);
	node->key[sizeof(node->key) - 1] = '\0'; // null termination
	node->val = val;
	node->next = NULL;

	return node;
}

void addEntry(HashMap *map, const char *key, int val) {

	unsigned int index = hash(key);
	Node *newNode = allocateNode(map, key, val);

	if (newNode == NULL) {
		esp_printf(putc, "Out of free nodes\n");
		return; // failed to allocate
	}
	
	if (map->table[index] == NULL) map->table[index] = newNode;
	else {
		Node *curr = map->table[index];
		Node *prev = NULL;
		
		// traverse to the end of the chain or find an existing key
		while (curr != NULL) {
			if (strEqual(curr->key, key)) {
				
				// key exists, update value
				curr->val = val; 

				// return unused newNode to free list
				newNode->next = map->freeList;
				map->freeList = newNode;
				return;
			}
			prev = curr;
			curr = curr->next;
		}

		// key does not exist, append the new node at the end
		prev->next = newNode;
	}
}

int containsKey(const HashMap *map, const char *key) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		Node *curr = map->table[i];
		while (curr != NULL) {
			if (strEqual(curr->key, key)) return 1;
			curr = curr->next;
		}
	}
	return 0;
}

int getValue(HashMap *map, const char *key) {
	unsigned int index = hash(key);
	Node *curr = map->table[index];

	while (curr != NULL) {
		if (strEqual(curr->key, key)) return curr->val;
		curr = curr->next;
	}
	return 0;
}

void freeNode(HashMap *map, Node *node) {
	if (node != NULL) {
		node->next = map->freeList;
		map->freeList = node;
	}
}

void printMapFreeList(const HashMap *map) {
	esp_printf(putc, "Free list:\n");
	Node *curr = map->freeList;
	while (curr != NULL) {
		esp_printf(putc, "Node key: %s\n", curr->key[0] ? curr->key : "(empty)");
		curr = curr->next;
	}
}

void printHashMap(const HashMap *map) {
	esp_printf(putc, "{");
	int isFirst = 1; // track the first entry
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (map->table[i] != NULL) {
			Node *curr = map->table[i];
				while (curr != NULL) {

					// if it's not the first entry, place comma followed by k/v
					if (!isFirst) esp_printf(putc, ", ");

					esp_printf(putc, "%s=%d", curr->key, curr->val);
					isFirst = 0; // set flag for all subsequent entries
					curr = curr->next;
			}
		}
	}
	esp_printf(putc,"}\n");
}





	




















