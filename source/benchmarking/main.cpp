#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <map>
#include <boost/program_options.hpp>

#include "options.h"
#include "benchmark.h"
#include "time_helper.h"

namespace opt = boost::program_options;
namespace chrono = std::chrono;
namespace th = time_helper;
using std::cout;
using std::cerr;
using std::endl;
using std::setw;

options g_options;

void print_time(std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period> time);

int main(int argc, char* argv[])
{
	// command-line arguments
	opt::options_description opt_desc("Allowed options");
	opt_desc.add_options()
		("algorithm,a", opt::value<std::string>(&g_options.algorithm)->default_value("bubble"), "algorithm used for benchmarking")
		("iterations,i", opt::value<unsigned int>(&g_options.iterations)->default_value(1000), "number of iterations taken")
		("array-size,s", opt::value<unsigned int>(&g_options.array_size)->default_value(10000), "size of the test array")
		("min", opt::value<int>(&g_options.arr_min_num)->default_value(0), "minimum value of digits in array")
		("max", opt::value<int>(&g_options.arr_max_num)->default_value(100), "maximum value of digits in array")
		("test,t", opt::value<bool>(&g_options.test)->implicit_value(true)->default_value(false), "enables testing of sorted arrays for order and integrity")
		("verbosity,v", opt::value<int>(&g_options.verbosity_level)->default_value(2), "amount of info printed")
		("help,h", "outputs some help info");

	opt::variables_map var_map;
	opt::store(opt::parse_command_line(argc, argv, opt_desc), var_map);
	opt::notify(var_map);

	if (var_map.count("help") > 0)
	{
		cout << opt_desc << endl;
		return 0;
	}

	// benchmark map
	std::map<std::string, void(*)(int *arr, unsigned int len, const options& opt, benchmark_results& result)> benchmark_map;
	benchmark_map["bubble"] = bubble_benchmark;
	benchmark_map["insertion"] = insertion_benchmark;
	benchmark_map["merge"] = merge_benchmark;

	// runing benchmark
	auto benchmark = benchmark_map[g_options.algorithm];
	if (benchmark == nullptr)
	{
		cerr << "No such algorithm: " << g_options.algorithm << endl;
		return 1;
	}

	cout << "Algorithm : " << g_options.algorithm << endl << endl;

	benchmark_results result;
	std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period> total_time, min_time, max_time;
	unsigned int integrity = 0, sorted = 0;

	for (unsigned int i = 0; i < g_options.iterations; i++)
	{
		benchmark_wrap(g_options, result, benchmark);
		total_time += result.time_taken;
		if (result.test_integrity) integrity++;
		if (result.test_sorted) sorted++;

		if (result.time_taken < min_time || min_time == min_time.zero())
			min_time = result.time_taken;
		if (result.time_taken > max_time)
			max_time = result.time_taken;

		if (g_options.verbosity_level >= 1)
			cout << "Time taken: ";

		if (g_options.verbosity_level >= 0)
			cout << chrono::duration_cast<chrono::seconds>(total_time).count() << ":"
				<< chrono::duration_cast<chrono::milliseconds>(total_time).count() % 1000 << endl << endl;
	}

	if (g_options.test)
	{
		cout << "Integrity : " << setw(number_width(g_options.iterations)) << integrity << "/" << g_options.iterations << endl;
		cout << "Sorted    : " << setw(number_width(g_options.iterations)) << sorted << "/" << g_options.iterations << endl;
	}

	cout << "Min time     : " << th::to_string(min_time) << " | ";
	print_time(min_time);
	cout << "Max time     : " << th::to_string(max_time) << " | ";
	print_time(max_time);
	cout << "Average time : " << th::to_string(total_time / g_options.iterations) << " | ";
	print_time(total_time / g_options.iterations);
	cout << "Total time   : " << th::to_string(total_time) << " | ";
	print_time(total_time);
}

void print_time(std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period> time)
{
	cout << setw(3) << chrono::duration_cast<chrono::seconds>(time).count() << ":"
		<< setw(3) << chrono::duration_cast<chrono::milliseconds>(time).count() % 1000 << ":"
		<< setw(3) << chrono::duration_cast<chrono::microseconds>(time).count() % 1000 << endl;
}