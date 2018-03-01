/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#pragma once
#include <iostream>
using namespace std;

class MySet
{
private:
	struct Node
	{
		Node() {};
		Node* left;
		Node* right;
		long data;
	};
	Node* root;

public:
	MySet()
	{
		root = NULL;
	}
	~MySet();
	MySet(MySet& origList);
	bool isEmpty() const { return root == NULL; }
	void insert(long element);
	long* search(long d);
	void inorder(Node*, ofstream &stream);
	void writeInorder();
	MySet& operator=(const MySet& other);
	void copySet(Node* &copiedTreeRoot, Node* otherTreeRoot);
	void deleteNode(Node *N);
};

