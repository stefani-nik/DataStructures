/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/


#pragma once
#include <iostream>
#include <list>

using namespace std;

class Leaf
{
public:
	Leaf() {}; 
	Leaf(int key)
	{
		Key = key;
	};
	int Key;
	list<string> DataList;


	//Override the  compariosn operators

	const bool operator < (Leaf l)
	{
		return this->Key > l.Key;
	}
	const bool operator == (Leaf l)
	{
		return this->Key == l.Key;
	}
};