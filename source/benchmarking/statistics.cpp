#include "statistics.h"
#include "pipeline_data.h"
#include "time_helper.h"

using namespace time_helper;

struct
{
	unsigned int iterations;

	duration min_duration;
	duration max_duration;
	duration total_duration;
} 
statistics
{ 
	0, duration::max(), duration::zero(), duration::zero()
};

void aggregate_statistics(pipeline_data& data)
{
	statistics.iterations++;

	if (data.time_taken < statistics.min_duration)
		statistics.min_duration = data.time_taken;

	if (data.time_taken > statistics.max_duration)
		statistics.max_duration = data.time_taken;

	statistics.total_duration += data.time_taken;
}

unsigned int get_iterations()
{
	return statistics.iterations;
}

duration get_min_duration()
{
	return statistics.min_duration;
}

duration get_max_duration()
{
	return statistics.max_duration;
}

duration get_avg_duration()
{
	return statistics.total_duration / statistics.iterations;
}

duration get_total_duration()
{
	return statistics.total_duration;
}