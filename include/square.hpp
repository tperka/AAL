#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "composite2.hpp"
#include "composite3.hpp"
#include <iostream>

struct square
{
	bool is_composite_3;
	int standalone_sides;
	composite3 composite_side_3;
	composite2 first_composite_side_2;
	composite2 second_composite_side_2;
	void operator=(const square& other_square);
	square();
    square(int sides[6]);
	square(const square& other_square);				// copy constructor
	~square();
    bool operator==(square other_square);
};

struct HashSquare
{
	size_t operator()(square const& hash_source) const noexcept
	{
		size_t seed;
		seed = 0;
		size_t hash_val;
        if(hash_source.is_composite_3) {
            hash_val = std::hash<int>{}(hash_source.standalone_sides);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            hash_val = std::hash<int>{}(hash_source.composite_side_3.first);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            hash_val = std::hash<int>{}(hash_source.composite_side_3.second);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            hash_val = std::hash<int>{}(hash_source.composite_side_3.third);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        } else {
            hash_val = std::hash<int>{}(hash_source.standalone_sides);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            
            hash_val = std::hash<int>{}(hash_source.first_composite_side_2.first);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            hash_val = std::hash<int>{}(hash_source.first_composite_side_2.second);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            hash_val = std::hash<int>{}(hash_source.second_composite_side_2.first);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            hash_val = std::hash<int>{}(hash_source.second_composite_side_2.second);
            seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
		return seed;
	}
};

std::ostream& operator <<(std::ostream& os, square& kwadrat);



#endif