/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#include "stdafx.h"

using namespace std;

class Operator {
	string representation;
	string actual;
public:
	void setRep(string str)
	{
		representation = str;
	}
	string getRep()
	{
		return representation;
	}
	void setActual(string str) {
		actual = str;
	}
	string getActual()
	{
		return actual;
	}
};

