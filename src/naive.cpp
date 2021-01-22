#include "naive.hpp"

#include <algorithm>

using namespace std;

bool isSquare(int potentialSquare[6]) {
    sort(potentialSquare, potentialSquare + 6);
    int standalone = potentialSquare[5];
    int counter = 1;
    for(int i = 0; i < 5; ++i) {
        if(potentialSquare[i] == standalone) {
            counter++;
        }
    }
    if(counter == 2) {
        if((potentialSquare[0]+potentialSquare[3]) == (potentialSquare[1] + potentialSquare[2]) && (potentialSquare[0]+potentialSquare[3]) == standalone) {
            return true;
        }
    }
    if(counter == 3) {
        if((potentialSquare[0] + potentialSquare[1] + potentialSquare[2]) == standalone) {
            return true;
        }
    }
    return false;
}

vector<square> naive(data_source data) {

    vector<square> results;
    int nOfSticks = data.potential_sides.size();
    for(int i = 0; i < nOfSticks; ++i) {
        for(int j = i + 1; j < nOfSticks; ++j) {
            for(int k = j + 1; k < nOfSticks; ++k) {
                for(int l = k+1; l < nOfSticks; ++l) {
                    for(int m = l+1; m < nOfSticks; ++m) {
                        for(int n = m+1; n < nOfSticks; ++n) {
                            int potentialSquare[6];
                            potentialSquare[0] = data.potential_sides.at(i);
                            potentialSquare[1] = data.potential_sides.at(j);
                            potentialSquare[2] = data.potential_sides.at(k);
                            potentialSquare[3] = data.potential_sides.at(l);
                            potentialSquare[4] = data.potential_sides.at(m);
                            potentialSquare[5] = data.potential_sides.at(n);
                            if(isSquare(potentialSquare)) {
                                square temp(potentialSquare);
                                results.push_back(temp);
                            }
                        }
                    }
                }

            }
        }
    }