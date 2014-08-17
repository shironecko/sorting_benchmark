#include <unordered_map>
#include "test.h"

bool integrity_test(int *unsorted, int *sorted, unsigned int len)
{
	std::unordered_map<unsigned int, int> counts;
	for (unsigned int i = 0; i < len; i++)
	{
		counts[unsorted[i]]++;
		counts[sorted[i]]--;
	}

	for each (auto count in counts)
	{
		if (count.second != 0)
			return false;
	}

	return true;
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