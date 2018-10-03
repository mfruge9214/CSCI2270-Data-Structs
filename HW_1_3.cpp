#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Movie
{
	private:
		string title;
		int year;
		double rating;
	public:
		Movie();
		Movie(string _title, int _year, double _rating);
		void setData(string _title, int _year, double _rating);
		void setTitle(string _title);
		void setYear(int _year);
		void setRating(double _rating);
		string getTitle();
		int getYear();
		double getRating();
		void printMovie();

};


Movie::Movie()
{
	title="unknown";
	year=2016;
	rating=0.0;
}

Movie::Movie(string _title, int _year, double _rating)
{
	title=_title;
	year=_year;
	rating=_rating;
}

void Movie::setData(string _title, int _year, double _rating)
{
	title=_title;
	year=_year;
	rating=_rating;
}

void Movie::setTitle(string _title)
{
	title=_title;
}

void Movie::setYear(int _year)
{
	year=_year;
}

void Movie::setRating(double _rating)
{
	rating=_rating;
}

string Movie::getTitle()
{
	return title;
}

int Movie::getYear()
{
	return year;
}

double Movie::getRating()
{
	return rating;
}

void Movie::printMovie()
{
	std::cout<< "Title: "<< title <<", Year: "<< year <<", Rating: "<< rating<< endl;
}


int main(int argc, char const *argv[])
{
	Movie M;
	Movie HappyG("Happy Gilmore", 1996, 7.0);
	Movie Shaw;
	Shaw.setTitle("The Shawshank Redemption");
	Shaw.setYear(1994);
	Shaw.setRating(9.3);
	string movietitle=Shaw.getTitle();
	int movieyear=Shaw.getYear();
	double movierating=Shaw.getRating();
	M.setData("unknown",2016,0.0);
	M.printMovie();
	HappyG.printMovie();
	cout<< movietitle<<endl;
	cout<< movieyear << endl;
	cout<< movierating<< endl;
	return 0;
}