/////////////////////////////////////////////////////////////////////
//  ASTree.cpp - Analyzes C++ language constructs                  //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP Pallvilion, Windows 7                        //
//  Application:   CodeParser for CSE687 Pr2, Sp16                 //
//  Author:        Shishir Bijalwan, Syracuse University           //
//                 (979) 587-6340, sbijalwa@syr.edu                //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "ASTree.h"
#include "ConfigureParser.h"


//This is the Node for the ASTree
struct ASTNode {
	std::string type;
	std::string name;
	size_t lineCountStart;
	size_t lineCountEnd;
	ASTNode();
	std::vector<ASTNode*> _child;
	ASTNode* _parent;

	std::string show()
	{
		std::ostringstream temp;
		temp << "(";
		temp << type;
		temp << ", ";
		temp << name;
		temp << ", ";
		temp << (lineCountEnd - lineCountStart +1);
		temp << ")";
		return temp.str();
	}

};

	

//Default Constructor to intialize parent to nullptr
ASTNode::ASTNode() {
	_parent = nullptr;
}


//This function is to add a new node to the tree
void ASTree::addASTNode(ASTNode* node)
{
	currentNode->_child.push_back(node);
	node->_parent = currentNode;
	currentNode = node;
}
//This function return line count of node
size_t ASTree::countLine(ASTNode* pASTNode)
{    
	size_t nodeSize = (pASTNode->lineCountEnd - pASTNode->lineCountStart + 1);

	return nodeSize;
}
//This function gives the number of child nodes of a particular node
int ASTree::calculateChildNodes(std::string name, ASTNode* currentRoot)
{
	int count = 0;
	ASTNode* temRoot;
	if (currentRoot == nullptr) {
			temRoot = searchNode(name);
	}
	else { temRoot = currentRoot; }
	if (temRoot->_child.size() == 0) count++;


	if (temRoot->_child.size() != 0) {
		count++;
	for (int i = 0; i < temRoot->_child.size(); i++) {
		
			count= count + calculateChildNodes(name, temRoot->_child[i]);
			 
		}
	}

	return count;
}

// This function is used at end of a scope for moving to parent node
void ASTree::endScopeNodeShift(size_t endLine)
{
	currentNode->lineCountEnd = endLine;
	if (currentNode->lineCountEnd > root->lineCountEnd)
		root->lineCountEnd = currentNode->lineCountEnd;
	currentNode = currentNode->_parent;

}
//This function searches for a node by name
ASTNode* ASTree::searchNode(std::string name, ASTNode* psearchNode)
{  
	ASTNode* tempRoot;
	ASTNode* NodeFound =nullptr;
	
	if(psearchNode == nullptr){
	tempRoot = root;
}
	else {
		tempRoot = psearchNode;
			
	}
	
for (int i = 0; i < tempRoot->_child.size(); i++) {
	if (tempRoot->_child[i]->name == name && tempRoot->_child[i]->type=="function") {
		NodeFound = tempRoot->_child[i];
		return NodeFound;
		}
	if(NodeFound==nullptr){
		NodeFound=searchNode(name, tempRoot->_child[i]);
}
	
	

}
return NodeFound;
	}

// This function is to return root
ASTNode* ASTree::returnRoot()
{
	return root;
}

//This function is for tree walk and display it
void ASTree::treeWalk(ASTNode* pItem)
{
	static size_t indentLevel = 0;
	std::cout << "\n  " << std::string(2 * indentLevel, ' ') << pItem->show();
	auto iter = pItem->_child.begin();
	++indentLevel;
	while (iter != pItem->_child.end())
	{
		treeWalk(*iter);
		++iter;
	}
	--indentLevel;

}

//This is the constructor which assigns the global namespace
ASTree::ASTree() {
	root = new ASTNode;
	root->type = "NameSpace";
	root->name = "Global";
	root->lineCountStart = 1;
	root->lineCountEnd = 1;
	currentNode = root;
}
//Function to delete tree
void ASTree::deleteTree(ASTNode * node)
{

	for (auto child : node->_child) {
		deleteTree(child);
	}
	delete node;
}
// destructor for ASTree
ASTree::~ASTree() {
	deleteTree(root);
}
//This function is to add a node to ASTree
void ASTree::AddNewNode(std::string nodetype, std::string nodename, size_t lineCount)
{
	ASTNode* newNode = new ASTNode;
	newNode->type = nodetype;
	newNode->name = nodename;
	newNode->lineCountStart = lineCount;
	newNode->_parent = currentNode;
	currentNode->_child.push_back(newNode);
	currentNode = newNode;
	
}
// This function is to collect same type of node names
std::vector<std::string> ASTree::collectSingleType(std::string _type, ASTNode * currentRoot)
{
	std::vector<std::string> collection;
	ASTNode* temRoot;
	if (currentRoot == nullptr) {
		temRoot = root;
	}
	else { temRoot = currentRoot; }
	if (temRoot->type == _type) {
		collection.push_back(temRoot->name);
	}
	for (int i = 0; i < temRoot->_child.size(); i++) {
			std::vector<std::string> temp = collectSingleType(_type, temRoot->_child[i]);
			collection.insert(collection.end(), temp.begin(), temp.end());
	
	}
	return collection;
}
//This was the test stub to test ASTree
#ifdef TEST_ASTree

#include <queue>
#include <string>
#define Util StringHelper

int main(int argc, char* argv[])
{
	ASTNode* node1 = new ASTNode;
	node1->type = "NameSpace";
	node1->name = "Global";
	node1->lineCountStart = 1;
	ASTree* asttree = new ASTree(node1);

	ASTNode* node2 = new ASTNode;
	node2->type = "Class";
	node2->name = "Test";
	node2->lineCountStart = 1;
	asttree->addASTNode(node2);


	ASTNode* node3 = new ASTNode;
	node3->type = "Function";
	node3->name = "Display";
	node3->lineCountStart = 2;
	asttree->addASTNode(node3);

	asttree->treeWalk(node1);


}

#endif