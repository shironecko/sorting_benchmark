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

int* merge_sort(int *up, int *down, unsigned int left, unsigned int right)
{
	if (left == right)
	{
		down[left] = up[left];
		return down;
	}

	unsigned int middle = (unsigned int)((left + right) * 0.5f);

	int *l_buff = merge_sort(up, down, left, middle);
	int *r_buff = merge_sort(up, down, middle + 1, right);

	// merge
	int *target = l_buff == up ? down : up;

	unsigned int width = right - left, l_cur = left, r_cur = middle + 1;
	for (unsigned int i = left; i <= right; i++)
	{
		if (l_cur <= middle && r_cur <= right)
		{
			if (l_buff[l_cur] < r_buff[r_cur])
			{
				target[i] = l_buff[l_cur];
				l_cur++;
			}
			else
			{
				target[i] = r_buff[r_cur];
				r_cur++;
			}
		}
		else if (l_cur <= middle)
		{
			target[i] = l_buff[l_cur];
			l_cur++;
		}
		else
		{
			target[i] = r_buff[r_cur];
			r_cur++;
		}
	}

	return target;
}