/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "CPCommand.h"
#include<iostream>
#include<sstream>


using namespace std;

CPCommand::CPCommand(AbstractFileSystem* fileSys) :
	 fs(fileSys) { }

int CPCommand::execute(std::string& CWD, std::string options) {
	string filePath,copyPath;
	istringstream iss(options);
	//check if they are valid file path and cophy path
	if (!(iss >> filePath)) {
		cout << "Command error, please check usage of cp" << endl;
		return CWDdoesnotexist;
	}
	if (!(iss >> copyPath)) {
		cout << "Command error, please check usage of cp" << endl;
		return CWDdoesnotexist;
	}

	if (filePath.find_last_of('.') == string::npos) {
		cout << filePath+" is not supposed tobe a directory, please check usage of cp" << endl;
		return CWDdoesnotexist;
	}

	if (copyPath.find_last_of('.') != string::npos) {
		cout << copyPath + " is not supposed tobe a file, please check usage of cp" << endl;
		return CWDdoesnotexist;
	}
	AbstractFile* f = fs->openFile(CWD +'/'+ filePath);
	if (f == nullptr) { // file not found
		cout << "file does not exist" << endl;
		return filedoesnotexist;
	}
	AbstractFile* clone = f->clone();
	fs->closeFile(f);

	if (clone == nullptr) { // file not found
		cout << "clone failed" << endl;
		delete clone;
		return clonefailed;
	}
	//add the clone
	int result = fs->addFile(copyPath + '/', clone);
	if (result != success) {
		cout << "failed to add file to file system, deleting file" << endl;
		delete clone;
		return failedtoadd;
	}
	return result;
}
void CPCommand::displayInfo() {
	cout << "Copy makes a copy of an existing file and stores it somewhere else in the file system" << endl;
	cout << "cp <file_to_copy> <full_path_to_destination>" << endl;
}