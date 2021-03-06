#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include "time_helper.h"

using namespace std;

namespace time_helper
{
	int get_hours(const duration& dur)
	{
		return chrono::duration_cast<chrono::hours>(dur).count();
	}

	int get_minutes(const duration& dur)
	{
		return chrono::duration_cast<chrono::minutes>(dur).count() % 60;
	}

	long long get_seconds(const duration& dur)
	{
		return chrono::duration_cast<chrono::seconds>(dur).count() % 60;
	}

	long long get_milliseconds(const duration& dur)
	{
		return chrono::duration_cast<chrono::milliseconds>(dur).count() % 1000;
	}

	long long get_microseconds(const duration& dur)
	{
		return chrono::duration_cast<chrono::microseconds>(dur).count() % 1000;
	}

	long long get_nanoseconds(const duration& dur)
	{
		return chrono::duration_cast<chrono::nanoseconds>(dur).count() % 1000;
	}

	long long get_nanoseconds_total(const duration& dur)
	{
		return chrono::duration_cast<chrono::nanoseconds>(dur).count();
	}

	string to_string(const duration& dur, bool microseconds, bool nanoseconds)
	{
		// TODO: change to thread_local when migrate to Clang
		static stringstream ss;

		int hours = get_hours(dur);
		int minutes = get_minutes(dur);
		long long seconds = get_seconds(dur);
		long long milliseconds = get_milliseconds(dur);
		long long microsec = get_microseconds(dur);
		long long nanosec = get_nanoseconds(dur);

		ss.str("");
		ss.clear();
		
		if (hours != 0)
			ss << hours << "h ";
		if (minutes != 0 || hours != 0)
			ss << setfill('0') << setw(2) << minutes << "m ";
		if (seconds != 0 || minutes != 0 || hours != 0)
			ss << setfill('0') << setw(2) << seconds << "s ";
		if (!microseconds || milliseconds != 0 || minutes != 0 || hours != 0)
			ss << setfill('0') << setw(3) << milliseconds << "ms ";
		if (microseconds || nanoseconds)
			ss << setfill('0') << setw(3) << microsec << "mcs ";
		if (nanoseconds)
			ss << setfill('0') << setw(3) << nanosec << "ns ";

		return ss.str();
	}

	time_point now()
	{
		return chrono::high_resolution_clock::now();
	}
}