/////////////////////////////////////////////////////////////////////
//  MetricsExecutive.cpp - Analyzes C++ language constructs           //
//  ver 1.4                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include "ASTree.h"
#include "MetricsAnalysis.h"
#include "MetricsExecutive.h"
#include  "Parser.h"
#include "ConfigureParser.h"
#include "../Utilities/Utilities.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../FileSystem-Windows/FileSystemDemo/FileMgr.h"

using namespace Scanner;
using namespace Utilities;

#ifdef TEST_EXECUTIVE

#include <queue>
#include <string>
#include "MetricsExecutive.h"
#define Util StringHelper


int main(int argc, char* argv[])
{	
	Util::Title("Testing for Project2", '=');
	DataStore ds;
MetricsExecutive metricExecutive;
bool treeDisplay = true;
metricExecutive.diplayRequirement1();
	FileMgr Fmanager(argv[1], ds);
	for (int i = 2; i < argc; i++) {
		Fmanager.addPattern(argv[i]);
	}
	Fmanager.search();

	for (auto itr : ds) {
		std::string msg = "Processing file" + itr;
		Util::title(msg);
		ConfigParseToConsole configure;
				Parser* pParser = configure.Build();
				try
				{if (pParser)
					{if (!configure.Attach(itr))
						{std::cout << "\n  could not open file " << itr << std::endl;continue;}
					}
					else{std::cout << "\n\n  Parser not built\n\n";return 1;}
					while (pParser->next())
						pParser->parse();
					std::cout << "\n";}
				catch (std::exception& ex){std::cout << "\n\n    " << ex.what() << "\n\n";}
				metricExecutive.displayTree(configure, treeDisplay);
				metricExecutive.displayComplexity(configure.getPointerASTree());	
	
	
	}

}

#endif
//This function is to get the collection of sub directories.Now we are using fileManager for this
void MetricsExecutive::setDirectoriesCollection(std::string currentDirectory)
{
	std::vector<std::string> dirCollection = FileSystem::Directory::getDirectories(currentDirectory);
	std::vector<std::string>::iterator itr = dirCollection.begin();
	itr += 2;
	while (itr != dirCollection.end()) {
		FileSystem::Directory::setCurrentDirectory(*itr);
		DirectoriesCollection.push_back(FileSystem::Directory::getCurrentDirectory());
		setDirectoriesCollection(".");
		++itr;
	}
	FileSystem::Directory::setCurrentDirectory("..");
}
//This function returns vector of directories
std::vector<std::string> MetricsExecutive::getDirectoriesCollection()
{
	return DirectoriesCollection;
}
//This functions supports in requirement display
void MetricsExecutive::displayTree(ConfigParseToConsole& config, bool& diplayTree)
{
	if (diplayTree) {

		std::cout << "Requirement 5. Provided an associated RulesAndActions package that has rules to detect: " << std::endl;
		std::cout << "           -Global functions and static and non-static member function definitions (Shown in Treewalk)" << std::endl;
		std::cout << "           -beginning and end of all C++ scopes." << std::endl;
		putline();
		std::cout << "============================" <<  std::endl;
		std::cout << "Tree Display start for File " << std::endl;
		std::cout << "============================" << std::endl;

		config.displayTree();
		diplayTree = false;
		putline(); putline();
		std::cout << "Requirement 6. Provides a facility for building an abstract syntax tree that provides an interface for adding scope nodes to the tree and an methods to analyze the contents of the tree.  " << std::endl;
		putline();
		std::cout << " Function- void addASTNode(ASTNode* node) to add the node to the Tree(Please note i have not used ScopeStack).  " << std::endl;
		std::cout << " Function- ASTNode* searchNode(std::string name, ASTNode* searchNode = nullptr) to search for a node in Tree" << std::endl;
		std::cout << " Function- void treeWalk(ASTNode* node) to display the tree.  " << std::endl;
		putline();
		std::cout << "Requirement 7. Provided a FileMgr package that supports finding files and/or directories in a directory tree rooted at a specified path ->FileMgr.h  " << std::endl;
		putline();
		std::cout << "Requirement 8.  Provided a MetricsAnalysis package for evaluating and displaying the size and complexity of all global functions, static member functions, and non-static member functions in each of a set of specified packages. ->MetricAnalysis.h  " << std::endl;
		putline();
		std::cout << "Requirement 9 and 10. Provided a MetricsExecutive package that enables collecting metrics for all the packages with names that match a specified pattern in a directory tree rooted at a specified path.It acts as the Automated set suit." << std::endl;

	}
}
//This function helps in display of Complexity
void MetricsExecutive::displayComplexity(ASTree * astree)
{
	std::cout << "==========================================================" << std::endl;
	std::cout << " Displaying complexity and size of functions available" << std::endl;
	std::cout << "==========================================================" << std::endl;
	MetricsAnalysis metric = MetricsAnalysis(astree);
	metric.DisplayMetrics("function");
}
//This function is to display Requirements
void MetricsExecutive::diplayRequirement1()
{
	putline();
	std::cout << "Requirement 1. Have used Visual Studio 2015 and its C++ Windows Console Projects, as provided in the ECS computer labs." << std::endl;
	std::cout << "Requirement 2. Have used the C++ standard library's streams for all I/O and new and delete for all heap-based memory management1." << std::endl;
	std::cout << "Requirement 3. Provided C++ packages for analyzing function size and complexity metrics for a set of specified packages. These packages  use the Tokenizer and SemiExpression packages developed in Project #1" << std::endl;
	std::cout << "Requirement 4.  Have provided a Parser package with a Parser class that is a container for Rules and that provides the interfaces IRule and IAction for rules contained in the Parser and actions contained in each rule. " << std::endl;
	putline();
}
