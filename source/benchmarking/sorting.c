#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sorting.h"

void swap(int* arr, unsigned int ai, unsigned int bi)
{
	int temp = arr[ai];
	arr[ai] = arr[bi];
	arr[bi] = temp;
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

void selection_sort(int *arr, unsigned int len)
{
	for (unsigned int i = 0; i < len - 1; i++)
	{
		int min = i;

		for (unsigned int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}

		swap(arr, i, min);
	}
}

/*
 * Sorts an array using recursive merge sort with no additional memory allocations
 * up - pointer to array to sort
 * down - pointer to an empty array with the same size as 'up', used as buffer
 * left - pass 0 to sort an array from the very begining
 * right - pass the length of the 'up' - 1 to sort the whole array
 * returns: pointer to the sorted array, this will be equal to either 'up' or 'down'
 * Note: take notice that sorted version of the array may end up either in 'up' or 'down'
 */
int* merge_sort(int *up, int *down, unsigned int left, unsigned int right)
{

	if (left == right)
	{
		down[left] = up[left];
		return down;
	}

	unsigned int middle = (unsigned int)((left + right) * 0.5f);

	// divide and sort
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

void count_sort(int *arr, unsigned int len, int min_num, int max_num)
{
	unsigned int arr_size = sizeof(int) * len;
	int* copy = malloc(arr_size);
	memcpy(copy, arr, arr_size);

	unsigned int pos_size = sizeof(int) * (max_num - min_num);
	int* positions = malloc(pos_size);
	memset(positions, 0, pos_size);

	// just for a moment positions array will store count of distinct number in the array
	for (unsigned int i = 0; i < len; i++)
		++positions[copy[i]];

	// now well calculate actual positions of the elements
	for (unsigned int i = 1; i < pos_size; i++)
		positions[i] += positions[i - 1] + min_num;

	for (unsigned int i = 0; i < len; i++)
	{
		unsigned int position = positions[copy[i]]++;
		arr[position] = copy[i];
	}

	free(copy);
}