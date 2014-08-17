#include <map>
#include "test.h"

bool integrity_test(int *unsorted, int *sorted, unsigned int len)
{
	return false;
}

bool sort_test(int *arr, unsigned int len)
{
	for (unsigned int i = 0; i < len - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}