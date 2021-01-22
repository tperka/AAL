#ifndef DATA_SOURCE_HPP
#define DATA_SOURCE_HPP

#include <vector>

struct data_source
{
	std::vector<int> potential_sides;
	int left_marker_1;
	int left_marker_2;
	int left_marker_3;
	int right_marker;
	int right_count;
	void generate(int size, int range, bool hard);
	void prepare();
};


#endif