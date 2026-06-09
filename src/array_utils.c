#include "array_utils.h"
#include <stdlib.h>
#include <string.h>

static void swapInt(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static void fisherYatesShuffle(int arr[], int n, unsigned int seed){
  srand(seed);
  for(int i = n - 1; i > 0; --i){
    int j = rand() % (i + 1);
    swapInt(&arr[i], &arr[j]);
  }
}

int parseInputType(const char inputTypeName[], InputType *inputType){
  if(strcmp(inputTypeName, "random") == 0){
    *inputType = INPUT_RANDOM;
    return 1;
  }
  if(strcmp(inputTypeName, "sorted") == 0){
    *inputType = INPUT_SORTED;
    return 1;
  }
  if(strcmp(inputTypeName, "reversed") == 0){
    *inputType = INPUT_REVERSED;
    return 1;
  }
  if(strcmp(inputTypeName, "repeated") == 0){
    *inputType = INPUT_REPEATED;
    return 1;
  }
  return 0;
}

const char *inputTypeToString(InputType inputType){
  switch(inputType){
    case INPUT_RANDOM: return "random";
    case INPUT_SORTED: return "sorted";
    case INPUT_REVERSED: return "reversed";
    case INPUT_REPEATED: return "repeated";
  }
  return "unknown";
}

void fillArray(int arr[], int n, InputType inputType, unsigned int seed){
  if(inputType == INPUT_RANDOM){
    for(int i = 0; i < n; ++i)
      arr[i] = i + 1;
    fisherYatesShuffle(arr, n, seed);
    return;
  }

  if(inputType == INPUT_SORTED){
    for(int i = 0; i < n; ++i)
      arr[i] = i + 1;
    return;
  }

  if(inputType == INPUT_REVERSED){
    for(int i = 0; i < n; ++i)
      arr[i] = n - i;
    return;
  }

  srand(seed);
  for(int i = 0; i < n; ++i)
    arr[i] = rand() % 100;
}

void copyArray(int dest[], const int src[], int n){
  for(int i = 0; i < n; ++i)
    dest[i] = src[i];
}

int isSorted(const int arr[], int n){
  for(int i = 1; i < n; ++i){
    if(arr[i - 1] > arr[i])
      return 0;
  }
  return 1;
}
