/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "DisplayCommand.h"
#include "ReadFileVisitor.h"
#include<sstream>
#include<iostream>

using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

// removes a file from the current working directory
int DisplayCommand::execute(std::string& CWD, std::string options) {
	istringstream iss(options);
	string fileName, flag;
	if (!(iss >> fileName)) {
		cout << "file does not exist" << endl;
		return filedoesnotexist;
	}

	AbstractFile* f = fs->openFile(CWD + "/" + fileName);
	if (f == nullptr) {
		cout << "file does not exist or is open" << endl;
		return filedoesnotexist;
	}

	if (iss >> options && options == "-d") {
		vector<char> contents = f->read();
		for (size_t i = 0; i < contents.size(); ++i) {
			cout << contents[i];
		}
		cout << endl;
	}
	else {
		ReadFileVisitor reader;
		f->accept(&reader);
	}
	
	fs->closeFile(f);
	return success;
}

void DisplayCommand::displayInfo() {
	cout << "display opens a file and displays its contents, either formatted or not" << endl;
	cout << "Usage: ds <filename> [-d]" << endl;
}