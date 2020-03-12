/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
filesystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
*/

#include <iostream>
#include "SimpleFileSystem.h"
#include "SimpleFileFactory.h"
#include<algorithm>
#include<iterator>
#include "ReadFileVisitor.h"
#include "HierarchicalFileSystem.h"
#include "HierarchicalFileFactory.h"
#include "CommandPrompt.h"
#include "TouchCommand.h"
#include "CDCommand.h"
#include "LSCommand.h"
#include "RemoveCommand.h"
#include "DisplayCommand.h"
#include "CatCommand.h"
#include "CPCommand.h"
#include "SymCommand.h"

//include more files to test
#include "TextFile.h"
#include "ImageFile.h"
#include "DirectoryFile.h"

using namespace std;

int main(int argc, char * arg[])
{
	// allocate all objects needed
	AbstractFileFactory* ff = new HierarchicalFileFactory();
	AbstractFileSystem *fs = new HierarchicalFileSystem();
	AbstractCommand* com = new TouchCommand(ff,fs);
	AbstractCommand* com1 = new CDCommand(fs);
	AbstractCommand* com2 = new LSCommand(fs);
	AbstractCommand* com3 = new RemoveCommand(fs);
	AbstractCommand* com4 = new DisplayCommand(fs);
	AbstractCommand* com5 = new CatCommand(fs);
	AbstractCommand* com6 = new CPCommand(fs);
	AbstractCommand* com7 = new SymCommand(fs);

	// create command prompt and configure
	// NOTE: the above commands will not work with a SimpleFileSystem, it would need a new set of commands
	// or a second CommandPrompt class
	CommandPrompt cmd;
	cmd.setFileSystem(fs);
	cmd.setFileFactory(ff);
	cmd.addCommand("touch", com);
	cmd.addCommand("cd", com1);
	cmd.addCommand("ls", com2);
	cmd.addCommand("rm", com3);
	cmd.addCommand("ds", com4);
	cmd.addCommand("cat", com5);
	cmd.addCommand("cp", com6);
	cmd.addCommand("sym", com7);

	//add to test
	TextFile* t = new TextFile("123.txt");
	vector<char> tContent(4, 'a');
	t->write(tContent);
	ImageFile* i = new ImageFile("abc.img");
	vector<char> iContent{ 'X',' ','X',' ','X',' ','X',' ','X', '3' };
	i->write(iContent);
	DirectoryFile* d = new DirectoryFile("xyz");
	DirectoryFile* dChild = new DirectoryFile("xyzChild");
	DirectoryFile* dChildChild = new DirectoryFile("xyzChildChild");

	TextFile* t2 = new TextFile("xyzTxt.txt");
	ImageFile* i2 = new ImageFile("xyzImg.img");

	TextFile* t3 = new TextFile("lastTxt.txt");

	fs->addFile("root/", t);
	fs->addFile("root/", i);
	fs->addFile("root/", d);
	fs->addFile("root/xyz/", dChild);
	fs->addFile("root/xyz/", t2);
	fs->addFile("root/xyz/", i2);
	AbstractFile* a = fs->openFile("root/xyz/xyzTxt.txt");
	fs->addFile("root/xyz/xyzChild/", dChildChild);
	fs->addFile("root/xyz/xyzChild/xyzChildChild/", t3);
	fs->openFile("root/xyz/xyzChild/xyzChildChild/lastTxt.txt");




	// run the command prompt
	cmd.run();

	// clean up dynamically allocated resources
	delete ff;
	delete fs; // all files are destroyed here (in the file system destructor)
	delete com;
	delete com1;
	delete com2;
	delete com3;
	delete com4;
	delete com5;
	delete com6;
	delete com7;

	return 0;
}

