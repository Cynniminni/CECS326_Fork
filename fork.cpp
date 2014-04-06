#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int searchText(ifstream & file, string input);

int main() {

	//Initialize
	string input = "";
	ifstream file ("text.txt");
	int result = 0;

	//Prompt user
	cout << "Input is case-sensitive. Enter \'!wq\' to exit." << endl;
	cout << "Please enter string to search:" << endl;
	cin >> input;

	//While user hasn't terminated the program
	while (input != "!wq") {
		//Search text file
		result = searchText(file, input);
		cout << "\n\"" << input << "\" occurs " << result << " times." << endl;

		cout << "\nInput is case-sensitive. Enter \'!wq\' to exit." << endl;
		cout << "Please enter string to search:" << endl;
		cin >> input;	
	}

	//Close file when done
	file.close();
	
	return 0;
}

int searchText(ifstream & file, string input) {
	size_t pos;//position of string to search
	string currentLine;
	int counter = 0;

	if (file.is_open()) {
		file.clear();//clear endoffile flag
		file.seekg(0, file.beg);//reset cursor to beginning of 

		while (getline(file, currentLine)) {//while file still has lines to read
			pos = currentLine.find(input, 0);//search current line at index 0

			//while pos is not the end of the line AND search is successful
			while (pos != currentLine.size() && pos != string::npos) {
				counter++;//count the occurrence
				pos = currentLine.find(input, pos + 1);//continue searching
			}
		}
	}

	return counter;//return number of input occurences
}

/*
	Pseudocode

	Start

	Initialize
		string input = "";
		long childPID;

	Read text file
		ifstream text;
		
	Prompt user
		Enter string
		Save as input

	While input is not terminating program...
	While (input != "!wq") {
		Spawn child process
			childPID = fork();

		Child process searches document
			if (childPID == 0) {
				searchText(text, input);
			} 

		Exit if fork() was unsuccessful
			else if (childPID < 0) {
				cout << "Failed to work. Exiting..." << endl;
				exit(1);
			} 
	}

	Exit program
		exit(0);


	Method: int searchText(ifstream text, string input) 
		text.open("text.txt");
		size_t pos;
		string currentLine;
		int counter = 0;

		while (!text.eof) {//search each line
			getline(text, currentLine);//save each line as string
			pos = line.find(input);//search line for the input

			if (pos != string::npos) {//if input found
				counter++;//count it
			}
		}

		text.close();
		return counter;//return number of input occurences


	End


*/
