#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include "MovieTree.hpp"

using namespace std;

MovieTree::MovieTree()
{
	root=NULL;
}

void destructMovieTreeHelper(MovieNode* root)
{
	if(root!=NULL)
	{
		destructMovieTreeHelper(root->leftChild);
		destructMovieTreeHelper(root->rightChild);
		delete root;
		root=NULL;
	}
}


MovieTree::~MovieTree() //Post-order traversal and deletion
{
	destructMovieTreeHelper(root);
}

void printMovieHelper(MovieNode* root)
{
	if(root==NULL)
		return;
	else
	{
		printMovieHelper(root->leftChild);
		cout << "Movie: " << root->title << " " << root->quantity << endl;
		printMovieHelper(root->rightChild);
	}
}

void MovieTree::printMovieInventory()
{
	printMovieHelper(root);
}

MovieNode* addMovieHelper(MovieNode* root, MovieNode* newmovie)
{
	int comp;
	if(root==NULL)
	{
		return newmovie;
	}
	string currtitle= root->title;
	comp=currtitle.compare(newmovie->title); // Comp is >0: if currtitle>newtitle and vice versa
	if(comp<0) 
	{
		root->rightChild=addMovieHelper(root->rightChild, newmovie);
		return root;
	}
	else
	{
		root->leftChild=addMovieHelper(root->leftChild, newmovie);
		return root;
	}
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
	MovieNode* newmovie= new MovieNode;
	newmovie->ranking=ranking;
	newmovie->title=title;
	newmovie->year=releaseYear;
	newmovie->quantity=quantity;
	root=addMovieHelper(root, newmovie);
}

// Search the sub-tree `node` for a descendant 
// node with the given title, and return 
// a pointer to that node.

MovieNode* searchHelper(MovieNode *node, string title)
{
	if(node==NULL)
	{
		return NULL;
	}
	string currtitle=node->title;
	int comp=currtitle.compare(title);
	if(comp<0)
	{
		return searchHelper(node->rightChild, title);
	}	
	else if(comp>0)
	{
		return searchHelper(node->leftChild, title);
	}
	return node;
}


void MovieTree::rentMovie(string title)
{
	MovieNode* target=searchHelper(root, title);
	if(target==NULL)
	{
		cout<<"Movie not found."<<endl;
		return;
	}
	else if(target->quantity>=1)
	{
		target->quantity--;
		cout << "Movie has been rented." << endl;
		cout << "Movie " << "'"<< target->title <<"' Info:"<< endl;
		cout << "================================" << endl;
		cout << "Ranking : " << target->ranking << endl;
		cout << "Title   : " << target->title << endl;
		cout << "Year    : " << target->year << endl;
		cout << "Quantity: " << target->quantity << endl;
	}
	if(target->quantity==0)
	{
		deleteMovie(title);
	}
}


void MovieTree::findMovie(string title)
{
	MovieNode* target=searchHelper(root, title);
	if(target==NULL)
	{
		cout<<"Movie not found. "<<endl;
		return;
	}
	cout << "Movie " << "'"<< target->title <<"' Info:"<< endl;
	cout << "================================" << endl;
	cout << "Ranking : " << target->ranking << endl;
	cout << "Title   : " << target->title << endl;
	cout << "Year    : " << target->year << endl;
	cout << "Quantity: " << target->quantity << endl;
}


int countMovieHelper(MovieNode* root)
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		int countL=countMovieHelper(root->leftChild);
		int countR=countMovieHelper(root->rightChild);
		return countL+countR+1;
	}
}

void MovieTree::countMovies()
{
	int count=0;
	count=countMovieHelper(root);
	cout<<"Count = "<< count <<endl;
}

MovieNode* findMin(MovieNode* root)
{
	if(root->leftChild==NULL)
	{
		return root;
	}
	return findMin(root->leftChild);
}

MovieNode* deleteMovieHelper(MovieNode* root, string title)
{
	if(root==NULL)
	{
		cout<< "Movie not found."<<endl;
		return NULL;
	}
	string currtitle=root->title;
	int comp=currtitle.compare(title);
	if(comp>0)
	{
		root->leftChild=deleteMovieHelper(root->leftChild, title);
	}
	else if(comp<0)
	{
		root->rightChild=deleteMovieHelper(root->rightChild, title);
	}
	else
	{
		if(root->leftChild==NULL && root->rightChild==NULL)
		{
			delete root;
			root=NULL;
		}
		else if(root->leftChild==NULL)
		{
			MovieNode* temp=root;
			root=root->rightChild;
			delete temp;
		}
		else if(root->rightChild==NULL)
		{
			MovieNode* temp=root;
			root=root->leftChild;
			delete temp;
		}
		else
		{
			MovieNode* minimum;
			minimum=findMin(root->rightChild);
			root->title=minimum->title;
			root->ranking=minimum->ranking;
			root->quantity=minimum->quantity;
			root->year=minimum->year;
			root->rightChild=deleteMovieHelper(root->rightChild, minimum->title);
		}
	}
	return root;
}

void MovieTree::deleteMovie(string title)
{
	root=deleteMovieHelper(root, title);
}