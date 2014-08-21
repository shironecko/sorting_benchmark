#include "benchmark.h"
#include "pipeline_data.h"
#include "time_helper.h"

extern "C"
{
	#include "sorting.h"
}

using namespace time_helper;

void benchmark_bubble(pipeline_data& data)
{
	time_point start = now();

	bubble_sort(data.sorted_array, data.array_size);

	data.time_taken = now() - start;
}

void benchmark_insertion(pipeline_data& data)
{
	time_point start = now();

	insertion_sort(data.sorted_array, data.array_size);

	data.time_taken = now() - start;
}

void benchmark_selection(pipeline_data& data)
{
	time_point start = now();

	selection_sort(data.sorted_array, data.array_size);

	data.time_taken = now() - start;
}

void benchmark_merge(pipeline_data& data)
{
	time_point start = now();

	int* additional_buff = new int[data.array_size];
	int* sorted_buff = merge_sort(data.sorted_array, additional_buff, 0, data.array_size - 1);

	data.time_taken = now() - start;

	if (sorted_buff != data.sorted_array)
	{
		for (unsigned int i = 0; i < data.array_size; i++)
			data.sorted_array[i] = sorted_buff[i];
	}

	delete[] additional_buff;
}