#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
int findnext(string Array[4096]) {
	for (int i = 0; i < 4096; i++) { //find the next empty slot
		if (Array[i] == "") {
			return i;
		}
	}
}
int main()
{
	string arr[4096]; //initialize the array
	char ch;
	for (int i = 0; i < 4096; i++) { 
		if (i < 256) { //add the ascii characters
			ch = i;
			string s{ ch };
			arr[i] = s;
		}
		else {
			arr[i] = ""; //fill with empty string for the rest
		}

	}
	string infile = "compout.txt";
	string outfile = "decompout.txt";
	ifstream read;
	ofstream write;
	read.open(infile.c_str());
	write.open(outfile.c_str());
	int code;
	int prev = -1; //previous code
	while (read >> code) {
		if (prev == -1) { //for the first code
			write << arr[code]; //find the text pair and write it to the file
			prev = code;

		}
		else if (arr[code] != "") {//if the code has a text pair
			write << arr[code]; //write the text
			arr[findnext(arr)] = arr[prev] + arr[code][0]; //add teh new text with this rule
			prev = code;
		}
		else { //if the code does not have a text pair
			arr[code] = arr[prev] + arr[prev][0]; //insert the text pair with this rule
			write << arr[code]; //write the text
			prev = code;

		}
	}
	read.close();
	write.close();
	return 0;
}