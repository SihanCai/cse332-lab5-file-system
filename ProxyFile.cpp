/*
Author: Jon Shidal
Purpose: CSE 332 lab 5, defines the TextFile class
*/

#include "ProxyFile.h"
#include "AbstractFileVisitor.h"
#include<iostream>

using namespace std;
//copy constructors for other time use
ProxyFile::ProxyFile(ProxyFile* File): realFile(File->realFile),count(File->count), parent(nullptr) {
	(*count)++;
}
//copy constructors for first time use
ProxyFile::ProxyFile(AbstractFile* File) : realFile(File),parent(nullptr) {
	unsigned int temp = 1;
	count = &temp;
}
//the shared pointer kind of destructor
ProxyFile::~ProxyFile() {
	(*count)--;
	if (*count == 0) {
		delete realFile;
		delete count;
	}
}

unsigned int ProxyFile::getSize() {
	return realFile->getSize();
}

string ProxyFile::getName() {
	return realFile->getName();
}

vector<char> ProxyFile::read() {
	return realFile->read();
}

AbstractFile* ProxyFile::clone() {
	return realFile->clone();
}

void ProxyFile::accept(AbstractFileVisitor* fv) {
	return realFile->accept(fv);
}

int ProxyFile::write(vector<char> data) {
	return realFile->write(data);
}

int ProxyFile::append(vector<char> data) {
	return realFile->append(data);
}

int ProxyFile::addChild(AbstractFile* f) {
	return notacomposite;
}

int ProxyFile::removeChild(string name) {
	return notacomposite;
}

AbstractFile* ProxyFile::getChild(std::string name) {
	return nullptr;
}

AbstractFile* ProxyFile::getParent() {
	return parent;
}
void ProxyFile::setParent(AbstractFile* p) {
	parent=p;
}