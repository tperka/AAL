#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <unordered_set>
#include <functional>
#include <iomanip>
#include <unistd.h>
#include <set>
#include <map>

#include "composite2.hpp"
#include "composite3.hpp"
#include "data_source.hpp"
#include "square.hpp"
#include "algorithm.hpp"
#include "naive.hpp"

using namespace std;


double avg(vector<int64_t> values)
{
	int n = 0;
	double mean = 0.0;
	for (auto x : values)
	{
		double delta = x - mean;
		mean += delta / ++n;
	}
	return mean;
}


void testTime(string resultFilename, int problemSize, int step, int nOfRepetitions, int nOfTests, bool isHard, vector<square> (*functionToTest)(data_source))
{

	ofstream file;
	file.open(resultFilename, ios::out);
	file << "Input Size,Time\n";
	vector<int64_t> times;

	data_source test_data;
	int maxlen = isHard ? problemSize : problemSize / 4;

	for (int i = 0; i < nOfTests; ++i, problemSize += step)
	{
		times.clear();
		for (int j = 0; j < nOfRepetitions; ++j)
		{

			test_data.generate(problemSize, problemSize/4, isHard);    //argument 2 ->  patyki d�ugo�ci od 1 do arg2 (w��cznie)

			auto start = chrono::high_resolution_clock::now();
			//funkcja testowana
			functionToTest(test_data);

			auto end = chrono::high_resolution_clock::now();
			int64_t durationInMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
			times.push_back(durationInMs);
		}
		double averageTime = avg(times);
		file << problemSize << "," << averageTime << "\n";
	}

	file.close();
}





void display_help(char* nameOfProgram) {
	printf("Program should be executed as following: \n \
1. For manual data input and stdout output:\n \
%s -m 1 \n\n \
2. For input from file and/or output to file:\n \
%s -m 1 <in.txt >out.txt\n\n \
3. To generate and solve random problem:\n \
%s -m 2 [-n number of sticks] [-r max stick length] [-d difficulty (can only be 'hard' or 'normal')] \n\n \
4. To test alghorithm efficiency and record results to file in csv format:\n \
%s -m 3 [-n initial number of sticks] [-s step between tests] [-k number of tests] [-r number of repetitions] [-f filename]\n\n \
5. To display this help and quit:\n \
%s\n",
nameOfProgram, nameOfProgram, nameOfProgram, nameOfProgram, nameOfProgram);
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		display_help(argv[0]);
	}


	data_source dane;
	string difficulty, filename;
	int option = 0, mode = 0, nOfTests = 0, initialProblemSize = 0, step = 0, nOfRepetitions = 0;
    while((option = getopt(argc, argv, "m:n:k:s:r:d:f:")) != -1) {
        switch (option) {
            case 'm':
                mode = atoi(optarg);
                break;
            case 'n':
                initialProblemSize = atoi(optarg);
                break;
            case 'k':
                nOfTests = atoi(optarg);
                break;
            case 's':
                step = atoi(optarg);
                break;
            case 'r':
                nOfRepetitions = atoi(optarg);
                break;
			case 'd':
				difficulty = optarg;
				if(difficulty != "hard" && difficulty != "normal") {
					cerr << "difficulty (-d) can only be 'hard' or 'normal'" << endl;
				}
				break;
			case 'f':
				filename = optarg;
				if(filename.empty()) {
					filename = "test.csv";
				}
				break;
			default:
				display_help(argv[0]);
				break;
        }
    }

    if(mode == 1) {
		cout << "Insert number of sticks" << endl;
		cin >> initialProblemSize;
		if (initialProblemSize < 6)
		{
			cout << "You can't use less then 6 sticks";
			return 1;
		}
		int input;
		cout << "Insert sticks' lengths, separated by space" << endl;
		while(initialProblemSize > 0) {
			cin >> input;
			dane.potential_sides.push_back(input);
			--initialProblemSize;
		}

		dane.prepare();
    } else if(mode == 2){
		if(initialProblemSize < 6) {
			cerr << "You can't use less than 6 sticks" << endl;
			return 1;
		}
		if(nOfRepetitions < 1) {
			cerr << "Minimal max range can't be less than 1" << endl;
			return 1;
		}
		dane.generate(initialProblemSize, nOfRepetitions, difficulty == "hard");
    } else if(mode ==3) {
        testTime(filename, initialProblemSize, step, nOfRepetitions,nOfTests, difficulty == "hard", find_squares);
		return 0;
    } else {
        cerr << "Mode should be 1, 2 or 3" << endl;
		return 1;
    }

	vector<square> results;
    vector<square> naiveResults;
	results = find_squares(dane);
    
	int n;
	int x;
	n = results.size();
	x = 0;

    cout << "Our algorithm:" << endl;
	cout << "Found: " << n << " squares" << '\n';
	while (x < n)
	{
		cout << results[x] << '\n';
		x++;
	}
    
	naiveResults = naive(dane);
    n = naiveResults.size();
	x = 0;
    cout << "Naive algorithm:" << endl;
	cout << "Found: " << n << " squares" << '\n';
	while (x < n)
	{
		cout << naiveResults[x] << '\n';
		x++;
	}

	results.clear();
    naiveResults.clear();

	return 0;
}