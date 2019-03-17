#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MovieTree.hpp"

using namespace std;


int main(int argc, char const *argv[])
{
	MovieTree test;
	test.addMovieNode(1, "It Happened One Night", 2007, 1);
	test.addMovieNode(2, "The Godfather", 1933, 10);
	test.addMovieNode(3, "Walking Ned Divine", 2027, 3);
	test.addMovieNode(4, "X-Men", 2005, 4);
	test.rentMovie("Another Brick in the Wall");
	/*test.addMovieNode(1, "Primer", 1988, 3);
	test.printMovieInventory();
	test.deleteMovie("Primer");
	test.printMovieInventory();*/
	return 0;
}