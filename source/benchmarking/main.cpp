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
#include "statistics.h"
#include "test.h"

using namespace std;
using namespace time_helper;


int main(int argc, char* argv[])
{
	options opts = initialize_options(argc, argv);

	// benchmark map
	std::map<std::string, void(*)(pipeline_data& data)> benchmark_map;
	benchmark_map["bubble"] = benchmark_bubble;
	benchmark_map["insertion"] = benchmark_insertion;
	benchmark_map["merge"] = benchmark_merge;

	// checking if the user specified a valid algorithm for benchmarking
	auto benchmark = benchmark_map[opts.algorithm];
	if (benchmark == nullptr)
	{
		cerr << "No such algorithm: " << opts.algorithm << endl;
		return 1;
	}

	cout << "Algorithm : " << opts.algorithm << endl << endl;

	// prepairing pipeline
	vector<void(*)(pipeline_data& data)> pipeline;
	pipeline.push_back(prepare_array);
	pipeline.push_back(benchmark);
	pipeline.push_back(aggregate_statistics);

	if (opts.test)
		pipeline.push_back(test);

	// prepairing pipeline data
	pipeline_data data{};
	data.array_size = opts.array_size;
	data.unsorted_array = new int[data.array_size];
	data.sorted_array = new int[data.array_size];
	data.min_number = opts.arr_min_num;
	data.max_number = opts.arr_max_num;

	// misc testing statistical vars
	unsigned int integrity = 0, sorted = 0;

	// the pipeline itself
	for (unsigned int i = 0; i < opts.iterations; i++)
	{
		cout << "\r" << int((double)i / (double)opts.iterations * 100.0) << "%...";

		for (auto step : pipeline)
			step(data);

		if (data.test_integrity) integrity++;
		if (data.test_sorted) sorted++;

		if (opts.verbosity_level >= 2)
			cout << "Time taken: ";

		if (opts.verbosity_level >= 1)
			cout << to_string(data.time_taken) << endl;
	}

	// clearing data
	delete[] data.unsorted_array;
	delete[] data.sorted_array;

	cout << "\r100%..." << endl << endl;

	if (opts.test)
	{
		cout << "Integrity : " << integrity << "/" << get_iterations() << endl;
		cout << "Sorted    : " << sorted << "/" << get_iterations() << endl;
	}

	cout << "Min time     : " << to_string(get_min_duration()) << endl;
	cout << "Max time     : " << to_string(get_max_duration()) << endl;
	cout << "Average time : " << to_string(get_avg_duration()) << endl;
	cout << "Total time   : " << to_string(get_total_duration()) << endl;
}