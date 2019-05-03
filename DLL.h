// MADALYN TOTH

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DLL
{
	public:
		ListNode<T> *front;
		ListNode<T> *back;
		unsigned int size;

		DLL()
		{
			size = 0;
			front = NULL;
			back = NULL;
		}

		~DLL()
		{
			delete front;
			delete back;
		}

		void insertBack(T d)
		{
			ListNode<T> *node = new ListNode<T>(d);

			if (size == 0) // if list is empty 
			{
				front = node;
			}

			else
			{
				back->next = node;
				node->prev = back;
			}

			back = node;
			++size;
		}

		T removeFront()
		{
		    if (!isEmpty())
		    {
				ListNode<T> *oldFront = front;

			    T oldData = oldFront->data;

				if (front->next == NULL) // if only one element exists 
				{
			        front = NULL;
			        back = NULL;
				}

				else // if more than one element exists 
				{
					front->next->prev = NULL;

			        front = front->next;
				}

				delete oldFront;
				size--;
				return oldData;
		    }

			else
			{
				return T();
			}
		}

		void removeAt(int pos)
		{
			int index = 0;
			ListNode<T> *current = front;
			ListNode<T> *previous = front;

			while (index != pos)
			{
				previous = current;
				current = current->next;
				++index;
			}

			previous->next = current->next;
			current->next->prev = previous;
			current->next = NULL;
			current->prev = NULL;

			size--;
			delete current;
		}

		T getFront()
		{
			return front->data;
		}

		void printList()
		{
			if (front != NULL)
			{
				ListNode<T> *current = front;

				while (true)
				{
					if (current == NULL)
					{
						break;
					}

					cout << current->data << ", " << endl;
					current = current->next;
				}
			}

			else
			{
				cout << "None" << endl;
			}
		}

		unsigned int getSize()
		{
			return size;
		}

        bool isEmpty()
		{
		    return (size == 0);
		}
};