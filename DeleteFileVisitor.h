#pragma once
#include "AbstractFileVisitor.h"
#include "AbstractFileSystem.h"

class DeleteFileVisitor : public AbstractFileVisitor {
public:
	virtual void visit(TextFile*) override;
	virtual void visit(ImageFile*) override;
	virtual void visit(DirectoryFile*) override;
	DeleteFileVisitor(AbstractFileSystem* fileSys, std::string cwd);
private:
	AbstractFileSystem* fs;
	std::string CWD;
};