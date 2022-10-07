#pragma once
#include "LinkList.h"
#include <iostream>

using namespace std;

template<class let>
class OperationControl
{
public:
	LinkList<let> operationText;
	int cursorPositionX;
	int cursorPositionY;
	typename LinkList<let>::iterator iter;
public:
	OperationControl()
	{

	}

	OperationControl(LinkList<let> operationText,int cursorPositionX, int cursorPositionY):operationText{operationText}
	{
		this->cursorPositionX = cursorPositionX;
		this->cursorPositionY = cursorPositionY;
	}



};