//vmangs
//9-26-2018
//updated 10-14-2018
//Markov Chain

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

//functions
void fileIntoWordList(string s);
string worldListIntoTweet(int i);

//the map of each word of the txt file
map<string, vector<string> > wordlist;

int main(int argc, char* argv[]) {

	srand(time(NULL));

	if (argc > 1) {
		fileIntoWordList(string(argv[1]));
		cout << worldListIntoTweet(280) << endl;
	}
	else
		cout << "No input file stated. Make sure you put the filename.txt as an argument." << endl;

	return 0;
}

//converts a txt file into the string vector map
void fileIntoWordList(string filename) {
	ifstream fileinput;
	fileinput.open(filename.c_str());
	string firstword, secondword;

	if (fileinput >> firstword) {
		while (fileinput >> secondword) {
			wordlist[firstword].push_back(secondword);
			firstword = secondword;
		}
	}
}


//returns a string that does not exceed the max length
string worldListIntoTweet(int max) {
	//Initialize output tweet
	string tweetOutput = "";

	//create iterator
	std::map<string, vector<string> >::iterator it = wordlist.begin();

	//select random word to start the tweet with
	advance(it, rand() % wordlist.size());
	tweetOutput += it->first;
	string firststring = it->first;

	//set up the next two words to look at
	firststring = wordlist[firststring].at(rand() % wordlist[firststring].size());
	string secondstring = wordlist[firststring].at(rand() % wordlist[firststring].size());

	//add words to the final tweet unless it exceeds the tweet max length
	while (tweetOutput.size() + secondstring.size() <= max) {
		tweetOutput += " ";
		tweetOutput += firststring;
		firststring = secondstring;
		secondstring = wordlist[firststring].at(rand() % wordlist[firststring].size());
	}

	return tweetOutput;
}