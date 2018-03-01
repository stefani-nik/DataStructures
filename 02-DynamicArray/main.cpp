/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Query.h"
#include "MyArr.h"

using namespace std;

int main(int argc, char * argv[])
{
	//Creating a vector to store all queries
	MyArr<Query> queriesQueue;

	//Reading the input file
	ifstream inputFile(argv[1]);

	string str;

	// Reading each line of the file 
	while (getline(inputFile, str)) {

		string currentLine = str;

		if (!isdigit(currentLine[0]))
		{
			istringstream iss(currentLine);

			//Reading each word of every line
			while (iss) {
				string word;
				iss >> word;
				try
				{
					Query currentQuery;
					int currFloor = stoi(word);

					iss >> word;
					int currTime = stoi(word);
					currentQuery.floor = currFloor;
					currentQuery.time = currTime;
					queriesQueue.Add(currentQuery);
				}
				catch (...)
				{
					continue;
				}
			}
		}
	}

	int position = 1; // Always starts from the first floor 
	int direction = 1;  // 1 for UP and 0 for DOWN

	int totalTime = queriesQueue[0].time;

	while (queriesQueue.GetSize() > 0)
	{
		// Initializing a dynamic array for all valid queries
		MyArr<Query> validQueries;

		//Take the first query and checking all of the rest if they are valid
		Query query = queriesQueue[0];
		validQueries.Add(query);

		int targetFloor = query.floor;
		int size = queriesQueue.GetSize();

		direction = targetFloor < position ? 0 : 1;

		for (int i = 1; i < size; i++)
		{
			//Take the next query 
			Query next = queriesQueue[i];

			// Check if the query is valid
			if ((direction == 1
				&& (next.floor <= targetFloor && next.floor >= position))
				|| (direction == 0
					&& (next.floor >= targetFloor && next.floor <= position)))

			{
				int currentTime = (abs(next.floor - position) * 5) + totalTime;

				//Check if the query time is valid
				if (currentTime >= next.time)
				{
					validQueries.Add(next);
					queriesQueue.Delete(i);
					size--;
					i--;
				}
			}
		}

		//Delete the first valid query
		queriesQueue.Delete(0);

		// If the current query time is bigger than the total time - change the values 
		if (totalTime < validQueries[0].time)
		{
			totalTime = validQueries[0].time;
		}
	
		//Sorting the valid queries 
		validQueries.SortQueries(direction);

		int currentFloor = validQueries[0].floor;

		//Check the position before printing
		string directionStr = direction == 0 ? "down" : "up";

		// Add the first floor of the valid queries to the total time
		totalTime += abs(currentFloor - position) * 5;

		cout << totalTime << " " << currentFloor << " " + directionStr << endl;

		//Find the difference between the current floor and the next floor
		int diff = abs(currentFloor - position) * 5;

		//Iterate through the valid queries 
		for (int i = 0; i < validQueries.GetSize(); i++)
		{
			//Check for the qniue valid queries 
			if (currentFloor != validQueries[i].floor)
			{
				// If the current query time is bigger than the total time - change the values 
				if (totalTime < validQueries[i].time)
				{
					totalTime = validQueries[i].time;
				}

				// Add the current valid query's time to the total time 
				totalTime += abs(validQueries[i].floor - position) * 5 - diff;
				// Change the current floor to the current query's time
				currentFloor = validQueries[i].floor;

				cout << totalTime << " " << currentFloor << " " + directionStr << endl;
			}
		}
		//Change the elevator's position
		position = query.floor;
	}
	return 0;
}

