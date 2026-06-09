#include "array_utils.h"
#include "sort.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printUsage(const char programName[]){
  fprintf(stderr, "Uso: %s <quick|merge> <random|sorted|reversed|repeated> <n> <seed>\n", programName);
}

int main(int argc, char *argv[]){
  if(argc != 5){
    printUsage(argv[0]);
    return 1;
  }

  const char *algorithm = argv[1];

  InputType inputType;
  if(!parseInputType(argv[2], &inputType)){
    printUsage(argv[0]);
    return 1;
  }

  int n = atoi(argv[3]);
  unsigned int seed = (unsigned int)strtoul(argv[4], NULL, 10);

  if(n <= 0){
    fprintf(stderr, "El tamaño n debe ser positivo.\n");
    return 1;
  }

  int *arr = malloc((size_t)n * sizeof(int));
  if(arr == NULL){
    fprintf(stderr, "No se pudo reservar memoria.\n");
    return 1;
  }

  fillArray(arr, n, inputType, seed);

  TimePoint start = getTimePoint();

  if(strcmp(algorithm, "quick") == 0)
    quickSort(arr, n);
  else if(strcmp(algorithm, "merge") == 0)
    mergeSort(arr, n);
  else{
    free(arr);
    printUsage(argv[0]);
    return 1;
  }

  TimePoint end = getTimePoint();
  double timeSeconds = elapsedSeconds(start, end);
  int sorted = isSorted(arr, n);

  printf("%s,%s,%d,%u,%.9f,%d\n", algorithm, inputTypeToString(inputType), n, seed, timeSeconds, sorted);

  free(arr);
  return sorted ? 0 : 2;
}
