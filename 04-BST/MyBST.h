/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#pragma once
#include <iostream>
using namespace std;

template<class T>
class MyBST
{
private:
	struct treeNode
	{
		treeNode() {};
		treeNode* left;
		treeNode* right;
		T data;
	};
	treeNode* root;
	int numberOfElements;
	void treeToVine(treeNode* root);
	void compress(treeNode* root, int count);
	void vineToTree(treeNode* root, int size);


public:
	MyBST()
	{
		root = NULL;
	}
	~MyBST();
	bool isEmpty() const { return root == NULL; }
	void insert(T);
	void remove(T);
	void deleteNode(treeNode *N);
	T* search(T d);
	void dsw();
};
