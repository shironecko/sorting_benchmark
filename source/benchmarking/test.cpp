#include <unordered_map>
#include "test.h"

void test(pipeline_data& data)
{
	data.test_integrity = integrity_test(data.unsorted_array, data.sorted_array, data.array_size);
	data.test_sorted = sort_test(data.sorted_array, data.array_size);
}

bool integrity_test(int *unsorted, int *sorted, unsigned int len)
{
	std::unordered_map<unsigned int, int> counts;
	for (unsigned int i = 0; i < len; i++)
	{
		counts[unsorted[i]]++;
		counts[sorted[i]]--;
	}

	for (auto count: counts)
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