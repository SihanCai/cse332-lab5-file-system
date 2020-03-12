#include "DeleteFileVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "DirectoryFile.h"
#include<iostream>
#include<vector>
using namespace std;

DeleteFileVisitor::DeleteFileVisitor(AbstractFileSystem* fileSys, string cwd): fs(fileSys), CWD(cwd) {}

void DeleteFileVisitor::visit(TextFile* file) {
	/*string fullPath = CWD + '/' + file->getName();
	cout << CWD << "lol" << endl;*/
	//fs->deleteFile(CWD);

}

void DeleteFileVisitor::visit(ImageFile* file) {
	/*string fullPath = CWD + '/' + file->getName();
	cout << CWD << "lol" << endl;*/
	//fs->deleteFile(CWD);
	
}

void DeleteFileVisitor::visit(DirectoryFile* file) {
	vector<char> contents = file->read();
	string fileName = "";
	for (size_t i = 0; i < contents.size(); ++i) {
		if (contents[i] == '\n') {
			string oldCWD = CWD;
			CWD = CWD + '/' + fileName;
			AbstractFile* fileInDir = fs->openFile(CWD);
			if (fileInDir == nullptr) {
				CWD = oldCWD;
				fileName = "";
				continue;
			}
			fileInDir->accept(this);
			fs->closeFile(fileInDir);
			fs->deleteFile(CWD);
			CWD = oldCWD;
			fileName = "";
			continue;
		}
		fileName += contents[i];
	}
}
	