/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/


using namespace std;
template <class TYPE>
class  MyVector {
public:

	typedef TYPE* Iterator;

	MyVector();
	MyVector(int size);
	MyVector(int size, const TYPE & initial);
	MyVector(const MyVector<TYPE>& v);
	~MyVector();
	

	int Capacity() const;
	int GetSize() const;
	bool IsEmpty() const;
	void Push(const TYPE& value);
	void Pop();
	void Erase(int index);

	void Reserve(int capacity);
	void Resize(int size);

	//TODO
	TYPE & operator[](int index);
	MyVector<TYPE> & operator = (const MyVector<TYPE> &);
	void Clear();
private:
	 int size;
	 int capacity;
	 int Grow;
	TYPE* elements;
};

template<class TYPE>
MyVector<TYPE>::MyVector()
{
	capacity = 0;
	size = 0;
	elements = 0;
	Grow = 0;
}

template<class TYPE>
MyVector<TYPE>::MyVector(const MyVector<TYPE> & value)
{
	size = value.size;
	Grow = value.Grow;
	capacity = value.capacity;
	elements = new TYPE[size];

	for (int i = 0; i < size; i++) 
	{
		elements[i] = value.elements[i];
	}
}

template<class TYPE>
MyVector<TYPE>::MyVector(int size) 
{
	size = size;
	Grow = ceil(log((double)size) / log(2.0));
	capacity = 1 << Grow;
	elements = new T[capacity];
}

template <class TYPE>
bool MyVector<TYPE>::IsEmpty() const 
{
	return size == 0;
}

template<class TYPE>
MyVector<TYPE>::MyVector(int size, const TYPE& initial) 
{
	size = size;
	Grow = ceil(log((double)size) / log(2.0));
	capacity = 1 << Grow;
	elements = new TYPE[capacity];
	for (unsigned int i = 0; i < size; i++)
		elements[i] = initial;
}

template<class TYPE>
MyVector<TYPE>& MyVector<TYPE>::operator = (const MyVector<TYPE> & value)
{
	delete[] elements;
	size = value.size;
	Grow = value.Grow;
	capacity = value.capacity;
	elements = new TYPE[capacity];
	for (int i = 0; i < size; i++)
	{
		elements[i] = v.elements[i];
	}
	
	return *this;
}
template<class TYPE>
TYPE& MyVector<TYPE>::operator[](int index) 
{
	return elements[index];
}

template<class TYPE>
void MyVector<TYPE>::Push(const TYPE & value)
{
	if (size >= capacity) {
		Reserve(1 << Grow);
		Grow++;
	}
	elements[size++] = value;
}

template<class TYPE>
void MyVector<TYPE>::Pop() 
{
	size--;
}
template<class TYPE>
void MyVector<TYPE>::Erase(int index)
{
	for (int i = index; i < size - 1; i++)
	{
		elements[i] = elements[i + 1];
	}
	size--;
}

template<class TYPE>
void MyVector<TYPE>::Reserve(int capacity)
{
	TYPE* newelements = new TYPE[capacity];

	for (int i = 0; i < size; i++) 
	{
		newelements[i] = elements[i];
	}

	capacity = capacity;
	delete[] elements;
	elements = newelements;
}

template<class TYPE>
int MyVector<TYPE>::GetSize() const 
{
	return size;
}

template<class TYPE>
void MyVector<TYPE>::Resize(int size)
{
	Grow = ceil(log((double)size) / log(2.0));
	reserve(1 << Grow);
	size = size;
}

template<class TYPE>
int MyVector<TYPE>::Capacity()const
{
	return capacity;
}

template<class TYPE>
MyVector<TYPE>::~MyVector() 
{
	delete[] elements;
}

template <class TYPE>
void MyVector<TYPE>::Clear()
{
	capacity = 0;
	size = 0;
	elements = 0;
	Grow = 0;
}
