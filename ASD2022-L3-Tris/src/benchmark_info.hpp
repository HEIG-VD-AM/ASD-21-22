#ifndef BENCHMARK_INFO_HPP
#define BENCHMARK_INFO_HPP

#include <string>
#include <vector>

#include "generator.hpp"

struct BenchmarkInfo {
	std::string function_name;
	InputType input_type;
	size_t min_sample_size;
	size_t max_sample_size;
	std::vector<std::size_t> samples;
};

#endif //BENCHMARK_INFO_HPP
