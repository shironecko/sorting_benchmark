#ifndef BENCHMARKING_PIPELINE_DATA_STRUCTURE
#define BENCHMARKING_PIPELINE_DATA_STRUCTURE

#include "time_helper.h"

using namespace time_helper;

struct pipeline_data
{
	// pointer to the unsorted array
	int* unsorted_array;
	// pointer to the memory block in wich sorted version of the array will be put by the sorting algorithm
	// initially it contains the same data as the unsorted_array
	int* sorted_array;
	// size of the both memory blocks
	unsigned int array_size;

	// time taken by this step, only benchmark itself contributes to it
	duration time_taken;
	
	// these are the indicators of the respective test passage
	bool test_sorted;
	bool test_integrity;
};


#endif