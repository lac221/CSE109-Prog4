
CC=gcc

CFLAGS=-g -Wall -Werror -c

SRCS=Allocator.c Allocation.c

OBJS=$(SRCS:.c=.o)

HEADERS=Allocator.h Allocation.h printAllocations.h

EXE=prog4

all: $(EXE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(EXE): $(OBJS)
	$(CC) $(OBJS) prog4.o -o $@



