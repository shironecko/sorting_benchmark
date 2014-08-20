#include <stdbool.h>
#include <stdlib.h>
#include "sorting.h"

void swap(int* arr, int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void bubble_sort(int *arr, unsigned int len)
{
	bool swapped = true;

	for (unsigned int i = len - 1; i >= 0 && swapped; i--)
	{
		swapped = false;

		for (unsigned int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr, j, j + 1);
				swapped = true;
			}
		}
	}
}

void insertion_sort(int *arr, unsigned int len)
{
	for (unsigned int i = 1; i < len; i++)
	{
		int current = arr[i];

		unsigned int j = i - 1;
		for ( ; j >= 0; j--)
		{
			if (arr[j] > current)
				arr[j + 1] = arr[j];
			else
				break;
		}

		arr[j + 1] = current;
	}
}

/*void merge_sort(int *arr, int *buff, int start, int end)
{
	int width = end - start;

	if (width == 0)
	{
		buff[start] = arr[start];
		return;
	}

	int middle = start + (start - end) * 0.5f;
	merge_sort(arr, buff, start, middle);
	merge_sort(arr, buff, middle + 1, end);


}*/

void make_merge(int *arr, int left, int mid, int right, int len)
{ 
	int *tmp = malloc(sizeof(int) * len);

	int count = 0; 
	int i = left;
	int j = mid + 1; 

	for (int step = 0; step < right - left + 1; step++)
	{ 
		if ((j > right) || ((i <= mid) && (arr[i] < arr[j])))
		{ 
			count += j - (mid + 1); 
			tmp[step] = arr[i]; i++; 
		} 
		else 
		{ 
			tmp[step] = arr[j]; 
			j++; 
		} 
	} 
	for (int step = 0; step < right - left + 1; ++step)
	{ 
		arr[left + step] = tmp[step]; 
	}

	free(tmp);
} 

void merge_sort(int *arr, int left, int right, int len)
{ 
	if (left == right)
		return;

	int mid = (left + right) / 2;

	merge_sort(arr, left, mid, len);
	merge_sort(arr, mid + 1, right, len);
	make_merge(arr, left, mid, right, len);
}