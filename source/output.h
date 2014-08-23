#ifndef BENCHMARKING_OUTPUT
#define BENCHMARKING_OUTPUT

#include "pipeline_data.h"
#include "options.h"

namespace benchmark_output
{
	void human_sparse(pipeline_data& data);
	void human_sparse_greetings(const options& opts);
	void human_sparse_report(const pipeline_data& data);
	void human_verbose(pipeline_data& data);
	void human_verbose_greetings(const options& opts);
	void human_verbose_report(const pipeline_data& data);
	void machine(pipeline_data& data);
}

#endif