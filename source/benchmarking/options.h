#ifndef BENCHMARK_OPTIONS
#define BENCHMARK_OPTIONS

#include <string>

struct options
{
	std::string algorithm;
	unsigned int iterations;
	unsigned int array_size;
	int arr_min_num;
	int arr_max_num;
	bool test;
	bool no_echo;
};

#endif