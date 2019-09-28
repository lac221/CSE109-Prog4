/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
creates a basic memory allocator, non-optimized, that can fulll memory requests made$
Program #4
*/
#include "Allocator.h"
#include "Allocation.h"
#include<stdio.h>
#include<stdlib.h>

void makeAllocator(struct Allocator_t* it, size_t capacity)
{
	// cap = (((cap - 1) / 16) + 1) * 16;
	if(capacity % 16 != 0)
	{
		int remainder = capacity % 16;
		capacity = capacity + 16 - remainder;
	}

	it->memory = (void*) malloc(capacity);
	it->memCapacity = capacity;
	it->amountAllocated = 0;
	it->list = NULL;
	it->capacity = 0;
	it->size = 0;
}

void freeAllocator(struct Allocator_t* it)
{
	for(int i = 0; i < it->size; i++)
	{
		free(it->list[i]);
		it->list[i] = NULL;
	}

	free(it->list);
	it->list = NULL;
	free(it->memory);
	it->memory = NULL;
}

void* allocate(struct Allocator_t* it, size_t amt)
{
	if(amt < 0 || it == NULL)
	{
		return NULL;
	}

	amt = (((amt - 1) / 16) + 1) * 16;
	if(amt > it->memCapacity)
	{
		return NULL;
	}

	int counter = 0;

	// expand list if needed

	for(int i = 0; i <= it->memCapacity - amt; i += 16)
	{
		counter = 0;
		for(int j = 0; j < it->size; j++)
		{
			if(doesOverlap(it->list[j], i, amt))
			{
				counter = 1;
				break;
			}
		}

		if(counter == 0)
		{
			// malloc new allocation
			struct Allocation_t* temp = (struct Allocation_t*)malloc(sizeof(struct Allocation_t));
			// makeAllocation
			makeAllocation(temp, i, amt);
			// add to list
			addAllocation(it, temp);
			// return pointer
			return ((char*)it->memory) + i;
		}
	}

	return NULL;
}

void addAllocation(struct Allocator_t* it, struct Allocation_t* newAlloc)
{
    if(it->size >= it->capacity)
    {
     	size_t newCap = (2 * (it->capacity) + 1);
        struct Allocation_t** newList = (struct Allocation_t**)malloc(newCap * sizeof(struct Allocation_t*));
        for(int i = 0; i < it->size; i++)
        {
            newList[i] = it->list[i];
        }
        free(it->list);
        it->list = newList;
        it->capacity = newCap;
    }
    it->list[it->size] = newAlloc;
    it->size += 1;
	it->amountAllocated += getSize(newAlloc);
    return;
}

void deallocate(struct Allocator_t* it, void* ptr)
{
	if(it == NULL || ptr == NULL)
	{
		return;
	}

	int start = (int)(((char*)ptr) - ((char*)it->memory));

	if(start < 0 || start > it->memCapacity)
	{
		fprintf(stderr, "Corruption in free\n");
		exit(1);
	}

	for(int i = 0; i < it->size; i++)
	{
		if(start == getStart(it->list[i]))
		{
			// decrement amtallocated
			it->amountAllocated -= getSize(it->list[i]);
			// free list[i]
			free(it->list[i]);
			// move everything back
			it->list[i] = it->list[it->size - 1];
			it->list[it->size - 1] = NULL;
			// decrement size
			it->size -= 1;
			// return
			return;
		}
	}

	fprintf(stderr, "Corruption in free\n");
	exit(1);
}

void* getBase(struct Allocator_t* it)
{
	return it->memory;
}

size_t getUsed(struct Allocator_t* it)
{
	return it-> amountAllocated;
}

size_t getCapacity(struct Allocator_t* it)
{
	return it->memCapacity;
}

struct Allocation_t* getAllocation(struct Allocator_t* it, size_t index)
{
	if(index >= it->size)
	{
		return NULL;
	}

	return it->list[index];
}

size_t numAllocations(struct Allocator_t* it)
{
	return it->size;
}

void* riskyAlloc(struct Allocator_t* it, size_t size)
{
	void* alloc = allocate(it, size);
	if(alloc != NULL)
	{
		return alloc;
	}

	void* newMemory = realloc(it->memory, it->memCapacity + size);
	it->memCapacity += size;

	if(newMemory != it->memory)
	{
		it->memory = newMemory;
		fprintf(stderr, "Bad realloc/n");
		return NULL;
	}

	return allocate(it, size);
}


