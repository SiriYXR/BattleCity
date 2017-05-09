#include "myQueue.h"

myQueue::myQueue()
{
	size = 0;
	head = new Node;
	tail = new Node;
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;
}


myQueue::~myQueue()
{
	while (!empty())
		pop();
	delete head;
	delete tail;
	head = NULL;
	tail = NULL;
}

void myQueue::push(int x, int y,int count)
{
	Node* p = new Node;
	p->count = count;
	p->x = x;
	p->y = y;
	p->next = tail;
	p->prev = tail->prev;
	tail->prev->next = p;
	tail->prev = p;
	p = NULL;
	size++;
}

void myQueue::pop()
{
	Node* p = head->next;
	head->next = p->next;
	p->next->prev = head;
	delete p;
	p = NULL;
	size--;
}

bool myQueue::empty()
{
	if (head->next == tail)
		return true;
	return false;
}

int myQueue::front_count()
{
	if (head->next == tail)
		return 0;
	return head->next->count;
}

int myQueue::front_x()
{
	if (head->next == tail)
		return 0;
	return head->next->x;
}

int myQueue::front_y()
{
	if (head->next == tail)
		return 0;
	return head->next->y;
}

int myQueue::getsize()
{
	return size;
}
