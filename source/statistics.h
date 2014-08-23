#ifndef BENCHMARKING_STATISTICS_AGREGGATION
#define BENCHMARKING_STATISTICS_AGREGGATION

#include "statistics.h"
#include "pipeline_data.h"
#include "time_helper.h"

using namespace time_helper;

void aggregate_statistics(pipeline_data& data);

unsigned int get_iterations();

duration get_min_duration();
duration get_max_duration();
duration get_avg_duration();
duration get_total_duration();

#endif