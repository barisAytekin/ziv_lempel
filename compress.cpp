#include "htable.h"
#include <fstream>
#include <sstream>
using namespace std;
struct Pair { //pair struct containing text-code pairs
	string text;
	int code;
	Pair(string a, int b)
		: text(a), code(b) {}
	Pair() {}
	bool operator==(const Pair& a) const
	{
		return text == a.text;
	}
	bool operator!=(const Pair& a) const
	{
		return text != a.text;
	}
};
int Hash(Pair key, int size) //hash function
{
	int sum = 0;
	for (int i = 0; i < key.text.length(); i++) {
		sum += (unsigned char)key.text[i];
	}
	return sum % size;
}
int main()
{
	
	Pair nfound("", -1);
	HashTable<Pair> table(nfound, 4096);
	char ch;
	for (int i = 0; i < 256; i++) { //insert the ascii characters
		ch = i;
		string s{ ch };
		Pair temp(s, i);
		table.insert(temp);
	}
	string infile = "compin.txt";
	string outfile = "compout.txt";
	ifstream t;
	ofstream o;
	t.open(infile.c_str());
	o.open(outfile.c_str());
	stringstream read;
	read << t.rdbuf(); // read the whole file
	string content = read.str();
	int counter = 0;
	int codenum = 256;
	string temp = content;
	while (true) {
		Pair foo(temp, -1);
		int num = table.find(foo).code; // try to find the code of the string
		if (num != -1) { // if found
			o << num << " "; //write the code
			if (content == temp) {
				break;
			}
			content = content.substr(temp.length(), content.length() - temp.length()); //truncate the found part and update the base string
			counter = 0;
			Pair bar(temp + content[0], codenum);
			table.insert(bar); //continue inserting text-code pairs if the compression has not yet been finished
			codenum++;
			temp = content; //update the temp container
		}
		else {
			temp = content.substr(0, content.length() - counter - 1); //if not found at every iteration truncate the string from the rhs
			counter++; //increment the counter
		}
	}
	t.close(); //close the streams
	o.close();
	return 0;
}