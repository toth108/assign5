// MADALYN TOTH

template <class T>
class GenStack
{
	public:
		GenStack();
		GenStack(int maxSize);
		~GenStack();

		void push(T data);
		T pop();
		T peek();
		T resize();

		int isFull();
		int isEmpty();

		int getSize(); 
		void setArray(T *a);
		int setSize(int newSize); 
		T* getArray();

		int top;
		int max;
		int size; 
		T *myArray;
};

template <class T>
GenStack<T>::GenStack()
{
    myArray = new T[30];
    size = myArray.size(); 
    top = -1; 
}

template <class T>
GenStack<T>::GenStack(int maxSize)
{
	// error checking 
    if(maxSize <1) 
    {
        cout << "ERROR: Max size must be a number greater than 0." << endl; 
    }
	else
    {
	    myArray = new T[maxSize];
	    max = maxSize;
	    top = -1;
	}
}

template <class T>
GenStack<T>::~GenStack()
{
	delete []myArray;
}

template <class T>
void GenStack<T>::push(T data)
{
	// make sure stack is not full 
    if (isFull())
    {
        resize();
    }

	myArray[top++] = data; // top is not 0 
}

template <class T>
T GenStack<T>::pop()
{
	// error checking 
    if(top == -1) 
    {
        cout << "ERROR: Stack is empty." << endl; 
    }
	else 
    {
        return myArray[top--]; 
    }
}

template <class T>
T GenStack<T>::peek()
{
	return myArray[top];
}

template<class T>
T GenStack<T>::resize()
{
    T *newStack;
    int newSize = (getSize()*2);
    newStack = new T[newSize];
    for (int i = 0; i < size; i++)
    {
        newStack[i] = myArray[i];
    }
    setSize(newSize);
    setArray(newStack);
}

template<class T>
int GenStack<T>::isFull()
{
    return (top == size-1);
}

template<class T>
int GenStack<T>::isEmpty()
{
    return (top == -1);
}

template<class T>
int GenStack<T>::getSize() 
{
    return top+1;
}

template <class T>
void GenStack<T>::setArray(T *a)
{
    myArray = a;
}

template<class T>
int GenStack<T>::setSize(int newSize) 
{
    size = newSize; 
    return newSize;
}

template <class T>
T* GenStack<T>::getArray()
{
    return myArray;
}