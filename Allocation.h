/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
creates a basic memory allocator, non-optimized, that can fulll memory requests made$
Program #4
*/
#ifndef ALLOCATION_H
#define ALLOCATION_H
#include<stdio.h>

struct Allocation_t
{
	size_t offset;
	size_t allocationSize;
};
void makeAllocation(struct Allocation_t* it, size_t start, size_t size);
void freeAllocation(struct Allocation_t*);
size_t getStart(struct Allocation_t* it);
size_t getEnd(struct Allocation_t* it);
size_t getSize(struct Allocation_t* it);
int doesOverlap(struct Allocation_t* it, size_t start, size_t size);

#endif
