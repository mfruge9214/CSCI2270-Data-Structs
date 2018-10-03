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
		void setData(string _title, int _year, double _rating);
		void setTitle(string _title);
		void setYear(int _year);
		void setRating(double _rating);
		string getTitle();
		int getYear();
		double getRating();
		void printMovie();

}

void Movie::setData(string _title, int _year, double _rating)
{
	title=_title;
	year=_year;
	rating=_rating;
}

void Movie::setTitle(string _title)
{
	title=_title
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
	Movie M, HappyG;
	return 0;
}