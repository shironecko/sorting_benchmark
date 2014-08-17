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
		for ( ; j >= 1; j--)
		{
			if (arr[j] > current)
				arr[j + 1] = arr[j];
			else
				break;
		}

		arr[j + 1] = current;
	}
}