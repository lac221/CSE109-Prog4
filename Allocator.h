/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
creates a basic memory allocator, non-optimized, that can fulll memory requests made$
Program #4
*/
#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include<stdlib.h>


struct Allocator_t
{
	void* memory;
	size_t memCapacity;
	size_t amountAllocated;
	struct Allocation_t** list;
	size_t capacity;
	size_t size;
};

void makeAllocator(struct Allocator_t* it, size_t capacity);
void freeAllocator(struct Allocator_t* it);
void* allocate(struct Allocator_t* it, size_t amt);
void addAllocation(struct Allocator_t* it, struct Allocation_t* newAlloc);
void deallocate(struct Allocator_t* it, void* ptr);
void* getBase(struct Allocator_t* it);
size_t getUsed(struct Allocator_t* it);
size_t getCapacity(struct Allocator_t* it);
struct Allocation_t* getAllocation(struct Allocator_t* it, size_t index);
size_t numAllocations(struct Allocator_t* it);
void* riskyAlloc(struct Allocator_t*, size_t size);

#endif


