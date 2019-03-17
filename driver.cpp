#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MovieTree.hpp"

using namespace std;


void Menu(MovieTree& root);


int main(int argc, char const *argv[])
{
	if(argc==1)
	{
		cout<<"Not enough command line arguments."<<endl;
		return -1;
	}
	ifstream inFile;	
	inFile.open(argv[1]);
	int indicator, numcopies, year, ranking;
	string line, linep, part, title;
	indicator=0;
	MovieTree website;
	// Loop for taking data from file and organizing it into nodes
	while(inFile.is_open())
	{
		getline(inFile, line);
		istringstream ss(line);

		//Stops the loop from continuing forever... the file should contain an EOF but does not
		if(line==linep)
		{
			inFile.close();
			break;
		}
		// Parse line into pieces
		while(getline(ss, part, ','))
		{
			//cout<<"Part is: "<<part<<endl;
			if(indicator%4==0)
			{
				ranking=stoi(part);
			}
			else if(indicator%4==1)
			{
				title=part;
			}
			else if(indicator%4==2)
			{
				year=stoi(part);
			}
			else if(indicator%4==3)
			{
				numcopies=stoi(part);
			}
			indicator++;
		}
		website.addMovieNode(ranking, title, year, numcopies);
		linep=line;
	}
	Menu(website);
	return 0;
}

void Menu(MovieTree& root)
{
	while(1)
	{
	cout << "======Main Menu======" << endl;
	cout << "1. Find a movie" << endl;
	cout << "2. Rent a movie" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Delete a movie"<< endl;
	cout << "5. Count movies"<< endl;
	cout << "6. Quit" << endl;
	string input, selection;
	getline(cin, input);
	if(input=="1"|| input=="Find")
	{	
		cout << "Enter title:" << endl;
		getline(cin, selection);
		root.findMovie(selection);
	}
	else if(input=="2"|| input=="Rent")
	{
		cout << "Enter title:" << endl;
		getline(cin, selection);
		root.rentMovie(selection);		
	}
	else if(input=="3"|| input=="Print")
	{
		root.printMovieInventory();
	}
	else if(input=="4"|| input=="Delete")
	{
		cout<<"Enter title:"<<endl;
		getline(cin, selection);
		root.deleteMovie(selection);
	}
	else if(input=="5"|| input=="Count")
	{
		root.countMovies();
	}
	else if(input=="6"|| input=="Quit")
	{
		cout << "Goodbye!" << endl;
		return;
	}
	else
	{
		cout<<"Could not understand, please try again"<<endl;
	}
	}
}