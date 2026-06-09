#include "sort.h"
#include <stdlib.h>

static void merge(int arr[], int aux[], int left, int mid, int right){
  int i = left;
  int j = mid + 1;
  int k = left;

  while(i <= mid && j <= right){
    if(arr[i] <= arr[j])
      aux[k++] = arr[i++];
    else
      aux[k++] = arr[j++];
  }

  while(i <= mid)
    aux[k++] = arr[i++];

  while(j <= right)
    aux[k++] = arr[j++];

  for(i = left; i <= right; ++i)
    arr[i] = aux[i];
}

static void mergeSortRange(int arr[], int aux[], int left, int right){
  if(left >= right)
    return;

  int mid = left + (right - left) / 2;
  mergeSortRange(arr, aux, left, mid);
  mergeSortRange(arr, aux, mid + 1, right);
  merge(arr, aux, left, mid, right);
}

void mergeSort(int arr[], int n){
  if(n <= 1)
    return;

  int *aux = malloc((size_t)n * sizeof(int));
  if(aux == NULL)
    return;

  mergeSortRange(arr, aux, 0, n - 1);
  free(aux);
}
