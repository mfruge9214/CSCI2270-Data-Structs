#include <string>
#include <iostream>
#include <array>
#include <fstream>
#include "HashTable.hpp"

/*===========================
Author: Michael Fruge
Assignment: Word Processing with Hash Tables
Date: 11/6/18
=============================*/

using namespace std;

HashTable::HashTable(int tableSize)
{
	hashTableSize=tableSize;
	numCollisions=0;
	numItems=0;
	hashTable=new wordItem*[hashTableSize];
	for (int i = 0; i < hashTableSize; i++)
	{
		hashTable[i]=NULL;
	}
}

HashTable::~HashTable()
{
	wordItem* temp;
	wordItem* temp2;
	for(int i=0; i<hashTableSize; i++)
	{
		temp=hashTable[i];
		while(temp!=NULL)
		{
			temp2=temp->next;
			delete temp;
			temp=temp2;
		}
	}
	delete[] hashTable;
}

unsigned int HashTable::getHash(string key)
{
	unsigned int hash=5381;
	int length=key.length();
	for (int i = 0; i < length; i++)
	{
		hash=33*hash+key[i];
	}
	hash=hash%hashTableSize;
	return hash;
}

//Add word Helper
wordItem* createWordItem(string key)
{
	wordItem* newword= new wordItem;
	newword->word=key;
	newword->next=NULL;
	newword->count=1;
	return newword;
}

void HashTable::addWord(string key)
{
	int index=getHash(key);
	wordItem* newword=createWordItem(key);
	wordItem* temp=hashTable[index];
	if(temp==NULL)
	{
		hashTable[index]=newword;
	}
	else
	{
		newword->next=temp;
		hashTable[index]=newword;
		numCollisions++;
	}
	numItems++;
}


wordItem* HashTable::searchTable(string key)
{
	int index=getHash(key);
	wordItem* temp=hashTable[index];
	while(temp!=NULL)
	{
		if(temp->word==key)
		{
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}

bool HashTable::isInTable(string key)
{
	wordItem* temp=searchTable(key);
	if(temp==NULL)
	{
		return false;
	}
	return true;
}

void HashTable::incrementCount(string key)
{
	wordItem* temp=searchTable(key);
	if(temp!=NULL)
	{
		temp->count++;
	}
}

int HashTable::getNumCollisions()
{
	return numCollisions;
}

int HashTable::getNumItems()
{
	return numItems;
}

int HashTable::getTotalNumWords()
{
	wordItem* temp;
	int count=0;
	for(int i=0; i<hashTableSize; i++)
	{
		temp=hashTable[i];
		while(temp!=NULL)
		{
			count+=temp->count;
			temp=temp->next;
		}
	}
	return count;
}

int findMin(wordItem* arr[], int n)
{
	int min=9999999;
	wordItem* temp;
	int j;
	for (int i = 0; i <n ; i++)
	{
		if(arr[i]->count<min)
		{
			temp=arr[i];
			min=temp->count;
			j=i;
		}
	}
	return j;
}

void sortArray(wordItem** arr, int n)
{
	int currMaxIdx;
	wordItem* temp;
	for (int i=0;i<n-1;i++)
	{
		currMaxIdx=i;
		for(int j=i+1; j<n; j++)
		{
			if(arr[j]->count>arr[currMaxIdx]->count)
			{
				currMaxIdx=j;
			}
		}
		temp=arr[currMaxIdx];
		arr[currMaxIdx]=arr[i];
		arr[i]=temp;
	}
}

void HashTable::printTopN(int n) //Populate the array and keep it sorted, then kick out the last element each time 
//and replace it with the new element that needs to go in while keeping the array sorted
{
	int counter=0;
	int replace;
	wordItem* topN[n];
	wordItem* temp;
	for(int i=0; i<hashTableSize; i++)
	{
		temp=hashTable[i];
		while(temp!=NULL)
		{
			if(counter<n) // If the array is not fully populated yet
			{
				topN[counter]=temp;
				counter++;
			}
			else
			{
				replace=findMin(topN, n);
				if( temp->count > topN[replace]->count )
				{
					topN[replace]=temp;
				}
			}
			temp=temp->next;
		}
	}
	sortArray(topN, n);
	for(int i=0; i<n; i++)
	{
		cout<<topN[i]->count<<" - "<<topN[i]->word<<endl;
	}
}


void getStopWords(char *ignorefilename, HashTable &table)
{
	string input;
	ifstream inFile(ignorefilename);
	while(getline(inFile, input))
	{
		table.addWord(input);
	}
}

bool isStopWord(string word, HashTable &table)
{
	bool indicator;
	indicator=table.isInTable(word);
	return indicator;
}

