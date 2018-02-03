#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream myfile;
	char c;
	myfile.open("d:\\original_file.txt");
	if (!myfile)
	{
		cerr << "Open original_file.txt failed!!";
		exit(1);
	}
	while (!myfile.eof())
	{
		myfile >> c;
		cout << c;
	}
	myfile.close();
	//for (int i = 0, j = 0; i > 200; i++, j--){ char c = i; cout << c << " "; }
}