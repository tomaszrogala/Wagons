#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


struct Node
{
	int data;
	Node *next;

	Node()
	{
		next = NULL;
	}
};

struct Stack
{
	Node *head;
	Node *tail;

	void push(int number);
	int pop();
	void view();
	void clear();
	bool check();

	Stack()
	{
		head = NULL;
		tail = NULL;
	}
};

void Stack::push(int number)
{
	Node *new_node = new Node;
	new_node->data = number;

	if (head == NULL)
	{
		head = new_node;
		return;
	}
	if (head != NULL && tail == NULL)
	{
		tail = head;
		head = new_node;
		head->next = tail;
		return;
	}
	if (head != NULL && tail != NULL)
	{
		new_node->next = head;
		head = new_node;
		return;
	}
}

int Stack::pop()
{
	int x = 0;
	Node *buffer;

	if (head == tail)
	{
		buffer = head;
		head = NULL;
		tail = NULL;
		x = buffer->data;
		delete buffer;
	}
	else
	{
		buffer = head;
		head = head->next;
		buffer->next = NULL;
		x = buffer->data;
		delete buffer;
	}

	return x;
}

void Stack::view()
{
	Node *pointer = head;
	if (head == NULL && tail == NULL)
	{
		std::cout << "stos jest pusty";
	}
	else
	{
		while (pointer != tail)
		{
			std::cout << pointer->data << ',';
			pointer = pointer->next;
		}
	}
	if (tail != NULL)
	{
		std::cout << tail->data << '\n';
	}
}

void Stack::clear()
{
	Node *buffer;

	while (head != NULL && tail != NULL)
	{
		if (head == tail)
		{
			buffer = head;
			head = NULL;
			tail = NULL;
			delete buffer;
		}
		else
		{
			buffer = head;
			head = head->next;
			buffer->next = NULL;
			delete buffer;
		}
	}
}

bool Stack::check()
{
	Node *pointer;
	pointer = head;

	if (tail != NULL)
	{
		while (pointer != tail)
		{
			if (pointer->data > pointer->next->data)
			{
				pointer = pointer->next;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

int exp(int base, int index)
{
	int x = 1;

	for (int i = 0; i < index; i++)
	{
		x *= base;
	}

	return x;
}

int input(char *&pointer)
{
	int x = 0;
	int k = 0;

	while (*pointer != ' ' && *pointer != '\n' && *pointer != '\0' && pointer != NULL)
	{
		k++;
		pointer++;
	}
	for (int i = 0; i < k; i++)
	{
		pointer--;
		x = x + ((*pointer - 48) * exp(10, i));
	}
	pointer = pointer + k;

	return x;
}


int main()

{
	bool flag = true; int number = 0; int size = 0; int m_size = 0; int size2 = 0;
	
	char array_in_1[100]; char array_in[10000]; char array_out[10000]; char *pointer; char *pointer2;
	
	Stack side_platform; Stack siding; Stack platform;

//-----------------------WPROWADZENIE DANYCH WEJŒCIOWYCH:

	fgets(array_in_1, 100, stdin);
	pointer2 = &array_in_1[0];

	while (pointer2 != NULL || pointer2 != '\0')
	{
		m_size = input(pointer2);

		fgets(array_in, 10000, stdin);

		pointer = &array_in[0];
		size = 0;

		for (int i = 0; i < m_size; i++)
		{
			array_out[i] = input(pointer);
			pointer++;
			size++;
		}

		for (int i = size - 1; i >= 0; i--)
		{
			side_platform.push(array_out[i]);
		}

//--------------------SPRAWDZENIE MO¯LIWOŒCI UPORZ¥DKOWANIA WAGONÓW:

		while (side_platform.head != NULL && side_platform.tail != NULL)
		{

			if (siding.head != NULL && platform.head != NULL)
			{
				if ((platform.head->data + 1) == siding.head->data)
				{
					platform.push(siding.pop());
				}
			}

			if (side_platform.head->next != NULL)
			{
				if (side_platform.head->data > side_platform.head->next->data)
				{
					siding.push(side_platform.pop());
				}
				else
				{
					platform.push(side_platform.pop());
				}
			}
			else if (siding.head != NULL)
			{
				if (siding.head->data < side_platform.head->data)
				{
					siding.push(side_platform.pop());
				}
				else
				{
					platform.push(side_platform.pop());
				}
			}
			else
			{
				siding.push(side_platform.pop());
			}
		}

//---------------------------------------------------------------------------------------------------------

		if (side_platform.head == NULL && side_platform.tail == NULL)
		{
			while (siding.head != NULL)
			{
				platform.push(siding.pop());
			}
		}

		if (platform.check() == true)
		{
			std::cout << "TAK";
			break;
		}
		else
		{
			std::cout << "NIE";
			break;
		}

	}

	platform.clear();
	siding.clear();
	side_platform.clear();

	return 0;
}