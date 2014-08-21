#include <cstdlib>
#include <ctime>
#include "array_prepare.h"

void prepare_array(pipeline_data& data)
{
	srand((unsigned int)time(nullptr));

	for (unsigned int i = 0; i < data.array_size; i++)
		data.unsorted_array[i] = rand() % (data.max_number + 1 - data.min_number) + data.min_number;

	memcpy(data.sorted_array, data.unsorted_array, sizeof(int) * data.array_size);
}