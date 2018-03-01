/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#pragma once
template <typename TYPE>

class LinkedStack {
	class Node {
	public:
		TYPE Data;
		Node* pNext;
		Node(TYPE, Node* = NULL);
	};

public:
	LinkedStack();
	~LinkedStack();

public:
	void Push( TYPE & Element);
	bool Pop();
	TYPE& Peek();
	bool IsEmpty() const;
	size_t GetSize() const;

private:
	void Init();

private:
	Node* top;
	size_t cnt;
};


template <typename TYPE>
LinkedStack<TYPE>::Node::Node(TYPE Data, Node* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
}

template <typename TYPE>
LinkedStack<TYPE>::LinkedStack()
{
	Init();
}

template <typename TYPE>
LinkedStack<TYPE>::~LinkedStack()
{
	while (!IsEmpty()) {
		Pop();
	}
	IsEmpty();
}

template <typename TYPE>
void LinkedStack<TYPE>::Init()
{
	top = 0;
	cnt = 0;
}
template<typename TYPE>
size_t LinkedStack<TYPE>::GetSize() const
{
	return cnt;
}
template <typename TYPE>
void LinkedStack<TYPE>::Push(TYPE & Element)
{
	top = new Node(Element, top);
	cnt++;
}

template<typename TYPE>
bool LinkedStack<TYPE>::Pop()
{
	if (!IsEmpty()) {
		Node *topNode = top;
		top = top->pNext;
		TYPE data = topNode->Data;
		delete topNode;
		cnt--;
		return true;
	}
	return false;
}


template<typename TYPE>
TYPE& LinkedStack<TYPE>::Peek()
{
	return top->Data;
}

template<typename TYPE>
bool LinkedStack<TYPE>::IsEmpty() const
{
	return top == NULL;
}
