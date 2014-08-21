#include <iostream>
#include "output.h"
#include "options.h"
#include "pipeline_data.h"
#include "statistics.h"

using namespace std;

namespace benchmark_output
{
	// internal
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
			cout.width(number_width + 1);
			cout << arr[i];
		}

		cout << " }" << endl;
	}

	// interface
	void human_sparse(pipeline_data& data)
	{
		// display percentage
		cout << "\r" << int((double)data.iteration / (double)data.iterations * 100.0) + 1 << "%...";
	}

	void human_sparse_greetings(const options& opts)
	{
		cout << "Algorithm    : " << opts.algorithm << endl 
			 << "Iterations   : " << opts.iterations << endl
			 << "Array size   : " << opts.array_size << endl
			 << "Numbers      : [" << opts.arr_min_num << ".." << opts.arr_max_num << "]" << endl << endl;
	}

	void human_sparse_report(const pipeline_data& data)
	{
		cout << endl << endl;

		if (data.test)
		{
			cout << "Integrity    : " << data.test_integrity_passed << "/" << get_iterations() << endl;
			cout << "Sorted       : " << data.test_sorted_passed << "/" << get_iterations() << endl;
		}

		cout << "Min time     : " << to_string(get_min_duration(), true) << endl;
		cout << "Max time     : " << to_string(get_max_duration(), true) << endl;
		cout << "Average time : " << to_string(get_avg_duration(), true) << endl;
		cout << "Total time   : " << to_string(get_total_duration()) << endl;
	}

	void human_verbose(pipeline_data& data)
	{
		int num_width = number_width(data.max_number);
		print_array(data.unsorted_array, data.array_size, num_width);
		print_array(data.sorted_array, data.array_size, num_width);

		if (data.test)
		{
			cout << "Integrity  : " << (data.test_integrity ? "OK" : "FAIL") << endl;
			cout << "Sorted     : " << (data.test_sorted ? "OK" : "FAIL") << endl;
		}
		cout << "Time taken : " << to_string(data.time_taken, true) << endl << endl;
	}

	void human_verbose_greetings(const options& opts)
	{
		human_sparse_greetings(opts);
	}

	void human_verbose_report(const pipeline_data& data)
	{
		human_sparse_report(data);
	}

	void machine(pipeline_data& data)
	{
		cout << get_nanoseconds_total(data.time_taken) << endl;
	}
}