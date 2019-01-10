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
	string getName() { return name; };
	StudentInfo* getNextStudent() { return nextStudentPtr; };
	void setNextStudent(StudentInfo* item);
	void deleteNext();
	void insertAfter(StudentInfo* item);
	friend bool operator== (const StudentInfo &s1, const StudentInfo &s2);
	friend bool operator< (const StudentInfo &s1, const StudentInfo &s2);

};

StudentInfo::StudentInfo(string value, StudentInfo* nextItem = nullptr) {
	this->name = value;
	this->nextStudentPtr = nextItem;
}

bool operator== (const StudentInfo &s1, const StudentInfo &s2) {
	return (s1.name == s2.name);
}

bool operator< (const StudentInfo &s1, const StudentInfo &s2) {
	return (s1.name < s2.name);
}

void StudentInfo::setNextStudent(StudentInfo* item) {
	this->nextStudentPtr = item;
}

void StudentInfo::deleteNext() {
	StudentInfo* temp = this->getNextStudent()->getNextStudent();
	delete this->getNextStudent();
	this->nextStudentPtr = temp;
}

void StudentInfo::insertAfter(StudentInfo* item) {
	StudentInfo* temp = this->getNextStudent();
	this->nextStudentPtr = item;
	item->setNextStudent(temp);
}


int main() {

	ifstream fin("input7.txt");
	if (!fin.is_open())
	{
		cout << "Could not open the input file input.txt" << endl;
		return -1;
	}
	StudentInfo* headItem = nullptr;
	while (!fin.eof())
	{
		string item, command;
		fin >> item >> command;

		// If the command is to add the item from the file, do so.
		if (command == "add")
		{
			StudentInfo* addItem = new StudentInfo(item);
			if (headItem == nullptr)		// If this is the first thing we read, make it the headItem
			{
				headItem = addItem;
			}
			else
			{
				if (addItem < headItem )  // If this is before the head item, then add that item and make add item the headitem
				{
					// Insert the headitem after our added item and make the added item the new item.
					addItem->setNextStudent(headItem);
					headItem = addItem;
				}
				StudentInfo* currentItem = headItem;
				while (currentItem != nullptr)
				{
					// If current Item is the last one, then the add Item must come after it.
					// If the item following is larger then we need to insert our item before it.
					if (currentItem->getNextStudent() == nullptr || addItem->getName() < currentItem->getNextStudent()->getName())
					{
						currentItem->insertAfter(addItem);
						break;
					}
					currentItem = currentItem->getNextStudent();
				}
			}
		}
		else if (command == "del")
		{
			StudentInfo* delItem = new StudentInfo(item);
			if (delItem == headItem)
			{
				StudentInfo* tempItem = headItem;
				headItem = headItem->getNextStudent();
				delete tempItem;
			}
			else
			{
				StudentInfo* currentItem = headItem;
				while (currentItem != nullptr)
				{
					if (currentItem->getNextStudent() == delItem)
					{
						currentItem->deleteNext();
						break;
					}
					currentItem = currentItem->getNextStudent();
				}
			}
		}
	}
	fin.close();

	// Show all the Items from headobj to the bottom
	StudentInfo* currentItem = headItem;
	while (currentItem != nullptr)
	{
		cout << "->" << currentItem->getName();
		currentItem = currentItem->getNextStudent();
	}
	cout << endl;

	// Remove all of the items and free the memory
	currentItem = headItem;
	while (currentItem != nullptr)
	{
		StudentInfo* temp = currentItem->getNextStudent();
		delete currentItem;
		currentItem = temp;
	}

	StudentInfo* headPtr = new StudentInfo("Alice");
	StudentInfo* temp = new StudentInfo("Bob");
	headPtr->setNextStudent(temp);

	return 0;
}