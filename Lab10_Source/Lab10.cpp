#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class StudentInfo {
private:
	string name;
	StudentInfo* nextStudentPtr;
public:
	StudentInfo(string value, StudentInfo* nextItem);
	string getName();
	StudentInfo* getNextStudent();
	void setNextStudent(StudentInfo* item);
};

int main() {

	// Declare any extra variables needed

	ifstream fin("input1.txt");
	
	if (!fin.is_open())
	{
		cout << "Could not open the input file input1.txt" << endl;
		return -1;
	}
	
	while (!fin.eof())
	{
		string item, command;
		fin >> item >> command;

		// Logic of handling the input.

	}
	fin.close();

	// Output the final linked list.

	// Free up all memory.

}