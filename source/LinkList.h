#pragma once
#include <iostream>
#include <vector>
using namespace std;
template <class let>
class LinkList
{
public:
	class Node
	{
		friend class LinkList<let>;
		let data;
		Node* next;
		Node* prev;
	public:
		Node()
		{
			next = prev = nullptr;
		}
		Node(let data, Node* next) : data{ data }, next{ next }, prev{ nullptr }{}
	};
	
	LinkList()
	{
		//giving dummy head node
		head = new Node();
	}
	LinkList(const LinkList<let>& rhs)
	{
		head = new Node();
		Node* thisCurrent = head;
		Node* current = rhs.head;
		while (current->next != nullptr)
		{
			thisCurrent->next = new Node(current->next->data, current->next->next);
			thisCurrent->next->prev = thisCurrent;
			current = current->next;
			thisCurrent = thisCurrent->next;
		}

	}

	void insertAtHead(let value)
	{


		Node* newNode = new Node(value, head->next);
		head->next = newNode;
		newNode->prev = head;
		if (newNode->next != nullptr)
		{
			newNode->next->prev = newNode;
		}

	}
	void deleteAtHead()
	{
		if (head->next != nullptr)
		{
			Node* temp = head->next;

			head->next = head->next->next;
			if (head->next != nullptr)
			{
				head->next->prev = head;
			}

			//delete temp;
		}
	}
	void removeEntries(let value)
	{
		Node* current = head->next;
		Node* prev = head;
		while (current != nullptr)
		{
			if (current->data == value)
			{
				Node* temp = current;

				prev->next = current->next;
				current = current->next;

				if (current != nullptr)
				{
					current->prev = prev;
				}


				delete temp;

			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
	}
	void replaceAll(let element, let value)
	{
		Node* current = head->next;
		while (current != nullptr)
		{
			if (current->data == element)
			{
				current->data = value;

			}
			current = current->next;
		}
	}
	void printTechnically()
	{
		cout << "=================Link List================" << endl;
		Node* current = head->next;
		while (current != nullptr)
		{
			cout << "Value of current : " << current << " <=> ";
			cout << " [ " << current->data << " ( " << current->prev << " , " << current->next << " ) ]";
			cout << endl;
			current = current->next;
		}
	}
	void swap(int index1, int index2)
	{
		Node* prev1 = head;
		Node* prev2 = head;
		Node* current1 = head->next;
		Node* current2 = head->next;

		Node* current = head->next;
		int i = 0;
		while (current != nullptr)
		{
			if (i < index1)
			{
				prev1 = current1;
				current1 = current1->next;
			}
			if (i < index2)
			{
				prev2 = current2;
				current2 = current2->next;
			}
			i++;
			current = current->next;
		}

		if (index2 - index1 > 1)
		{
			prev2->next = prev2->next->next;
			prev1->next = prev1->next->next;

			current2->next = prev1->next;
			current2->prev = prev1;
			if (current2->next != nullptr)
			{
				current2->next->prev = current2;
			}

			prev1->next = current2;
			current2->prev = prev1;

			current1->next = prev2->next;
			prev2->next = current1;

			if (current1->next != nullptr)
			{
				current1->next->prev = current1;
			}

			prev2->next = current1;
			current1->prev = prev2;
		}
		else if (index2 - index1 == 0)
		{
			return;
		}
		else
		{
			prev1->next = current2;
			current2->prev = prev1;
			current1->next = current2->next;
			if (current1->next != nullptr)
			{
				current1->next->prev = current1;
			}
			current2->next = current1;
			current1->prev = current2;


		}

	}
	class iterator
	{
		Node* current;
		friend class LinkList<let>;
	public:
		iterator()
		{
			current = nullptr;

		}
		iterator(Node* init) :current{ init } {}
		iterator& operator++()
		{
			if (current == nullptr) return *this;
			current = current->next;
			return *this;
		}
		Node* giveCurrent()
		{
			return current;
		}
		iterator operator+(int number)
		{
			if(current != nullptr)
				return current->next;
			
			return current;

		}
		iterator operator++(int)
		{
			if (current == nullptr) return *this;

			iterator temp = *this;
			++(*this);
			return temp;
		}
		iterator& operator--()
		{
			if (current== nullptr) return *this;


			current = current->prev;
			return *this;
		}
		iterator operator--(int)
		{
			if (current == nullptr) return *this;
			iterator temp = *this;
			--(*this);
			return temp;
		}
		let& operator*()
		{
			if(current!=nullptr)
			return current->data;
		}
		bool operator==(iterator rhs)
		{
			return current == rhs.current;
		}
		bool operator!=(iterator rhs)
		{
			return !(current == rhs.current);
		}

	};
	iterator begin()
	{
		return head->next;

	}
	iterator extremeBegin()
	{
		return head;
	}
	iterator end()
	{
		return nullptr;
	}
	int size()
	{
		int total = 0;
		for (iterator i = begin(); i != end(); ++i)
		{
			total++;
		}
		return total;
	}
	void insert(iterator obj, let value)
	{
		Node* current = obj.current;
		Node* newNode = new Node(value, current->next);
		current->next = newNode;
		newNode->prev = current;
		if (newNode->next != nullptr)
		{
			newNode->next->prev = newNode;
		}
	}
	void insertMultiple(iterator obj, let values[], int size)
	{
		for (int i = size - 1; i >= 0; --i)
		{
			insert(obj, values[i]);
		}
	}
	void deleteNode(iterator& i)
	{
		Node* temp = i.current;
		if (i.current->prev == nullptr) return;

		i.current->prev->next = i.current->next;

		if (i.current->next != nullptr)
		{
			i.current->next->prev = i.current->prev;
		}

		if(i.current->prev!=nullptr) // might be prev->prev
			i--;
		delete temp;
	}
	void deleteMultiple(iterator i, let values[], int size)
	{
		while (i != nullptr)
		{
			for (int j = 0; j < size; ++j)
			{
				if (i.current->data == values[j])
				{
					deleteNode(i);
				}
			}
			++i;
		}
	}
	void deleteInRange(iterator i, iterator j)
	{
		while (i + 1 != j)
		{
			Node* temp = i.current->next;
			i.current->next = i.current->next->next;
			i.current->next->prev = i.current;
			delete temp;
		}
	}
	iterator searchFirst(let value)
	{
		iterator* iptr = new iterator{ begin() };
		while (*iptr != end())
		{
			if (iptr->current->data == value)
			{
				return *iptr;
			}
			else
				(*iptr)++;
		}
		return nullptr;
	}
	vector <LinkList<let>::iterator> searchAll(let value)
	{
		vector <LinkList<let>::iterator> list;
		for (LinkList<let>::iterator i = begin(); i != end(); ++i)
		{
			if (*i == value)
			{
				LinkList<let>::iterator newIterator = i;
				list.push_back(newIterator);
			}
		}

		return list;	
	}
private:

	Node* head;

};
