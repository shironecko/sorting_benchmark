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
#include "output.h"

using namespace std;
using namespace time_helper;
namespace output = benchmark_output;


int main(int argc, char* argv[])
{
	options opts = initialize_options(argc, argv);

	// benchmark map
	std::map<std::string, void(*)(pipeline_data& data)> benchmark_map;
	benchmark_map["bubble"] = benchmark_bubble;
	benchmark_map["insertion"] = benchmark_insertion;
	benchmark_map["selection"] = benchmark_selection;
	benchmark_map["merge"] = benchmark_merge;

	// checking if the user specified a valid algorithm for benchmarking
	auto benchmark = benchmark_map[opts.algorithm];
	if (benchmark == nullptr)
	{
		cerr << "No such algorithm: " << opts.algorithm << endl;
		return 1;
	}

	// prepairing pipeline
	vector<void(*)(pipeline_data& data)> pipeline;
	pipeline.push_back(prepare_array);
	pipeline.push_back(benchmark);
	pipeline.push_back(aggregate_statistics);

	if (opts.test)
		pipeline.push_back(test);

	// printing greeting according to output mode and adding appropriate output method to the pipeline
	if (opts.output == "hs")
	{
		pipeline.push_back(output::human_sparse);
		output::human_sparse_greetings(opts);
	}
	else if (opts.output == "hv")
	{
		pipeline.push_back(output::human_verbose);
		output::human_verbose_greetings(opts);
	}
	else if (opts.output == "m")
		pipeline.push_back(output::machine);
	else
	{
		cout << "Unknown output mode: " << opts.output << endl;
		exit(2);
	}

	// prepairing pipeline data
	pipeline_data data{};
	data.array_size = opts.array_size;
	data.unsorted_array = new int[data.array_size];
	data.sorted_array = new int[data.array_size];
	data.iterations = opts.iterations;
	data.min_number = opts.arr_min_num;
	data.max_number = opts.arr_max_num;
	data.test = opts.test;

	// misc testing statistical vars
	unsigned int integrity = 0, sorted = 0;

	// the pipeline itself
	for (unsigned int i = 0; i < opts.iterations; i++)
	{
		data.iteration = i;

		for (auto step : pipeline)
			step(data);
	}

	// presenting the report according to the set output tipe
	if (opts.output == "hs")
		output::human_sparse_report(data);
	else if (opts.output == "hv")
		output::human_verbose_report(data);

	// clearing data
	delete[] data.unsorted_array;
	delete[] data.sorted_array;
}