#ifndef CONFIGUREPARSER_H
#define CONFIGUREPARSER_H
/////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - builds and configures parsers              //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP Pallvilion, Windows 7                        //
//  Application:   CodeParser for CSE687 Pr2, Sp16                 //
//  Author:        Shishir Bijalwan, Syracuse University           //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module builds and configures parsers.  It builds the parser
parts and configures them with application specific rules and actions.

Public Interface:
=================
ConfigParseToConsole conConfig;
conConfig.Build();
conConfig.Attach(someFileName);

Build Process:
==============
Required files
-MetricsAnalysis.h,ASTree.h, ConfigureParser.h, ConfigureParser.cpp, Parser.h, Parser.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
Build commands (either one)
- devenv Project1HelpS06.sln
- cl /EHsc /DTEST_PARSER ConfigureParser.cpp parser.cpp \
ActionsAndRules.cpp \
semiexpression.cpp tokenizer.cpp /link setargv.obj

Maintenance History:
====================
ver 1.0
*/

//
#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"
#include "ASTree.h"
#include "MetricsAnalysis.h"

///////////////////////////////////////////////////////////////
// build parser that writes its output to console

class ConfigParseToConsole : IBuilder
{
public:
	ConfigParseToConsole() {};
	~ConfigParseToConsole();
	bool Attach(const std::string& name, bool isFile = true);
	Parser* Build();
	void displayTree() {pRepo->ASTree()->treeWalk(pRepo->ASTree()->returnRoot());}

	ASTree* getPointerASTree() {return astree;}
private:
	// Builder must hold onto all the pieces

	std::ifstream* pIn;
	Scanner::Toker* pToker;
	Scanner::SemiExp* pSemi;
	Parser* pParser;
	Repository* pRepo;
	ASTree* astree;
	

	// add Rules and Actions

	BeginningOfScope* pBeginningOfScope;
	HandlePush* pHandlePush;
	EndOfScope* pEndOfScope;
	HandlePop* pHandlePop;
	FunctionDefinition* pFunctionDefinition;
	PushFunction* pPushFunction;
	PrintFunction* pPrintFunction;
	ConditionalStatements* pConditionalStatements;
	PushConditionsalStatements* pPushConditionalStatements;
	PrintConditionalStatement* pPrintConditionalStatement;
	ClassAndNameSpace* pClassAndNameSpace;
	PushClassAndNameSpace* pPushClassAndNameSpace;
	PrintClassAndNameSpace* pPrintClassAndNameSpace;
	ExceptionRule* pExceptionRule;
	PushExceptionScope* pPushExceptionScope;
	BeginningOfDeclarationScope* pBeginningOfDeclarationScope;
	DeclarationScopePush* pDeclarationScopePush;

	// prohibit copies and assignments

	ConfigParseToConsole(const ConfigParseToConsole&) = delete;
	ConfigParseToConsole& operator=(const ConfigParseToConsole&) = delete;
};


#endif
