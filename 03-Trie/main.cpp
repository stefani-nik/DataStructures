/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include "MyTrie.h"

using namespace std;

//Transforming word to lower case method
string wordToLower(string word) {
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	return word;
}

int main(int argc, char * argv[])
{
	Trie wordTrie;

	//Reading the input file
	ifstream inputFile(argv[1]);
	string str;

	// Reading each line of the file 
	while (getline(inputFile, str))
	{
		vector<string> currentPhrase;
		string currentLine = str;
		istringstream iss(currentLine);

		//Reading each word of every line
		while (iss) {
			string word;
			iss >> word;
			if (word != "")
				currentPhrase.push_back(word);
		}

		//Take the value of the phrase
		int value = stoi(currentPhrase[currentPhrase.size() - 1]);

		//Adding the phrase to the tree
		for (int i = 0; i < currentPhrase.size() - 1; i++)
		{
			if (!wordTrie.searchWord(currentPhrase[i]))
			{
				if (i == currentPhrase.size() - 2)
				{
					wordTrie.addWord(wordToLower(currentPhrase[i]), value, currentPhrase.size() - 1);
				}
				else
				{
					wordTrie.addWord(wordToLower(currentPhrase[i]), 0, 0);
				}
			}
		}
	}

	// Reading all the passed files
	for (int i = 2; i < argc; i++)
	{
		//Initializing some variables 
		double result = 0;
		int cnt = 0;
		int phraseLength = 1;
		double weight = 0;

		string currentLine;
		ifstream textFile;
		textFile.open(argv[i]);

		string word;

		// Reading between white spaces
		while (textFile >> word)
		{
			regex rgx("[A-Za-z]+");

			//Matching words with the regex
			for (sregex_iterator it(word.begin(), word.end(), rgx), it_end; it != it_end; ++it)
			{
				cnt++;
				string currentWord = wordToLower((*it)[0]);

				//Fat but still not completely working logic about the searching
				if (wordTrie.searchWord(currentWord))
				{

					if (wordTrie.getPhraseLength(currentWord) == phraseLength)
					{
						weight += wordTrie.getWordWeight(currentWord);
						phraseLength = 1;
					}

					else if (wordTrie.getPhraseLength(currentWord) != 0)
					{
						phraseLength = 1;
					}
					else
					{
						phraseLength++;
					}
				}
				else
				{
					phraseLength = 1;
				}
			}
		}
		if (weight != 0)
			result = weight / cnt;

		cout << argv[i] << " " << result << endl;
	}

	return 0;
}

