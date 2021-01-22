#include "square.hpp"

#include <algorithm>
using namespace std;
square::~square()
{

}


square::square()
{
	this->is_composite_3 = false;
	this->standalone_sides = 0;
	this->composite_side_3 = composite3();
	this->first_composite_side_2 = composite2();
	this->second_composite_side_2 = composite2();
}


bool operator==(const square& square1,const square& other_square) {
    int sides[6], osides[6];
    if(square1.is_composite_3 == other_square.is_composite_3 && square1.is_composite_3) {
        sides[4] = sides[3] = sides[5] = square1.standalone_sides;
        osides[4] = osides[3] = osides[5] = other_square.standalone_sides;
        
        sides[0] = square1.composite_side_3.first;
        sides[1] = square1.composite_side_3.second;
        sides[2] = square1.composite_side_3.third;

        osides[0] = other_square.composite_side_3.first;
        osides[1] = other_square.composite_side_3.second;
        osides[2] = other_square.composite_side_3.third;
        sort(sides, sides+6);
        sort(osides, osides+6);
        for(int i = 0; i < 6; ++i) {
            if(sides[i] != osides[i])
                return false;
        }
        return true;
    }
    if(square1.is_composite_3 == other_square.is_composite_3 && !square1.is_composite_3) {
        sides[4] = sides[5] = square1.standalone_sides;
        
        osides[4] = osides[5] = other_square.standalone_sides;
        
        sides[0] = square1.first_composite_side_2.first;
        sides[1] = square1.first_composite_side_2.second;
        sides[2] = square1.second_composite_side_2.first;
        sides[3] = square1.second_composite_side_2.second;
        
        osides[0] = other_square.first_composite_side_2.first;
        osides[1] = other_square.first_composite_side_2.second;
        osides[2] = other_square.second_composite_side_2.first;
        osides[3] = other_square.second_composite_side_2.second;

        sort(sides, sides+6);
        sort(osides, osides+6);
        for(int i = 0; i < 6; ++i) {
            if(sides[i] != osides[i])
                return false;
        }
        return true;
    }

    return false;

}

int* square::toArray() const{
    int* result = new int[6];
    if(is_composite_3) {
        result[0] = result[1] = result[2] = standalone_sides;
        result[3] = composite_side_3.first;
        result[4] = composite_side_3.second;
        result[5] = composite_side_3.third;

    } else {
        result[0] = first_composite_side_2.first;
        result[1] = first_composite_side_2.second;
        result[2] = second_composite_side_2.first;
        result[3] = second_composite_side_2.second;
        result[4] = result[5] = standalone_sides;
    }
    sort(result, result+6);
    return result;
}

bool operator<(const square& square1, const square& square2) {
    int* sq1 = square1.toArray();
    int* sq2 = square2.toArray();
    for(int i = 5; i >=0; --i) {
        if(sq1[i] < sq2[i]) {
            delete[] sq1;
            delete[] sq2;
            return true;
        } else if(sq1[i] > sq2[i]) {
            delete[] sq1;
            delete[] sq2;
            return false;
        }
    }
    delete[] sq1;
    delete[] sq2;
    return false;
}

square::square(int sides[6])
{
    sort(sides, sides+6);
    int standalone = sides[5];
    int counter = 1;
    for(int i = 0; i < 5; ++i) {
        if(sides[i] == standalone) {
            counter++;
        }
    }
    if(counter == 2) {
        this->is_composite_3 = false;
        this->first_composite_side_2 = composite2();
        this->second_composite_side_2 = composite2();
        this->first_composite_side_2.first = sides[0];
        this->first_composite_side_2.second = sides[3];
        this->second_composite_side_2.first = sides[1];
        this->second_composite_side_2.second = sides[2];
        this->standalone_sides = standalone;
    }
    if(counter == 3) {
        this->composite_side_3 = composite3();
        this->is_composite_3 = true;
        this->composite_side_3.first = sides[0];
        this->composite_side_3.second = sides[1];
        this->composite_side_3.third = sides[2];
        this->standalone_sides = standalone;
    }

}

square::square(const square& other_square)
{
	this->is_composite_3 = other_square.is_composite_3;
	this->standalone_sides = other_square.standalone_sides;
	this->composite_side_3 = other_square.composite_side_3;
	this->first_composite_side_2 = other_square.first_composite_side_2;
	this->second_composite_side_2 = other_square.second_composite_side_2;
}

void square::operator=(const square& other_square)
{
	this->is_composite_3 = other_square.is_composite_3;
	this->standalone_sides = other_square.standalone_sides;
	this->composite_side_3 = other_square.composite_side_3;
	this->first_composite_side_2 = other_square.first_composite_side_2;
	this->second_composite_side_2 = other_square.second_composite_side_2;
}

std::ostream& operator <<(std::ostream& os, square& kwadrat)
{
	if (kwadrat.is_composite_3)
	{
		os << kwadrat.standalone_sides << " " << kwadrat.standalone_sides << " " << kwadrat.standalone_sides << " " << kwadrat.composite_side_3.first << " " << kwadrat.composite_side_3.second << " " << kwadrat.composite_side_3.third;
	}
	else
	{
		os << kwadrat.standalone_sides << " " << kwadrat.standalone_sides << " " << kwadrat.first_composite_side_2.first << " " << kwadrat.first_composite_side_2.second << " " << kwadrat.second_composite_side_2.first << " " << kwadrat.second_composite_side_2.second;
	}
	return os;
}
