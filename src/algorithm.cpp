#include "algorithm.hpp"

#include <unordered_set>

using namespace std;

vector<square> find_squares(data_source dane)
{

	//przygotowania
	vector<square> results;
	unordered_set<composite2, HashComposite2> candidates_2;
	unordered_set<composite3, HashComposite3> candidates_3;
	unordered_set<composite2, HashComposite2> candidates_2_duplicates;
	composite2 insert_helper_2;
	composite3 insert_helper_3;
	square insert_helper_square;

	int value_helper;
	int right_stick_value_helper;


	//g��wna p�tla
	while (dane.right_marker > 0)
	{
		if (static_cast<double>(dane.potential_sides[0]) > static_cast<double>(0.5 * static_cast<double>(dane.potential_sides[dane.right_marker])))			//je�eli ten warunek jest spe�niony, nie da si� ju� utworzy� wi�cej kwadrat�w
			return results;

		//zliczamy ilo�� patyk�w takiej samej d�ugo�ci plus zapisujemy t� d�ugo��
		right_stick_value_helper = dane.potential_sides[dane.right_marker];
		dane.right_count = 1;

		while (dane.right_marker > 0 && right_stick_value_helper == dane.potential_sides[dane.right_marker - 1])
		{
			dane.right_count++;
			dane.right_marker--;
		}
		//co najmniej 3 patyki tej samej d�ugo�ci - szukamy kwadrat�w z bokiem 3-kompozytowym
		if (dane.right_count >= 3)
		{
			candidates_3.clear();

			if (static_cast<double>(dane.potential_sides[0]) <= static_cast<double>(0.3334 * static_cast<double>(right_stick_value_helper)))		//je�eli ten warunek nie jest spe�niony, nie da si� ju� utworzy� wi�cej kwadrat�w z bokiem 3-kompozytowym	
			{
				dane.left_marker_1 = 0;
				dane.left_marker_2 = 1;
				dane.left_marker_3 = 2;

				while (dane.left_marker_1 <= (dane.right_marker - 3) && static_cast<double>(dane.potential_sides[dane.left_marker_1]) <= static_cast<double>(0.3334 * static_cast<double>(right_stick_value_helper)))	//zaczyna od patyka najbardziej z lewej
				{
					dane.left_marker_2 = dane.left_marker_1 + 1;
					while (dane.left_marker_2 <= (dane.right_marker - 2))		//zaczyna od drugiego z lewej patyka
					{
						dane.left_marker_3 = dane.left_marker_2 + 1;
						while (dane.left_marker_3 <= (dane.right_marker - 1))		//zaczyna od trzeciego z lewej patyka
						{
							value_helper = dane.potential_sides[dane.left_marker_1] + dane.potential_sides[dane.left_marker_2] + dane.potential_sides[dane.left_marker_3];
							if (value_helper == right_stick_value_helper)
							{
								//sk�adanie kwadrat�w 3-kompozytowych

								insert_helper_3.first = dane.potential_sides[dane.left_marker_1];
								insert_helper_3.second = dane.potential_sides[dane.left_marker_2];
								insert_helper_3.third = dane.potential_sides[dane.left_marker_3];

								candidates_3.insert(insert_helper_3);
								
								break;		// X = A + B + C    nie ma sensu szuka� C2 >= C, i tak nie b�dzie pasowa�
							}

							if (value_helper > right_stick_value_helper)
								break;

							dane.left_marker_3++;
						}
						dane.left_marker_2++;
					}
					dane.left_marker_1++;
				}

				//add to result set
				auto start3 = candidates_3.begin();
				auto finish3 = candidates_3.end();
				while (start3 != finish3)
				{
					insert_helper_square.is_composite_3 = true;
					insert_helper_square.standalone_sides = right_stick_value_helper;
					insert_helper_square.composite_side_3 = *start3;

					results.push_back(insert_helper_square);

					start3++;
				}

			}
		}
		
		//co najmniej 2 patyki tej samej d�ugo�ci - szukamy kwadrat�w z bokami 2-kompozytowymi
		if (dane.right_count >= 2)
		{
			candidates_2.clear();
			candidates_2_duplicates.clear();
			dane.left_marker_1 = 0;
			dane.left_marker_2 = 1;

			while (dane.left_marker_1 <= (dane.right_marker - 2) && static_cast<double>(dane.potential_sides[dane.left_marker_1]) <= static_cast<double>(0.5 * static_cast<double>(right_stick_value_helper)))			//zaczyna od patyka najbardziej z lewej
			{
				dane.left_marker_2 = dane.left_marker_1 + 1;
				while (dane.left_marker_2 <= (dane.right_marker - 1))			//zaczyna od drugiego z lewej patyka
				{
					value_helper = dane.potential_sides[dane.left_marker_1] + dane.potential_sides[dane.left_marker_2];
					if (value_helper == right_stick_value_helper)
					{
						//sk�adanie kwadrat�w 2-kompozytowych

						insert_helper_2.first = dane.potential_sides[dane.left_marker_1];
						insert_helper_2.second = dane.potential_sides[dane.left_marker_2];
	
						candidates_2.insert(insert_helper_2);

						if (dane.potential_sides[dane.left_marker_1] == dane.potential_sides[dane.left_marker_2] && dane.potential_sides[dane.left_marker_2] == dane.potential_sides[dane.left_marker_2 + 1] && dane.potential_sides[dane.left_marker_2] == dane.potential_sides[dane.left_marker_2 + 2])
						{
							candidates_2_duplicates.insert(insert_helper_2);
						}
						else if (dane.potential_sides[dane.left_marker_1] != dane.potential_sides[dane.left_marker_2] && dane.potential_sides[dane.left_marker_1] == dane.potential_sides[dane.left_marker_1 + 1] && dane.potential_sides[dane.left_marker_2] == dane.potential_sides[dane.left_marker_2 + 1])
						{
							candidates_2_duplicates.insert(insert_helper_2);
						}

						break;		// X = A + B   nie ma sensu szuka� B2 >= B, i tak nie b�dzie pasowa�
					}
					if (value_helper > right_stick_value_helper)
						break;

					dane.left_marker_2++;
				}
				dane.left_marker_1++;
			}

			//add to result set
			auto start2 = candidates_2.begin();
			auto it2 = candidates_2.begin();
			auto finish2 = candidates_2.end();
			auto duplicate_start = candidates_2_duplicates.begin();
			auto duplicate_end = candidates_2_duplicates.end();

			while (duplicate_start != duplicate_end)
			{
				insert_helper_square.is_composite_3 = false;
				insert_helper_square.standalone_sides = right_stick_value_helper;
				insert_helper_square.first_composite_side_2 = *duplicate_start;
				insert_helper_square.second_composite_side_2 = *duplicate_start;

				results.push_back(insert_helper_square);

				duplicate_start++;
			}


			while (true)
			{
				if (start2 == finish2)
					break;

				it2 = start2;
				it2++;

				while (true)
				{
					if (it2 == finish2)
						break;

					//dodawanie do wynik�w
					insert_helper_square.is_composite_3 = false;
					insert_helper_square.standalone_sides = right_stick_value_helper;
					insert_helper_square.first_composite_side_2 = (*start2);
					insert_helper_square.second_composite_side_2 = (*it2);

					results.push_back(insert_helper_square);

					it2++;
				}
				start2++;
			}


		}
;
		dane.left_marker_1 = 0;
		dane.left_marker_2 = 1;
		dane.left_marker_3 = 2;

		dane.right_count = 0;
		dane.right_marker--;

	}

	
	return results;

}