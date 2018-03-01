/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/

#include <iostream>
#include <vector>

using namespace std;

class Word {
public:
	Word() { _symbol = ' '; _value = NULL; _length = NULL; _last = false; }
	~Word() {}
	char content() { return _symbol; }
	void setContent(char c) { _symbol = c; }
	bool getLast() { return _last; }
	void setLast() { _last = true; }
	Word* findChild(char c);
	void setValue(double value) { _value = value;  }
	int getValue() { return _value; }
	void setLength(double length) { _length = length; }
	int getLength() { return _length; }
	void appendChild(Word* child) { _children.push_back(child); }
	vector<Word*> children() { return _children; }

private:
	char _symbol;
	bool _last;
	double _value;
	int _length;
	vector<Word*> _children;
};

class Trie {
public:
	Trie();
	~Trie();
	void addWord(string s, double value, int legth);
	bool searchWord(string s);
	int getWordWeight(string word);
	int getPhraseLength(string word);
private:
	Word* root;
};

Word* Word::findChild(char ch)
{
	for (int i = 0; i < _children.size(); i++)
	{
		Word* temp = _children.at(i);
		if (temp->content() == ch)
		{
			return temp;
		}
	}

	return NULL;
}

Trie::Trie()
{
	root = new Word();
}

Trie::~Trie()
{
	delete root;
}

void Trie::addWord(string str, double value, int lenght)
{
	Word* current = root;

	if (str.length() == 0)
	{
		current->setLast(); // an empty word
		return;
	}

	for (int i = 0; i < str.length(); i++)
	{
		Word* child = current->findChild(str[i]);
		if (child != NULL)
		{
			current = child;
		}
		else
		{
			Word* temp = new Word();
			temp->setContent(str[i]);
			current->appendChild(temp);
			current = temp;
		}
		if (i == str.length() - 1)
		{
			current->setLast();
			current->setValue(value);
			current->setLength(lenght);
		}
	}
}


bool Trie::searchWord(string str)
{
	Word* current = root;

	while (current != NULL)
	{
		for (int i = 0; i < str.length(); i++)
		{
			Word* temp = current->findChild(str[i]);
			if (temp == NULL)
				return false;
			current = temp;
		}

		if (current->getLast())
			return true;
		else
			return false;
	}

	return false;
}
int Trie::getWordWeight(string word)
{
	if (this->searchWord(word))
	{
		Word* current = root;

		for (int i = 0; i < word.length(); i++)
		{
			Word* child = current->findChild(word[i]);

			if (child != NULL)
			{
				current = child;
			}
			else
			{
				return 0;
			}
		}

		return current->getValue();
	}

	return 0;
}
int Trie::getPhraseLength(string word)
{
	//TODO: Check if it is necessary
	if (this->searchWord(word))
	{
		Word* current = root;

		for (int i = 0; i < word.length(); i++)
		{
			Word* child = current->findChild(word[i]);

			if (child != NULL)
			{
				current = child;
			}
			else
			{
				return 0;
			}
		}

		return current->getLength();
	}

	return 0;
}