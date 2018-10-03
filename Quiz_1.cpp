#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;




struct Word
{
	string word;
	string rootLang;
	int length;
};


class State
{
private:
	string name;
public:
	State(string _name);
	void setName(string _name);
	string getName();
};

State::State(string _name)
{
	name=_name;
}

void State::setName(string _name)
{
	name=_name;
}

string State::getName()
{
	return name;
}

int differ(int x, int y)
{
	return y-x;
}

int function()
{
	int value=35;
	return value+5;
	value +=10;
}

int insertInArray(float listInput[ ], int capOfArray, int* numItems, int index, float newVal)
{
	if(capOfArray==*numItems)
	{
		return -1;
	}
	else
	{
		for(int i=*numItems; i>=index; i--)
		{
			listInput[i]=listInput[i-1];
		}
		listInput[index]=newVal;
		(*numItems)++;
	}
	return 0;
}

	
int main(int argc, char const *argv[])
{
	int rtn;
	int x=4;
	int limit=5;
	float array[limit]={9,2,8,3};
	int* numEl;
	numEl=&x;
	int index=2;
	float val=3.5;
	cout<< "numEl= "<< numEl<< endl;
	cout<< "*numEl= "<< *numEl<<endl;
	rtn=insertInArray(array, limit, numEl, index, val);
	cout<<"Number of elements: "<< x<<endl;
	for(int i=0; i<limit; i++)
	{

		cout<<array[i]<<endl;
	}

	/* Question 7
	for(int i=0; i<numElements; i++)
	{
		cout<<details[i];
		if(details[i]==key)
		{
			break;
		}

		cout<<",";
	}*/
	return 0;
} 