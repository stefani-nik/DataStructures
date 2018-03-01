/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/


#include "stdafx.h"
#include "MyBST.h"
#include "MyBST.cpp"
#include "Leaf.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


MyBST<Leaf> tree;

bool searchElement(int key, string data)
{
	Leaf helper = Leaf(key);

	Leaf* element = tree.search(helper);

	if (element != NULL)
	{
		for each (string value in element->DataList)
		{
			if ((string)value == data)
			{
				return true;
			}
		}

	}
	return false;
}

void insretElement( int key, string value)
{
	Leaf helper = Leaf(key);
	Leaf* element = tree.search(helper);

	if (element != NULL)
	{
		//cout << element << endl;
		element->DataList.push_back(value);
	}
	else
	{
		list<string> leafList = { value };
		Leaf currentLeaf(key);
		currentLeaf.DataList = leafList;
		tree.insert(currentLeaf);
	}
}
void removeSingleElement(int key, string value)
{
	Leaf helper = Leaf(key);
	Leaf* element = tree.search(helper);

	if (searchElement(key,value))
	{
		element->DataList.remove(value);

		if (element->DataList.size() == 0)
		{
			tree.remove(*element);
		}
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
}
void removeAllElements(int key)
{
	Leaf helper = Leaf(key);
	Leaf* element = tree.search(helper);

	if (element != NULL)
	{
		cout << element->DataList.size() << endl;
		tree.remove(*element);
	}
}

int main(int argc, char* argv[])
{
		std::ifstream reader(argv[1]);

		while (!reader.eof())
		{
			int key;
			reader.read((char*)&key, sizeof(key));

			int size = 0;
			reader.read((char*)&size, sizeof(size));

			char *buffer = new char[size + 1];
			reader.read(buffer, size);

			buffer[size] = '\0';

			if (buffer[0] != '\0')
			{
				insretElement( key, buffer);
			}

		}
		reader.close();


		// Balance the tree
		tree.dsw();


		string inputLine;
		while (getline(cin, inputLine))
		{

			istringstream iss(inputLine);
			string command;
			iss >> command;

			if (command == "removeall")
			{
				int key;
				iss >> key;
				removeAllElements(key);
			}
			else
			{
				int key;
				iss >> key;
				string data;
				iss >> data;


				if (command == "search")
				{
					if (searchElement(key, data))
					{
						cout << "true" << endl;
					}
					else
					{
						cout << "false" << endl;
					}
				}
				else if (command == "remove")
				{
					removeSingleElement( key, data);
				}
				else if (command == "add")
				{
					insretElement( key, data);
				}
				else
				{
					cout << "Invalid command!" << endl;
				}
			}

		}

	return 0;

}

