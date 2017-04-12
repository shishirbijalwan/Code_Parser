#ifndef METRICSEXECUTIVE_H
#define METRICSEXECUTIVE_H
/////////////////////////////////////////////////////////////////////
//  MetricsExecutive.h - Analyzes C++ language constructs                    //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP Pallvilion, Windows 7                        //
//  Application:   CodeParser for CSE687 Pr2, Sp16                 //
//  Author:        Shishir Bijalwan, Syracuse University           //
//                 (979) 587-6340, sbijalwa@syr.edu                //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This module is to test the whole system as a whole. We have shown each and 
every requirement in the this package.

Public Interface:
=================
diplayRequirement1()         This function is to display the requirements

Build Process:
==============
Required files
- ConfigureParser.h,ASTree.h

Maintenance History:
====================
ver 1.0

*/

#include <string>
#include <iostream>
#include <vector>
#include "ConfigureParser.h"
#include "ASTree.h"


class MetricsExecutive {
public:
	void setDirectoriesCollection(std::string currentDirectory);
	std::vector<std::string> getDirectoriesCollection();
	void displayTree(ConfigParseToConsole& config, bool& diplayTree);
	void displayComplexity(ASTree* astree);
	void diplayRequirement1();
private:
	std::vector<std::string> DirectoriesCollection;

};


#endif
