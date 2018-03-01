/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/


// This is a set implemented with binary search tree

#pragma once
#include "stdafx.h"
#include "MySet.h"
#include <iostream>
#include <fstream>

using namespace std;

//Standartd insert function but it does not add equal elements
void MySet::insert(long element)
{
	Node* temp = new Node;
	Node* parent;
	temp->data = element;
	temp->left = NULL;
	temp->right = NULL;
	parent = NULL;


	if (isEmpty())
	{
		root = temp;
	}
	else
	{
		Node* currentEl;
		currentEl = root;
		while (currentEl)
		{
			parent = currentEl;

			if (currentEl->data < temp->data)
			{
				currentEl = currentEl->right;
			}
			else if (currentEl->data == temp->data)
			{
				return;
			}
			else
			{
				currentEl = currentEl->left;
			}
		}

		if (temp->data < parent->data)
		{
			parent->left = temp;
		}
		else
		{
			parent->right = temp;
		}

	}
}

//Searh function returns a pointer to the found element

long* MySet::search(long element)
{
	if (isEmpty())
	{
		return NULL;
	}
	Node* currentEl;
	Node* parent;
	currentEl = root;
	parent = (Node*)NULL;
	while (currentEl != NULL)
	{
		if (currentEl->data == element)
		{
			return &currentEl->data;
			break;
		}
		else
		{
			parent = currentEl;
			if (currentEl->data < element)
			{
				currentEl = currentEl->right;
			}
			else
			{
				currentEl = currentEl->left;
			}
		}
	}
	return NULL;
}

// Write the elements of the set into a binary file
void MySet::writeInorder()
{
	ofstream out("result.bin", ios::binary);
	inorder(root, out);
	out.close();
}

//Traverse the set inorder and write each element in the binary file 
void MySet::inorder(Node* p, ofstream &out)
{

	if (p != NULL)
	{
		if (p->left) inorder(p->left, out);
		out.write((char*)&p->data, sizeof(long));
		if (p->right) inorder(p->right, out);
	}
	else
	{
		return;
	}
}

// Assingnment operator
MySet& MySet::operator=(const MySet& other)
{
	
	if (this != &other)
	{
		if (root != NULL)
		{
			deleteNode(root);
		}		
		if (other.root == NULL)
		{
			root = NULL;
		}
		else
		{
			copySet(root, other.root);
		}
	}

	return *this;
}

//Copy constructor
MySet::MySet(MySet& original)
{
	copySet(original.root, root);
}

//Function to copy the set into another set
void MySet::copySet(Node* &copiedNode,Node* otherNode)
{
	if (otherNode == NULL)
	{
		copiedNode = NULL;
	}
	else
	{
		copiedNode = new Node;
		copiedNode->data = otherNode->data;
		copySet(copiedNode->left, otherNode->left);
		copySet(copiedNode->right, otherNode->right);
	}
}

// Function to delete the set recursively
void MySet::deleteNode(Node *N)
{
	if (N)
	{
		deleteNode(N->left);
		deleteNode(N->right);
		delete N;
	}
}

// Destructor
MySet::~MySet()
{
	deleteNode(root);
}