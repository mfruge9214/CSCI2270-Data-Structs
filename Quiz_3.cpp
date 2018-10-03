#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Node{
	int data;
	Node *next;
};

Node* initializeLL(int val)
{
	Node* head=new Node;
	head->data=val;
	head->next=NULL;
	return head;
}

void addNode(Node* head, int val)
{
	Node* temp=head;
	Node* newnode=new Node;
	Node* prev=head;
	newnode->data=val;
	newnode->next=NULL;
	while(temp!=newnode)
	{
		if(temp->next==nullptr)
		{
			temp->next=newnode;
		}
		temp=temp->next;
	}
}

Node* deleteKey(Node* head, int key)
{
	Node* temp=head;
	Node* prev=head;
	if(temp->data==key) //Takes care of the border case if head needs to be deleted
	{
		temp=head->next;
		delete head;
		head=temp;
		return head;
	}
	while(temp!=NULL && temp->data!=key)
	{
		prev=temp;
		temp=temp->next;
	}
	if(temp->data==key && temp!=NULL) // Case where deletion happens in the middle of the list
	{
		
		prev->next=temp->next;
		delete temp;
	}
	else if(temp->data==key && temp==NULL) // Case where deletion happens at end of list
	{
		prev->next=NULL;
		delete temp;
	}

	return head;
}

int LinkedListFindMin(Node *head)
{
	Node* temp=head;
	int min=head->data;
	while(temp!=NULL)
	{
		if(temp->data<min)
		{
			min=temp->data;
		}
		temp=temp->next;
	}
	return min;
}

int main(int argc, char const *argv[])
{
	Node* head=initializeLL(5);
	addNode(head, -5);
	addNode(head, 1000);
	addNode(head, 55);
	addNode(head, 0);
	int min=LinkedListFindMin(head);
	cout<<min<<endl;
	/*head=deleteKey(head, 1);
	head=deleteKey(head, 5);
	head=deleteKey(head, 2);*/
	Node* temp=head;
	while(temp!=NULL)
	{
		cout<< temp->data<<endl;
		temp=temp->next;
	}
	return 0;
}