#ifndef SORTING_ALGORITHMS
#define SORTING_ALGORITHMS

void swap(int* arr, unsigned int ai, unsigned int bi);

// O(n^2)
void bubble_sort(int *arr, unsigned int len);
void insertion_sort(int *arr, unsigned int len);
void selection_sort(int *arr, unsigned int len);

// O(n log n)
int* merge_sort(int *up, int *down, unsigned int left, unsigned int right);

// O(n)
void count_sort(int* arr, int* buff, unsigned int len, int min_num, int max_num);

#endif