//===========================================
//Created: 9/19/2018
//By:Michael Fruge
//
//Description: Counts unique words in a file 
// Outputs the top n most common words
//===========================================

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct wordItem
{
	string word;
	int count;
};

/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into vector
* @param ignoreWordFile - filename (the file storing ignore/stop words)
* @param _vecIgnoreWords - store ignore words from the file (pass by reference)
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(const char *ignoreWordFileName, vector<string> &_vecIgnoreWords);
 
/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param _vecIgnoreWords - the vector type of string storing ignore/stop words
* @return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(string word, vector<string> &_vecIgnoreWords);
 
/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array (including repeated words)
* @param list - an array of wordItems containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including repeated words multiple times)
*/
int getTotalNumberNonStopWords(wordItem list[], int length);

/*
* Function name: arraySort
* Purpose: sort an array of wordItems, decreasing, by their count fields
* @param list - an array of wordItems to be sorted
* @param length - the length of the words array
*/
void arraySort(wordItem list[], int length);
 
/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of wordItems
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN);
 
const int STOPWORD_LIST_SIZE = 50;
 
const int INITIAL_ARRAY_SIZE = 100;
 
// ./a.out 10 HW2-HungerGames_edit.txt HW2-ignoreWords.txt

int main(int argc, char *argv[])
{
    // verify we have the correct # of parameters, else throw error msg & return
    if (argc != 4)
    {
        cout << "Usage: ";
        cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>";
        cout << endl;
        return 0;
    }
    // Parse the number of stopwords
    int topN=stoi(argv[1]);

    // Get Stopwords reads from the file, and saves what it reads into a vector, so we need to create them

    vector<string> vecIgnoreWords(STOPWORD_LIST_SIZE);
    getStopWords(argv[3], vecIgnoreWords); 
    // Now, vecIgnoreWords is populated with stopwords

    //By now, we have a vector of size 50 that is all stopwords
    // Next, we need to read in the words of the large text file and check if it is a stopword
    // We will do this by reading in each word of the book using a combination of getline and stringstream to parse the whitespace
    // and call isStopWord each loop
    bool ignore;
    bool addword;
    int numDoublings=0;
    string input, word;
    int numUniqueWords=0;
    int capacity=INITIAL_ARRAY_SIZE;
    ifstream inFile;
    inFile.open(argv[2]);
    wordItem* uniquewords;
    uniquewords=new wordItem [capacity];
    if(inFile.is_open())
    {
    	while(inFile>> word) // In this loop we will call isStopWord to see if word is a stopword
    	{
    		if(word=="\n") break; //To not count the spaces 
    		ignore=isStopWord(word, vecIgnoreWords);
    		if(!ignore)
    		{
    			addword=true;
    			for(int i=0; i<numUniqueWords; i++)// This loop checks if the word just read in from the file is unique or not
    			{
    				if(word==uniquewords[i].word) // If the word is in the array already, add 1 to the count
    				{
    					uniquewords[i].count++;
    					addword=false;
    				}
    			}
    			if(addword) //Make sure we need to add the word rather than increment a counter
    			{
    			//Before we add a new entry, check to make sure we have space
    				if(numUniqueWords==capacity)
    				{
    					//Resize
    					numDoublings++;
    					capacity*=2;
    					wordItem* newarray;
						newarray=new wordItem[capacity];
						for(int i=0;i<numUniqueWords;i++)
						{
							newarray[i]=uniquewords[i];
						}
						delete [] uniquewords;
						uniquewords=newarray;
   	 				}
    				uniquewords[numUniqueWords].word=word;
    				uniquewords[numUniqueWords].count=1;
    				numUniqueWords++;
    			}	
    		}
    	}
    }
    arraySort(uniquewords, numUniqueWords);
    printTopN(uniquewords, topN);
    cout<<"#"<<endl;
    cout<<"Array doubled: "<< numDoublings<<endl;
    cout<<"#"<<endl;
    cout<<"Unique non-stop words: "<<numUniqueWords<<endl;
    cout<<"#"<<endl;
    cout<<"Total non-stop words: ";
    cout<<getTotalNumberNonStopWords(uniquewords, numUniqueWords)<<endl;
 	return 0;

}


void getStopWords(const char *ignoreWordFileName, vector<string> &_vecIgnoreWords)
{
	int i=0;
	string input;
	ifstream inFile(ignoreWordFileName);
	while(getline(inFile, input)) // This loop reads 1 line, stores that into input, and then input gets stored in the vector
	{
		stringstream ss(input);
		_vecIgnoreWords[i]=input;
		i++;
	}
  
}
 
bool isStopWord(string word, vector<string> &_vecIgnoreWords)
{
	for(int i=0; i<STOPWORD_LIST_SIZE; i++)
	{
		if(word==_vecIgnoreWords[i])
		{
			return true;
		}
	}
	return false;
}
 
int getTotalNumberNonStopWords(wordItem list[], int length)
{
	int words=0;
	for(int i=0; i<length; i++)
	{
		words= words+list[i].count;
	}
    return words;
}
 
void arraySort(wordItem list[], int length)
{
	int currentmax;
	int i, j;
	wordItem temp;
	int index;
	for(i=0; i<length-1; i++)
	{
		index=i;
		currentmax=list[i].count;
		for(j=i; j<length; j++)
		{
			if(list[j].count>currentmax)
			{
				currentmax=list[j].count;
				index=j;
			}
		}
		temp=list[i];
		list[i]=list[index];
		list[index]=temp;
	}
}
 
void printTopN(wordItem wordItemList[], int topN)
{
	for(int i=0; i<topN; i++)
	{
		cout<<wordItemList[i].count<<" - "<<wordItemList[i].word<<endl;
	}
}

