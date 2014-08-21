#ifndef BENCHMARKING_ALGORITHMS
#define BENCHMARKING_ALGORITHMS

#include <chrono>
#include "options.h"

std::chrono::high_resolution_clock::time_point get_time_point();
void random_fill(int *arr, unsigned int len, int min, int max);
int  number_width(int number);
void print_array(int *arr, unsigned int len, int number_width);
void benchmark_wrap(const options& opt, benchmark_results& result, void(*benchmark) (int *arr, unsigned int len, const options& opt, benchmark_results& result));
void bubble_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result);
void insertion_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result);
void merge_benchmark(int *arr, unsigned int len, const options& opt, benchmark_results& result);

#endif