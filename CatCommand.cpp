/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "CatCommand.h"
#include "ReadFileVisitor.h"
#include<sstream>
#include<iostream>

using namespace std;

CatCommand::CatCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

// removes a file from the current working directory
int CatCommand::execute(std::string& CWD, std::string options) {
	istringstream iss(options);
	string fileName, flag;
	if (!(iss >> fileName)) {
		cout << "file does not exist" << endl;
		return filedoesnotexist;
	}

	AbstractFile* f = fs->openFile(CWD + "/" + fileName);
	if (f == nullptr) {
		cout << "file does not exist" << endl;
		return filedoesnotexist;
	}

	if (iss >> options && options == "-a") {
		ReadFileVisitor reader;
		f->accept(&reader);
		string inputLine;
		vector<char> allInput;
		bool isFirstLine = true;
		while (getline(cin, inputLine)) {
			if (inputLine == ":wq") {
				f->append(allInput);
				break;
			}
			else if (inputLine == ":q") {
				break;
			}
			else {
				if (isFirstLine)
					isFirstLine = false;
				else
					inputLine = "\n" + inputLine;
				copy(inputLine.begin(), inputLine.end(), back_inserter(allInput));
			}
		}

	}
	else {
		string inputLine;
		vector<char> allInput;
		bool isFirstLine = true;
		while (getline(cin, inputLine)) {
			if (inputLine == ":wq") {
				f->write(allInput);
				break;
			}
			else if (inputLine == ":q") {
				break;
			}
			else {
				if (isFirstLine)
					isFirstLine = false;
				else
					inputLine = "\n" + inputLine;
				copy(inputLine.begin(), inputLine.end(), back_inserter(allInput));
			}
		}
		
	}

	fs->closeFile(f);
	return 0;
	
}

void CatCommand::displayInfo() {
	cout << "writes or appends to a file" << endl;
	cout << "Usage: cat <filename> [-a]" << endl;
}