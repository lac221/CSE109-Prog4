/*
CSE 109: Fall 2018
Lydia Cornwell
LAC221
creates a basic memory allocator, non-optimized, that can fulll memory requests made by users.
Program #4
*/
#include"Allocation.h"
#include<stdio.h>
#include<stdlib.h>

void makeAllocation(struct Allocation_t* it, size_t start, size_t size)
{
	it->offset = start;
	it->allocationSize = size;
}

void freeAllocation(struct Allocation_t* it)
{
	it->offset = 0;
	it->allocationSize = 0;
}

size_t getStart(struct Allocation_t* it)
{
	return it->offset;
}

size_t getEnd(struct Allocation_t* it)
{
	return ((it->offset) + (it->allocationSize));
	//maybe -1
}

size_t getSize(struct Allocation_t* it)
{
	return it->allocationSize;
}

int doesOverlap(struct Allocation_t* it, size_t start, size_t size)
{
	size_t min = 0;
	size_t max = 0;

	if(getStart(it) < start)
	{
		min = it->offset;
	}
	else if(start < getStart(it))
	{
		min = start;
	}
	else if(start == getStart(it))
	{
		return 1;
	}

	if(getEnd(it) < (start + size))
	{
		max = (start + size);
	}
	if(getEnd(it) > (start + size))
	{
		max = getEnd(it);
	}
	else if(getEnd(it) == (start + size))
	{
		return 1;
	}

	if((max - min) < (size + it->allocationSize))
	{
		return 1;
	}
	return 0;
}


