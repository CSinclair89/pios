#ifndef PAGE_H
#define PAGE_H

#include "rprintf.h"
#include "serial.h"

#define PAGE_COUNT 128

struct ppage {
	struct ppage *next;
	struct ppage *prev;
	void *physAddr;
};

extern struct ppage physPageArray[PAGE_COUNT];
extern struct ppage *freeList;

void init_pfa_list(void);
void printPhysAddr(void);
struct ppage *allocatePhysPages(unsigned int npages);
void freePhysPages(struct ppage *ppageList);
void printFreeList(void);

#endif
