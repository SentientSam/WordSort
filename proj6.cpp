// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 6                                *
// * Filename: proj6.cpp                                     *
// * Date Created: 4/21/2020                                 *
// * References: cda 3101 (map/multimap usage), cplusplus    *
// *                                                         *
// * Description: Takes an input file and sorts it,          *
// * giving you frequency of numbers, words, and characters. *
// *                                                         *
// *                                                         *
// ***********************************************************

#include <iomanip>
#include <iostream>
#include <map>
#include <cctype>
#include <ctime>
#include <vector>
#include <string>
#include <cstring>
using namespace std;  
void printCharacter(multimap<int, char> & mMap);
void printWord(multimap<int, string> & mMap);
void printNumber(multimap<int, string> & mMap);

int main()
{
	//
	// Clock for execution time
	//

	clock_t t;
	t = clock();
	////////////////////////////////////////////////////////
	// Making a map for each thing that I am checking for //
	// Also an additonal map for the order they appear    //
	//                                                    //
	//                                                    // 
	////////////////////////////////////////////////////////
	map<char, int> cMap; 
	map<string, int> wMap;
	map<string, int> nMap;
	map<string, char> wInsertPoint;
	map<string, char> nInsertPoint;
	char charCount;
	char currChar;
	char addOn;
	char wordCount = 65;
	char numberCount= 65;
	bool alpha = false;
	multimap<int, char> characterMMap;
	multimap<int, string> wordMMap;
	multimap<int, string> numberMMap;
	string character = "";
	//
	// While we have not reached the end of the input file, the code will loop //
	//

  do
  {
		cin.get(currChar);
		addOn = cin.peek(); 
		//
		// Adding Characters (everything is a character)
		//
		++cMap[currChar];

		//
		// Checking for words
		//
		//
		// If isalpha(currChar), current characters gets stored as lowercase version and added to the stack
		//

		if(isalpha(currChar))
    {
			alpha = true;
      currChar = tolower(currChar);
      character += currChar;
    }
		//
		// If next character is not alphanumerical (space, newline, etc) then add the character to the stack
		// 
		//
		if (!isalpha(addOn) && isalpha(currChar))
		{
			if(alpha)
			{
				//
				// Odd unknown issue I figured was worth mentioning. When I initially wrote this I had character += wordCount
				// That adds extra outputs behind some of the words in my sort, so I have to do character = wordCount + character
				// 
				if (wInsertPoint.find(character) == wInsertPoint.end())
				{
					wInsertPoint.emplace(character,wordCount);
					character = wordCount + character;
					wordCount += 1;
				}
				else
				{
					auto itr = wInsertPoint.find(character);
					charCount = itr -> second;
					character = charCount + character;
				}
				++wMap[character];
			}
			character.clear();
			alpha = false;
		}
		
		//
		// Checking for numbers
		// If number and next character is a number just loop it
		// 

		if (isdigit(currChar))
		{
			if (isdigit(addOn))
			{
				character += currChar;
			}
			else
			{
				character += currChar;
				if (nInsertPoint.find(character) == nInsertPoint.end())
				{
					nInsertPoint.emplace(character,numberCount);
					character = numberCount + character;
					numberCount += 1;
				}
				else
				{
					auto itr = nInsertPoint.find(character);
					charCount = itr -> second;
					character = charCount + character;
				}
				++nMap[character];
				character.clear();
			}
		}
  } while(!cin.eof());

	//
	// inserting the map characters into a multimap, makes sorting easier by reverse iterating
	//

	for(map<char,int>::reverse_iterator itr = cMap.rbegin(); itr != cMap.rend(); ++itr)
	{
		characterMMap.insert(pair<int,char>(itr -> second,itr -> first));
	}

	for(map<string,int>::reverse_iterator itr = wMap.rbegin(); itr != wMap.rend(); ++itr)
	{
		wordMMap.insert(pair<int,string>(itr -> second,itr -> first));
	}

	for(map<string,int>::reverse_iterator itr = nMap.rbegin(); itr != nMap.rend(); ++itr)
	{
		numberMMap.insert(pair<int,string>(itr -> second,itr -> first));
	}
	
	//
	// print functions
	//

	printWord(wordMMap);
	printNumber(numberMMap);
	printCharacter(characterMMap);
	t = clock() - t;
	cout << "Execution time: " << ((double)t / CLOCKS_PER_SEC) << " Seconds" << endl;
	return 0;
}



void printCharacter(multimap<int, char> & mMap)
{
	int top = 10;
	int index = 0;
	if (mMap.size() <= 10)
	{
		top = mMap.size();
	}
	cout << "There are " << mMap.size() << " Unique Characters, The Top " << top << " Characters\n";
	cout << left << "Index" << internal << setw(10) <<  "Item" << setw(10) << "Number" << endl;
	cout << left << "-----" << internal << setw(10) <<  "----" << setw(10) << "------" << endl;
	for (multimap<int,char>::reverse_iterator itr = mMap.rbegin(); itr != mMap.rend(); ++ itr)
	{
		if (index < 10)
		{
			cout << "[ " << index << "]       ";
		}
		else
		{
			cout << "[" << index << "]       ";
		}
		++index;
		if (itr -> second == '\n')
		{
			cout << left << setw(8) << "Newline" << itr -> first << endl;
		}
		else if (itr -> second == '\t')
		{
			cout << left << setw(8) << "Tab" << itr -> first << endl;
		}
		else if (itr -> second == ' ')
		{
			cout << left << setw(8) << "Blank" << itr -> first << endl;
		}
		else
		{
			cout << left << setw(8) << itr -> second << itr -> first << endl;
		}
		if (index == 10)
		{
			break;
		}
	}
}
void printWord(multimap<int, string> & mMap)
{
	int top = 10;
	int index = 0;
	if (mMap.size() <= 10)
	{
		top = mMap.size();
	}
	cout << "There are " << mMap.size() << " Unique Words, The Top " << top <<" Words\n";
	cout << left << "Index" << internal << setw(11) <<  "Item" << setw(20) << "Number" << endl;
	cout << left << "-----" << internal << setw(11) <<  "----" << setw(20) << "------" << endl;
	for (multimap<int,string>::reverse_iterator itr = mMap.rbegin(); itr != mMap.rend(); ++ itr)
	{
		itr -> second.front() = 0;
		if (index < 10)
		{
			cout << "[ " << index << "]       ";
		}
		else
		{
			cout << "[" << index << "]       ";
		}
		++index;
		cout << left << setw(19) << itr -> second << itr -> first << endl;
		if (index == 10)
		{
			break;
		}
	}
}
void printNumber(multimap<int, string> & mMap)
{
	int top = 10;
	int index = 0;
	if (mMap.size() <= 10)
	{
		top = mMap.size();
	}
	cout << "There are " << mMap.size() << " Unique Numbers, The Top " << top << " Numbers\n";
	cout << left << "Index" << internal << setw(11) <<  "Item" << setw(10) << "Number" << endl;
	cout << left << "-----" << internal << setw(11) <<  "----" << setw(10) << "------" << endl;
	for (multimap<int,string>::reverse_iterator itr = mMap.rbegin(); itr != mMap.rend(); ++ itr)
	{
		itr -> second.front() = 0;
		if (index < 10)
		{
			cout << "[ " << index << "]       ";
		}
		else
		{
			cout << "[" << index << "]       ";
		}
		++index;
		cout << left << setw(9) << itr -> second << itr -> first << endl;
		if (index == 10)
		{
			break;
		}
	}
}
