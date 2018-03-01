/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/
#pragma once
#include "stdafx.h"
#include "MyBST.h"
#include <iostream>

using namespace std;

//Insert function searches for the right position and the adds 
//TODO: Try simplifying

template <class T>
void MyBST<T>::insert(T element)
{
	treeNode* temp = new treeNode;
	treeNode* parent;
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
		treeNode* currentEl;
		currentEl = root;
		while (currentEl)
		{
			parent = currentEl;

			if (currentEl->data < temp->data)
			{
				currentEl = currentEl->right;
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
	numberOfElements++;
}

//Searh function returns a pointer to the found element
template <class T>
T* MyBST<T>::search(T element)
{
	if (isEmpty())
	{
		return NULL;
	}
	treeNode* currentEl;
	treeNode* parent;
	currentEl = root;
	parent = (treeNode*)NULL;
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


//Remove function with several cases 

template <class T>
void MyBST<T>::remove(T element)
{

	bool found = false;
	if (isEmpty())
	{
		return;
	}

	treeNode* currentEl;
	treeNode* parent;
	currentEl = root;
	parent = (treeNode*)NULL;
	while (currentEl != NULL)
	{
		if (currentEl->data == element)
		{
			found = true;
			//parent = root;
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
	if (!found)
	{
		return;
	}

	//Remove element with no children
	if (currentEl->left == NULL && currentEl->right == NULL)
	{
		if (parent == NULL)
		{
			delete currentEl;
		}
		else
		{
			if (parent->left == currentEl)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
			delete currentEl;
		}
	return;
	}

	// Remove element with single child

	//If the condition is true that means that the node has only one child

	if ((currentEl->left == NULL && currentEl->right != NULL) || 
		(currentEl->left != NULL && currentEl->right == NULL))
	{
		//Check if is left or right

		if (currentEl->left == NULL && currentEl->right != NULL) // delete the right child
		{
			if (parent->left == currentEl)
			{
				parent->left = currentEl->right;
				delete currentEl;
			}
			else
			{
				parent->right = currentEl->right;
				delete currentEl;
			}
		}
		else // delete the right child
		{
			if (parent->left == currentEl)
			{
				parent->left = currentEl->left;
				delete currentEl;
			}
			else
			{
				parent->right = currentEl->left;
				delete currentEl;
			}
		}
		return;
	}


	//Remove element with two children

	if (currentEl->left != NULL && currentEl->right != NULL)
	{
		treeNode* child;

		child = currentEl->right; // Find the right child and check if it has children
		if ((child->left == NULL) && (child->right == NULL))
		{
			currentEl = child;
			delete child;
			currentEl->right = NULL;
		}
		else // Right child has children
		{
			if ((currentEl->right)->left != NULL) //check if there are left children of the child o.O
			{
				treeNode* leftChild;
				treeNode* leftChildParrent;

				leftChildParrent = currentEl->right;
				leftChild = (currentEl->right)->left;

				// Going to the leftmost element of the tree
				while (leftChild->left != NULL)
				{
					leftChildParrent = leftChild;
					leftChild = leftChild->left;
				}
				currentEl->data = leftChild->data;
				delete leftChild;
				leftChildParrent->left = NULL;
			}
			else //Just switch
			{
				treeNode* temp;
				temp = currentEl->right;
				currentEl->data = temp->data;
				currentEl->right = temp->right;
				delete temp;
			}

		}
		numberOfElements--;
		return;
	}

}

template <class T>
void MyBST<T>::deleteNode(treeNode *N)
{
	if (N)
	{
		deleteNode(N->left);
		deleteNode(N->right);
		delete N;
	}
}

template <class T>
MyBST<T>::~MyBST<T>()
{
	deleteNode(root);
}


// Day–stout–warren algorithm for balancing the tree
//Some magic which I coppied from internet

template<class T>
void MyBST<T>::dsw()
{
	treeNode* temp = new treeNode;
	temp->right = root;
	treeToVine(temp);
	vineToTree(temp, numberOfElements);
	this->root = temp->right;
}
template<class T>
void MyBST<T>::treeToVine(treeNode* root)
{
	treeNode* tail = root;
	treeNode* rest = tail->right;

	while (rest != NULL) {
		if (rest->left == NULL) {
			tail = rest;
			rest = rest->right;
		}
		else {
			treeNode* temp = rest->left;
			rest->left = temp->right;
			temp->right = rest;
			rest = temp;
			tail->right = temp;
		}
	}
}

template <class T>
void MyBST<T>::compress(treeNode* root, int count)
{
	treeNode* scanner = root;
	for (int i = 0; i < count; i++)
	{
		treeNode* child = scanner->right;
		scanner->right = child->right;
		scanner = scanner->right;
		child->right = scanner->left;
		scanner->left = child;
	}
}
template <class T>
void MyBST<T>::vineToTree(treeNode* root, int size)
{
	int numberOfLeaves = (int)(size + 1 - pow(2, floor(log(size + 1) / log(2))));
	compress(root, numberOfLeaves);
	size = size - numberOfLeaves;
	while (size > 1) {
		compress(root, (int)floor(size / 2));
		size = (int)floor(size / 2);
	}
}