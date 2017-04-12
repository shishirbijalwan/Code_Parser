/////////////////////////////////////////////////////////////////////
// FileMgr.cpp - find files matching specified patterns            //
//               on a specified path                               //
//                                                                 //
// Jim Fawcett, Help Session Demo, Spring 2015                     //
/////////////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include "DataStore.h"
#include <iostream>

#ifdef TEST_FILEMGR

int main()
{
  DataStore ds;

  std::cout << "\n  Demonstrating FileMgr";
  std::cout << "\n =======================\n";

  std::string path = FileSystem::Path::getFullFileSpec(".");
  std::cout << "\n  searching path: " << path << "\n";
  FileMgr fm(".", ds);
  //fm.addPattern("*.h");
  //fm.addPattern("*.partial");
  fm.search();
  for (auto fs : ds)
  {
    std::cout << "\n  " << fs;
  }
  std::cout << "\n\n";
  return 0;
}
#endif
//This function returns all the sub directories
//void FileMgr::setDirectoriesCollection(std::string currentDirectory)
//{
//	std::vector<std::string> dirCollection = FileSystem::Directory::getDirectories(currentDirectory);
//	std::vector<std::string>::iterator itr = dirCollection.begin();
//
//
//
//	itr += 2;
//	while (itr != dirCollection.end()) {
//		FileSystem::Directory::setCurrentDirectory(*itr);
//		DirectoriesCollection.push_back(FileSystem::Directory::getCurrentDirectory());
//		setDirectoriesCollection(".");
//		++itr;
//	}
//	FileSystem::Directory::setCurrentDirectory("..");
//}
////this function returns the collection of directories in a vector
//std::vector<std::string> FileMgr::getDirectoriesCollection()
//{
//	return DirectoriesCollection;
//}
