#include <string>
#include <iostream>
using namespace std;

int myFunc(int n)
{
	int result=0;
	if (n<=0)
	{
		return 0;
	}
	if (n==1)
	{
		return 1;
	}
	result=myFunc(n-1)+myFunc(n-3);
	return result;
}
void calculateCost(int count, float& subtotal, float& taxCost)
{
	if(count < 10)
	{
		subtotal=count*.5;
	}
	else
	{
		subtotal=count*.20;
	}
	taxCost=.1*subtotal;
}

int main(int argc, char const *argv[])
{
	//cout<< myFunc(4)<< endl;
	int x=9;
	int* gPointer=&x;
	int number;
	number=*gPointer;
	cout<<"number = "<< number <<endl;
	float tax= 0.0;
	float distance= 17.9;
	float subtotal= 0.0;
	calculateCost(15, subtotal, tax);
	//cout<< "The cost for 15 items is "<< subtotal<<", and the tax for"<< subtotal<< " is"<< tax<< endl;
	return 0;
}