#ifndef SORTING_ALGORITHMS
#define SORTING_ALGORITHMS

void swap(int* arr, int a, int b);
void bubble_sort(int *arr, unsigned int len);
void insertion_sort(int *arr, unsigned int len);
int* merge_sort(int *up, int *down, unsigned int left, unsigned int right);

#endif