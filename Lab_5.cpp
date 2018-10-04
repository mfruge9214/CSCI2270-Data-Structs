#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
int key;
Node *previous;
Node *next;
};


class DLL{
private:
	Node* head;
	Node* tail;
public:
	DLL();
	void append(int val);
	void print();
	void printReverse();
};

DLL::DLL()
{
	head=NULL;
	tail=NULL;
}

void DLL::append(int val)
{
	Node* newnode= new Node;
	newnode->key=val;
	newnode->next=NULL;
	newnode->previous=NULL;
	if(tail==NULL)
	{
		head=newnode;
		tail=newnode;
		return;
	}
	newnode->previous=tail;
	tail->next=newnode;
	tail=newnode;
	return;
}

void DLL::printReverse()
{
	Node* temp=tail;
	while(temp!=NULL)
	{
		cout<<temp->key<<endl;
		temp=temp->previous;
	}
}

int main()
{
	DLL list;
	cout<<"appending 1, 3, 5"<< endl;
	list.append(1);
	list.append(3);
	list.append(5);
	list.printReverse();
}