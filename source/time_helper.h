#ifndef BENCHMARK_TIME_MEASUREMENT_HELPER
#define BENCHMARK_TIME_MEASUREMENT_HELPER

#include <chrono>
#include <string>

using namespace std;

namespace time_helper
{
	typedef chrono::duration < chrono::high_resolution_clock::rep, chrono::high_resolution_clock::period > duration;
	typedef chrono::high_resolution_clock::time_point time_point;

	int get_hours(const duration& dur);
	int get_minutes(const duration& dur);
	long long get_seconds(const duration& dur);
	long long get_milliseconds(const duration& dur);
	long long get_microseconds(const duration& dur);
	long long get_nanoseconds(const duration& dur);
	long long get_nanoseconds_total(const duration& dur);

	string to_string(const duration& dur, bool microseconds = false, bool nanoseconds = false);
	time_point now();
}

#endif