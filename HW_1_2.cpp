#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/*Use an ampersand, pass by value*/
struct student
{
	string username;
	float gpa;
	int age;
};

void addUser(vector<student> &gradeList, string name, float _gpa, int _age)
{
	student stud;
	stud.username=name;
	stud.gpa=_gpa;
	stud.age=_age;
	gradeList.push_back(stud);
};

void printList(const vector<student> gradeList)
{
	for(int i=0; i<gradeList.size(); i++)
	{
	cout<<gradeList[i].username<<" ["<<gradeList[i].gpa<<"] age:"<<gradeList[i].age<<endl;
	}
};

int main(int argc, char const *argv[])
{
	string input, username, data;
	vector<student> vec;
	int count=0;
	int age;
	float gpa;
	if (argc!=2)
	{
		cout<<"Not Enough Command Line Arguments"<< endl;
	}

	ifstream inFile(argv[1]);
	while(getline(inFile, input))
	{
		stringstream ss(input);
		while(getline(ss, data, ','))
		{
			if(count%3==0)
			{
				username=data;
			}
			else if(count%3==1)
			{
				gpa=stof(data);
			}
			else if(count%3==2)
			{
				age=stoi(data);
			}
			count++;
		}
		addUser(vec, username, gpa, age);
	}
	printList(vec);
	inFile.close();
	return 0;
}