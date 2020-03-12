/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "SymCommand.h"
#include "ProxyFile.h"
#include<iostream>
#include<sstream>


using namespace std;

SymCommand::SymCommand(AbstractFileSystem* fileSys) :
	 fs(fileSys) { }
int SymCommand::execute(std::string& CWD, std::string options) {
	string filePath,copyPath;
	istringstream iss(options);
	//check if they are valid file path and cophy path
	if (!(iss >> filePath)) {
		cout << "Command error, please check usage of sym" << endl;
		return CWDdoesnotexist;
	}
	if (!(iss >> copyPath)) {
		cout << "Command error, please check usage of sym" << endl;
		return CWDdoesnotexist;
	}

	if (filePath.find_last_of('.') == string::npos) {
		cout << filePath+" is not supposed tobe a directory, please check usage of sym" << endl;
		return CWDdoesnotexist;
	}

	if (copyPath.find_last_of('.') != string::npos) {
		cout << copyPath + " is not supposed tobe a file, please check usage of sym" << endl;
		return CWDdoesnotexist;
	}
	AbstractFile* f = fs->openFile(CWD +'/'+ filePath);
	if (f == nullptr) { // file not found
		cout << "file does not exist" << endl;
		return filedoesnotexist;
	}
	ProxyFile* proxy;
	int result;
	//check if the sym target is already a proxy. If so just create one out of it. If not, use a clone of the object to create 2 links.
	if (ProxyFile* pf= dynamic_cast<ProxyFile*>(f)) {
		proxy = new ProxyFile(pf);
		fs->closeFile(f);
	}
	else {
		AbstractFile* clone = f->clone();
		fs->closeFile(f);
		if (clone == nullptr) { // file not found
			cout << "clone failed" << endl;
			delete clone;
			return clonefailed;
		}

		result = fs->deleteFile(CWD + '/' + filePath);
		if (result == AbstractFileSystem::fileisopen) {
			cout << "File is currently in use" << endl;
			delete clone;
			return fileinuse;
		}
		ProxyFile* first = new ProxyFile(clone);
		result = fs->addFile(CWD + '/', first);
		if (result != success) {
			result = fs->addFile(CWD + '/', clone);
			cout << "failed to add proxy to file system, recovering file" << endl;
			delete first;
			return failedtoadd;
		}
		proxy = new ProxyFile(first);

	}
	result = fs->addFile(copyPath + '/', proxy);
	if (result != success) {
		cout << result << endl;
		cout << "failed to add proxy to file system, deleting proxy" << endl;
		delete proxy;
		return failedtoadd;
	}
	return result;
}
void SymCommand::displayInfo() {
	cout << "sym makes symbolic links" << endl;
	cout << "sym <file_to_copy> <full_path_to_destination>" << endl;
}