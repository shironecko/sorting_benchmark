#ifndef BENCHMARKING_ALGORITHMS
#define BENCHMARKING_ALGORITHMS

#include <chrono>
#include "options.h"

struct benchmark_results
{
	std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period> time_taken;
	bool test_sorted;
	bool test_integrity;
};

std::chrono::high_resolution_clock::time_point get_time_point();
void random_fill(int *arr, unsigned int len, int min, int max);
void benchmark_wrap(const options& opt, benchmark_results& result, void(*benchmark) (int *arr, unsigned int len, const options& opt, benchmark_results& result));
void bubble_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result);
void insertion_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result);

#endif