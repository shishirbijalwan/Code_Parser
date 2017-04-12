#ifndef METRICSANALYSIS_H
#define METRICSANALYSIS_H
/////////////////////////////////////////////////////////////////////
//  MetricAnalysis.h - Analyzes C++ language constructs            //
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
This module is for doing the matrix analysis of the Abstract Syntax tree. It works
on the abstract syntax stree to calculate its complexity and line count.

Public Interface:
=================
DisplayMetrics (_type);          // display the complexity and lines of a particular type

Build Process:
==============
Required files
- ASTree.h

Maintenance History:
====================
ver 1.0

*/

#include <string>
#include <iostream>
#include <vector>
#include "ASTree.h"


class MetricsAnalysis {
public:
	MetricsAnalysis(ASTree* astree);
	void DisplayMetrics (std::string _type);
	~MetricsAnalysis() { delete treeEvaluated; }
private:
	ASTree* treeEvaluated;
	
};


#endif
