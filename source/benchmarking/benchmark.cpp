#include <chrono>
#include <random>
#include "benchmark.h"
#include "options.h"
#include "sorting.h"

namespace chrono = std::chrono;

inline std::chrono::high_resolution_clock::time_point get_time_point()
{
	return chrono::high_resolution_clock::now();
}

void random_fill(int *arr, unsigned int len, int min, int max)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(min, max);

	for (unsigned int i = 0; i < len; i++)
	{
		arr[i] = distribution(generator);
	}
}

void benchmark_wrap(const options& opt, benchmark_results& result, void(*benchmark) (int *arr, unsigned int len, const options& opt, benchmark_results& result))
{
	int *arr = new int[opt.array_size];
	random_fill(arr, opt.array_size, opt.arr_min_num, opt.arr_max_num);

	auto start = chrono::high_resolution_clock::now();
	benchmark(arr, opt.array_size, opt, result);
	auto end = chrono::high_resolution_clock::now();

	result.time_taken = end - start;
	delete[] arr;
}

void bubble_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result)
{
	bubble_sort(arr, len);
}

void insertion_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result)
{
	insertion_sort(arr, len);
}