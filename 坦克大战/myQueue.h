#pragma once
#include"functions.h"

class myQueue
{
	struct Node
	{
		int count;
		int x;
		int y;
		Node* prev;
		Node* next;
	};
public:
	myQueue();
	~myQueue();

	void push(int x, int y, int count = 60);
	void pop();
	bool empty();
	int front_count();
	int front_x();
	int front_y();
	int getsize();
private:
	Node* head;
	Node* tail;
	int size;
};

