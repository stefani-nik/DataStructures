/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#include "stdafx.h"
#include "MySet.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main()
{
	//Creating the first set which will be rewritten with the reading of 
	//every file except for the first one

	MySet resultSet;
	int n;
	cin >> n;
	int i = 0;
		
		while(i < n)
		{
			//Creating the helper set which will hold the section 
			//of numbers of the current and the previous file

			MySet helperSet;

			string inputLine;
			cin >> inputLine;
		
			ifstream reader(inputLine);

			//Reading each number of the file and if it is the first iteration of the while loop
			// we are inserting all numbers in the result set. 
			// If it is not the first iteration and the number 
			// exists in the result set we are inserting it in the helper.  

			while (!reader.eof())
			{
				long currentNum;
				reader.read((char*)&currentNum, sizeof(currentNum));
				if (i == 0)
				{
					resultSet.insert(currentNum);
				}
				else if (resultSet.search(currentNum))
				{
					helperSet.insert(currentNum);
				}
			}
			reader.close();

			// Rewriting the result set with the helper
			if (i != 0)
			{
				resultSet = helperSet;
			}
			i++;
		}

		//Writing in the file
		resultSet.writeInorder();

    return 0;
}

