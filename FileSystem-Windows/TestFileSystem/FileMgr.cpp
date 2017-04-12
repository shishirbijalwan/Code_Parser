/////////////////////////////////////////////////////////////////////
// FileMgr.cpp - find files matching specified patterns            //
//               on a specified path                               //
//                                                                 //
// Jim Fawcett, Help Session Demo, Spring 2015                     //
/////////////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include "../DataStore/DataStore.h"
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
