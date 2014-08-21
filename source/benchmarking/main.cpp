#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <boost/program_options.hpp>

#include "time_helper.h"
#include "options.h"
#include "pipeline_data.h"
#include "array_prepare.h"
#include "benchmark.h"
#include "test.h"

using namespace std;
using namespace time_helper;
namespace opt = boost::program_options;

options g_options;

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
	std::map<std::string, void(*)(pipeline_data& data)> benchmark_map;
	benchmark_map["bubble"] = benchmark_bubble;
	benchmark_map["insertion"] = benchmark_insertion;
	benchmark_map["merge"] = benchmark_merge;

	// checking if the user specified a valid algorithm for benchmarking
	auto benchmark = benchmark_map[g_options.algorithm];
	if (benchmark == nullptr)
	{
		cerr << "No such algorithm: " << g_options.algorithm << endl;
		return 1;
	}

	cout << "Algorithm : " << g_options.algorithm << endl << endl;

	// prepairing pipeline
	vector<void(*)(pipeline_data& data)> pipeline;
	pipeline.push_back(prepare_array);
	pipeline.push_back(benchmark);

	if (g_options.test)
		pipeline.push_back(test);

	// prepairing pipeline data
	pipeline_data data{};
	data.array_size = g_options.array_size;
	data.unsorted_array = new int[data.array_size];
	data.sorted_array = new int[data.array_size];
	data.min_number = g_options.arr_min_num;
	data.max_number = g_options.arr_max_num;

	// misc statistical vars
	duration total_time, min_time, max_time;
	unsigned int integrity = 0, sorted = 0;

	// the pipeline itself
	for (unsigned int i = 0; i < g_options.iterations; i++)
	{
		for (auto step : pipeline)
			step(data);

		total_time += data.time_taken;

		if (data.time_taken < min_time || min_time == min_time.zero())
			min_time = data.time_taken;
		if (data.time_taken > max_time)
			max_time = data.time_taken;

		if (data.test_integrity) integrity++;
		if (data.test_sorted) sorted++;

		if (g_options.verbosity_level >= 2)
			cout << "Time taken: ";

		if (g_options.verbosity_level >= 1)
			cout << to_string(data.time_taken) << endl;
	}

	// clearing data
	delete[] data.unsorted_array;
	delete[] data.sorted_array;

	if (g_options.test)
	{
		cout << "Integrity : " << integrity << "/" << g_options.iterations << endl;
		cout << "Sorted    : " << sorted << "/" << g_options.iterations << endl;
	}

	cout << "Min time     : " << to_string(min_time) << endl;
	cout << "Max time     : " << to_string(max_time) << endl;
	cout << "Average time : " << to_string(total_time / g_options.iterations) << endl;
	cout << "Total time   : " << to_string(total_time) << endl;
}