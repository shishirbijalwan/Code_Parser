#ifndef ASTREE_H
#define ASTREE_H
/////////////////////////////////////////////////////////////////////
//  ASTree.h - Analyzes C++ language constructs                    //
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
This module defines a Abstract Syntax tree. It provides various interfaces to interact with the tree.
Like the treewalk function which is used to display the tree. It also has interfaces to search a node
in the tree. This tree is mailny created to hold the scopes of the semi expressions.

Public Interface:
=================
treeWalk(ASTNode)         This function is to display the tree

Build Process:
==============
Required files
- None

Maintenance History:
====================
ver 1.0

*/

#include <string>
#include <iostream>
#include <vector>
//forward declaration of the struct ASTNode
struct ASTNode;
class ASTree {
public:
	void treeWalk(ASTNode* node);
	void addASTNode(ASTNode* node);
	//void showCompleteTree();
	size_t countLine(ASTNode* pASTNode);
	int calculateChildNodes(std::string name, ASTNode* currentRoot = nullptr);
	void endScopeNodeShift(size_t endLine);
	ASTNode* searchNode(std::string name, ASTNode* searchNode = nullptr);
	ASTNode* returnRoot();
	ASTree();
	void deleteTree(ASTNode* node);
	~ASTree();
	void AddNewNode(std::string type, std::string name, size_t lineCount) ;
	std::vector<std::string> collectSingleType(std::string _type, ASTNode* currentRoot = nullptr);

private:
	ASTNode* root;
	ASTNode* currentNode;

};


#endif
