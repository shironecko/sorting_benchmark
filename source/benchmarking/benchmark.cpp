#include <iostream>
#include <chrono>
#include <random>
#include "benchmark.h"
#include "options.h"
#include "test.h"

extern "C"
{
	#include "sorting.h"
}

namespace chrono = std::chrono;
using std::cout;
using std::endl;

inline std::chrono::high_resolution_clock::time_point get_time_point()
{
	return chrono::high_resolution_clock::now();
}

void random_fill(int *arr, unsigned int len, int min, int max)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(min, max);

	generator.seed(unsigned long(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count()));

	for (unsigned int i = 0; i < len; i++)
	{
		arr[i] = distribution(generator);
	}
}

int number_width(int number)
{
	int width = 1;

	while ((number /= 10) > 0)
		width++;

	return width;
}

void print_array(int *arr, unsigned int len, int number_width)
{
	cout << "{";

	for (unsigned int i = 0; i < len; i++)
	{
		cout.width(number_width);
		cout << arr[i];
	}

	cout << " }";
}

void benchmark_wrap(const options& opt, benchmark_results& result, void(*benchmark) (int *arr, unsigned int len, const options& opt, benchmark_results& result))
{
	int *arr = new int[opt.array_size];
	random_fill(arr, opt.array_size, opt.arr_min_num, opt.arr_max_num);

	int *backup = nullptr;
	if (opt.test)
	{
		backup = new int[opt.array_size];
		for (unsigned int i = 0; i < opt.array_size; i++)
			backup[i] = arr[i];
	}

	auto start = chrono::high_resolution_clock::now();
	benchmark(arr, opt.array_size, opt, result);
	auto end = chrono::high_resolution_clock::now();

	result.time_taken = end - start;
	if (opt.test)
	{
		if (opt.verbosity_level >= 2)
		{
			print_array(backup, opt.array_size, number_width(opt.arr_max_num) + 1);
			cout << endl;
			print_array(arr, opt.array_size, number_width(opt.arr_max_num) + 1);
			cout << endl;
		}

		result.test_sorted = sort_test(arr, opt.array_size);
		result.test_integrity = integrity_test(backup, arr, opt.array_size);

		if (opt.verbosity_level >= 1)
		{
			cout << "Sorted    : " << (result.test_sorted ? "OK" : "FAIL") << endl;
			cout << "Integrity : " << (result.test_integrity ? "OK" : "FAIL") << endl;
		}
	}

	delete[] arr;
	delete[] backup;
}

void bubble_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result)
{
	bubble_sort(arr, len);
}

void insertion_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result)
{
	insertion_sort(arr, len);
}

void merge_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result)
{
	int* buff = new int[len];

	if (merge_sort(arr, buff, 0, len -1) != arr)
	{
		for (unsigned int i = 0; i < len; i++)
			arr[i] = buff[i];
	}

	delete[] buff;
}