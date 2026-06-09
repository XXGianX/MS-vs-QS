#include "sort.h"

static void swapInt(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static int partition(int arr[], int left, int right){
  int pivot = arr[right];
  int i = left - 1;

  for(int j = left; j < right; j++){
    if(arr[j] <= pivot){
      i++;
      swapInt(&arr[i], &arr[j]);
    }
  }
  swapInt(&arr[i + 1], &arr[right]);
  return i + 1;
}

static void quickSortRange(int arr[], int left, int right){
  if(left >= right)
    return;

  int pivotIndex = partition(arr, left, right);
  quickSortRange(arr, left, pivotIndex - 1);
  quickSortRange(arr, pivotIndex + 1, right);
}

void quickSort(int arr[], int n){
  if(n <= 1)
    return;
  quickSortRange(arr, 0, n - 1);
}
