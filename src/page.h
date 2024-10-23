#include "rprintf.h"
#include "serial.h"

#define PAGE_COUNT 128

struct ppage {
	struct ppage *next;
	struct ppage *prev;
	void *physAddr;
};

struct ppage *physPageArray[PAGE_COUNT];
struct ppage *freeList = NULL;

void init_pfa_list(void);
struct ppage *allocatePhysPages(unsigned int npages);
void freePhysPages(struct ppage *ppageList);
void printFreeList(void);
