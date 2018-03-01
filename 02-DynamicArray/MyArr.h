/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#include <iostream>

template<class TYPE>

class MyArr
{
public:
	MyArr();
	MyArr(const MyArr &curr);
	~MyArr();
	MyArr& operator = (const MyArr &curr);
	TYPE& operator [] (int index);

	void Add(const TYPE &element);
	int GetSize();
	void Clear();
	void Delete(int position);
	void SortQueries(int direction);

private:
	TYPE *arr;
	int size;
	int realSize;

	int step = 16;
	int mult = 2;
};

template <class TYPE>
MyArr<TYPE>::MyArr()
{
	realSize = step;
	size = 0;
	arr = (TYPE *)malloc(realSize * sizeof(TYPE));
}

template <class TYPE>
MyArr<TYPE>::~MyArr()
{
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

template <class TYPE>
MyArr<TYPE>::MyArr(const MyArr &curr)
{
	arr = (TYPE *)malloc(sizeof(TYPE)*curr.realSize);
	realSize = curr.realSize;
	size = curr.size;
}

template <class TYPE >
MyArr<TYPE >& MyArr<TYPE >::operator = (const MyArr &curr)
{
	if (this == &curr)
	{
		return *this;
	}

	if (curr.size == 0)
	{
		Clear();
	}

	return *this;
}

template <class TYPE>
int MyArr<TYPE>::GetSize()
{
	return size;
}

template <class TYPE >
void MyArr<TYPE >::Delete(int position)
{
	if (size == 1)
	{
		Clear();
	}
	else
	{
		for (int i = position; i < size - 1; i++)
		{
			arr[i] = arr[i + 1];
		}
		size--;
	}
}

template <class TYPE>
void MyArr<TYPE>::Clear()
{
	size = 0;
	realSize = step;
}

template <class TYPE>
TYPE& MyArr<TYPE>::operator [] (int index)
{
	return arr[index];
}

template <class TYPE>
void MyArr<TYPE>::Add(const TYPE &element)
{
	size++;
	if (size > realSize)
	{
		realSize *= mult;
	}
	arr[size - 1] = element;
}
template <class TYPE>
void MyArr<TYPE>::SortQueries(int direction)
{
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size - 1; i++)
		{
			Query temp;

			if (direction == 1)
			{
				if (arr[i].floor > arr[i + 1].floor)
				{
					temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
				}
			}
			else
			{
				if (arr[i].floor < arr[i + 1].floor)
				{
					temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
				}
			}

		}
	}
}
