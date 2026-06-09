CC=gcc
CFLAGS=-O2 -std=c11 -Wall -Wextra -pedantic -Iinclude
LDFLAGS=-lm

SRC=src/main.c src/array_utils.c src/mergesort.c src/quicksort.c src/timer.c
OBJ=$(SRC:.c=.o)

all: experiment

experiment: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o experiment $(LDFLAGS)

run: experiment
	bash scripts/runExperiment.sh

test: experiment
	@echo "algorithm,inputType,n,seed,timeSeconds,sorted"
	@./experiment merge random 10000 101
	@./experiment quick random 10000 101
	@./experiment merge sorted 10000 101
	@./experiment quick sorted 10000 101

clean:
	rm -f experiment $(OBJ)
	rm -f results/*.csv results/*.png

.PHONY: all run test clean
