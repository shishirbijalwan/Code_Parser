#ifndef FILEMGR_H
#define FILEMGR_H
/////////////////////////////////////////////////////////////////////
// FileMgr.h - find files matching specified patterns              //
//             on a specified path                                 //
//                                                                 //
// Jim Fawcett, Help Session Demo, Spring 2015                     //
/////////////////////////////////////////////////////////////////////

#include "FileSystem.h"
#include "../DataStore/DataStore.h"

class FileMgr
{
public:
  using iterator = DataStore::iterator;
  using patterns = std::vector<std::string>;

  FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
  {
    patterns_.push_back("*.*");
  }

  void addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
  }

  void search()
  {
    find(path_);
  }

  void find(const std::string& path)
  {
    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
      for (auto f : files)
      {
        store_.save(f);
      }
      std::vector<std::string> dirs = FileSystem::Directory::getDirectories(path);
      for (auto d : dirs)
      {
        if (d == "." || d == "..")
          continue;
        find(d);
      }
    }
  }
private:
  std::string path_;
  DataStore& store_;
  patterns patterns_;
};

#endif
