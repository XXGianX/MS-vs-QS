#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

typedef enum {
  INPUT_RANDOM,
  INPUT_SORTED,
  INPUT_REVERSED,
  INPUT_REPEATED
} InputType;

int parseInputType(const char inputTypeName[], InputType *inputType);
const char *inputTypeToString(InputType inputType);
void fillArray(int arr[], int n, InputType inputType, unsigned int seed);
void copyArray(int dest[], const int src[], int n);
int isSorted(const int arr[], int n);

#endif
