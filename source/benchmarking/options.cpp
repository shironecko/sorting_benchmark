#include <iostream>
#include <cstdlib>
#include <boost/program_options.hpp>
#include "options.h"

using namespace std;
namespace opt = boost::program_options;

options initialize_options(int argc, char* argv[])
{
	options result;

	opt::options_description opt_desc("Allowed options");
	opt_desc.add_options()
		("algorithm,a", opt::value<std::string>(&result.algorithm)->required(), "algorithm used for benchmarking")
		("iterations,i", opt::value<unsigned int>(&result.iterations)->required(), "number of iterations taken")
		("array-size,s", opt::value<unsigned int>(&result.array_size)->required(), "size of the test array")
		("min", opt::value<int>(&result.arr_min_num)->default_value(0), "minimum value of digits in array")
		("max", opt::value<int>(&result.arr_max_num)->default_value(100), "maximum value of digits in array")
		("test,t", opt::value<bool>(&result.test)->implicit_value(true)->default_value(false), "enables testing of sorted arrays for order and integrity")
		("verbosity,v", opt::value<int>(&result.verbosity_level)->default_value(2), "amount of info printed")
		("help,h", "prints the list of available commands");

	opt::variables_map var_map;

	try
	{
		opt::store(opt::parse_command_line(argc, argv, opt_desc), var_map);
		opt::notify(var_map);
	}
	catch (opt::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
		std::cerr << opt_desc << std::endl;
		exit(1);
	}

	if (var_map.count("help") > 0)
	{
		cout << opt_desc << endl;
		exit(0);
	}

	return result;
}