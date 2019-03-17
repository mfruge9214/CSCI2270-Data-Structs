#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.hpp"

using namespace std;

void getUniqueWords(char *textfilename, HashTable &uniqueTable, HashTable &ignoreTable)
{
	string word;
	bool ignore, inTable;
	ifstream inFile;
	inFile.open(textfilename);
	while(inFile>>word)
	{
		//if(word=='\n') break;
		ignore=isStopWord(word, ignoreTable);
		if(!ignore) // If the word just read is not a stopword
		{
			inTable=uniqueTable.isInTable(word);
			if(!inTable)
			{
				uniqueTable.addWord(word);
			}
			else
			{
				uniqueTable.incrementCount(word);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 5)
    {
        cout << "Usage: ";
        cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt> <size of unique words table>";
        cout << endl;
        return 0;
    }
    // Parse the number of stopwords
    int topN=stoi(argv[1]);
    int uniqueWordsSize=stoi(argv[4]);
    HashTable stopwords(50);
    HashTable uniqueWordsTable(uniqueWordsSize);
    getStopWords(argv[3], stopwords);
    cout<<"Stop Words Gotten"<<endl;
    getUniqueWords(argv[2], uniqueWordsTable, stopwords);
    cout<<"Unique Words Gotten"<<endl;
    uniqueWordsTable.printTopN(topN);
    cout<<"#"<<endl;
    cout<<"Number of collisions: "<< uniqueWordsTable.getNumCollisions()<<endl;
    cout<<"#"<<endl;
    cout<<"Unique non-stop words: "<< uniqueWordsTable.getNumItems()<<endl;
    cout<<"#"<<endl;
    cout<<"Total non-stop words: "<< uniqueWordsTable.getTotalNumWords()<<endl;
	return 0;
}