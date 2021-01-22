#include "data_source.hpp"
#include <ctime>
#include <algorithm>



void data_source::prepare()
{
	this->left_marker_1 = 0;
	this->left_marker_2 = 1;
	this->left_marker_3 = 2;

	this->right_count = 0;
	this->right_marker = (this->potential_sides.size() - 1);

	sort(this->potential_sides.begin(), this->potential_sides.end());

	return;
}


void data_source::generate(int size, int range, bool hard)
{

	this->potential_sides.clear();
	srand(time(NULL));
	int helper;
	if (hard)
	{
		while (size > 0)
		{
			helper = (rand() % range) + 1;
			this->potential_sides.push_back(helper);
			this->potential_sides.push_back(helper);
			this->potential_sides.push_back(helper);
			this->potential_sides.push_back(helper);
			size-=4;
		}
	}
	else
	{
		while (size > 0)
		{
			helper = (rand() % range) + 1;
			this->potential_sides.push_back(helper);
			size--;
		}
	}


	this->prepare();


	return;
}