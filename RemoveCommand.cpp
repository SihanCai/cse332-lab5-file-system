/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "RemoveCommand.h"
#include "DeleteFileVisitor.h"
#include<iostream>
#include<sstream>

using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

// removes a file from the current working directory
int RemoveCommand::execute(std::string& CWD, std::string options) {
	istringstream iss(options);
	string fileName, flag;
	string fullPath = CWD;
	fullPath += '/';
	if (!(iss >> fileName)) {
		cout << "file does not exist" << endl;
		return filedoesnotexist;
	}
	fullPath += fileName;
	int result = fs->deleteFile(fullPath);
	if (result == AbstractFileSystem::filedoesnotexist) {
		cout << "File does not exist" << endl;
		return filedoesnotexist;
	}
	else if (result == AbstractFileSystem::fileisopen) {
		cout << "File is currently in use" << endl;
		return fileinuse;
	}
	else if (result == AbstractFileSystem::directorynotempty) {
		if ((iss >> flag) && flag == "-r") {
			DeleteFileVisitor dVisitor(fs, fullPath);
			AbstractFile* fileInDir = fs->openFile(fullPath);
			fileInDir->accept(&dVisitor);
			fs->closeFile(fileInDir);
			int status = fs->deleteFile(fullPath);
			if (status == AbstractFileSystem::directorynotempty) {
				cout << "Directory is not empty" << endl;
				return directorynotempty;
			}
		}
		else {
			cout << "Directory is not empty" << endl;
			return directorynotempty;
		}
	}
	return success;
}
void RemoveCommand::displayInfo() {
	cout << "touch removes a file from the file system and then deletes the file" << endl;
	cout << "Usage: rm <filename> [-r]" << endl;
}