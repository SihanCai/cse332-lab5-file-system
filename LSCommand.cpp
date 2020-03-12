/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "LSCommand.h"
#include "ReadFileVisitor.h"
#include "ReadMetadataFileVisitor.h"
#include<iostream>

using namespace std;

LSCommand::LSCommand(AbstractFileSystem * fileSys) : fs(fileSys) {}

int LSCommand::execute(std::string& CWD, std::string options) {
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}

	ReadFileVisitor reader;
	ReadMetadataFileVisitor readerMeta;
	if (options == "-l") {
		vector<char> contents = f->read();
		string fileName = "";
		for (size_t i = 0; i < contents.size(); ++i) {
			if (contents[i] == '\n') {
				AbstractFile* fileInDir = fs->openFile(CWD + '/' + fileName);
				if (fileInDir == nullptr) {
					cout << fileName << " cannot be inspected!" << endl;
					fileName = "";
					continue;
				}
				fileInDir->accept(&readerMeta);
				fs->closeFile(fileInDir);
				fileName = "";		
				continue;
			}
			fileName += contents[i];
		}
	}
	else {
		f->accept(&reader);
	}
	fs->closeFile(f);
	return success;
}
void LSCommand::displayInfo() {
	cout << "lists the contents of the current directory" << endl;
	cout << "Usage: ls [-l]" << endl;
}