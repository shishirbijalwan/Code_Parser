/////////////////////////////////////////////////////////////////////
//  MetricsAnalysis.cpp - Analyzes C++ language constructs         //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP Pallvilion, Windows 7                        //
//  Application:   CodeParser for CSE687 Pr2, Sp16                 //
//  Author:        Shishir Bijalwan, Syracuse University           //
//                 (979) 587-6340, sbijalwa@syr.edu                //
/////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include "ASTree.h"
#include "MetricsAnalysis.h"
#include  "Parser.h"
#include "ConfigureParser.h"
#include "../Utilities/Utilities.h"
using namespace Scanner;
using namespace Utilities;

//Constructor to assign value of ASTree pointer
MetricsAnalysis::MetricsAnalysis(ASTree* astree) {
	treeEvaluated = astree;
	
}

//This functions is display the complexity of the functions in the file
void MetricsAnalysis::DisplayMetrics(std::string _type)
{
	std::vector<std::string> collection;
	collection = treeEvaluated->collectSingleType(_type);

	for (int i = 0; i < collection.size(); i++) {
		ASTNode* astNode = treeEvaluated->searchNode(collection[i]);
	 std::cout << _type <<" " << collection[i] <<" " <<" Complexity "	<<treeEvaluated->calculateChildNodes(collection[i])  << " Size " << treeEvaluated->countLine(astNode) <<  "\n";
	}

}

#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"

#ifdef TEST_MetricsAnalysis

#include <queue>
#include <string>
#define Util StringHelper

int main(int argc, char* argv[])
{
	Util::Title("Testing the Integrated system", '=');
	putline();

	// collecting tokens from files, named on the command line

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}
	//std::cout << "\n value of current directory before change " << FileSystem::Directory::getCurrentDirectory();
	//std::cout << "\nvalue in argument two is " << argv[2];

	FileSystem::Directory::setCurrentDirectory(argv[1]);
	//std::cout << "\n value of current directory after change " << FileSystem::Directory::getCurrentDirectory();
	std::string directory= FileSystem::Directory::getCurrentDirectory();
	//std::cout << " \n value in directory is " << directory;
	std::vector<std::string> files = FileSystem::Directory::getFiles(directory, argv[2]);

	for (int i = 0; i<files.size(); ++i)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(files[i]);
		std::string msg = "Processing file" + fileSpec;
		Util::title(msg);
		putline();
		

		ConfigParseToConsole configure;
		Parser* pParser = configure.Build();

		try
		{
			if (pParser)
			{
				if (!configure.Attach(fileSpec))
				{
					std::cout << "\n  could not open file " << fileSpec << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}
			// now that parser is built, use it

			while (pParser->next())
				pParser->parse();
			std::cout << "\n";
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
		std::cout << "Tree Display start for File " <<(i+1) << "\n\n";
		configure.displayTree();
		std::cout << "\n\n Displaying complexity and size of functions available\n \n";
		
		MetricsAnalysis metric= MetricsAnalysis(configure.getPointerASTree());
	//	MetricsAnalysis* pMetricsAnalysis = new MetricsAnalysis(configure.getPointerASTree);
		metric.DisplayMetrics("function");
		//std::cout << "\n Displaying complexity and size of Class available\n";
		//metric.DisplayMetrics("CLass");
		
	}

	std::cout << "\n";
}

#endif