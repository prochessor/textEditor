#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "LinkList.h"
# include "myconsole.h"
# include "editor.h"
#include <string>
#include <string.h>
#include <cstring>
#include "OperationControl.h"
using namespace std;



//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK = 0x00;	int B_Royal_Blue = 0x10;	int B_Dark_Green = 0x20;
int B_Tale_Blue = 0x30;	int B_Dark_Red = 0x40;	int B_Purple = 0x50;
int B_Tale_Green = 0x60;	int B_Light_Grey = 0x70; int B_Dark_Gray = 0x80;
int B_Light_Blue = 0x90; int B_Light_Green = 0xA0;	int B_Sky_Blue = 0xB0;
int B_Red = 0xC0;	int B_Pink = 0xD0;	int B_Yellow = 0xE0;
int B_White = 0xF0;

int F_BLACK = 0x00;	int F_Royal_Blue = 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue = 0x03;	int F_Dark_Red = 0x04;	int F_Purple = 0x05;
int F_Tale_Green = 0x06;	int F_Light_Grey = 0x07; int F_Dark_Gray = 0x08;
int F_Light_Blue = 0x09; int F_Light_Green = 0x0A;	int F_Sky_Blue = 0x0B;
int F_Red = 0x0C;	int F_Pink = 0x0D;	int F_Yellow = 0x0E;
int F_White = 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x < MaxPoint.x)
		x++;
	else if (y < MaxPoint.y)
	{
		x = 0;
		y = y + 1;
	}
	else
		returnValue = false;

	return returnValue;
}

bool point::incrementY()
{
	bool returnValue = true;
	if (y < MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else if (y > 0)
	{
		x = MaxPoint.x;
		y--;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//


//--------------------------The function Where you will write code--------------------------------//


int mainEditor()
{
	LinkList<char> text;
	int key = 0;
	bool stop = false;
	point currentPosition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;
	LinkList<char> ::iterator currentPos = text.extremeBegin();
	int cursorEndPositionX = 0;
	int cursorEndPositionY = 0;

	LinkList<OperationControl<char>> operations;
	int operationSize = 0;
	int operationsMaxSize = 15;
	LinkList<OperationControl<char>>::iterator currentOperation = operations.extremeBegin();
	while (!stop)
	{
		bool isCharKeyPressed = false;
		key = CheckWhichKeyPressed(specialKey);
		//escape key stops the editor
		if (key == ESCKEY)
			stop = true;
		//to insert the charecter in the list and to print the charecters
		else if (!specialKey && key >= 32 && key <= 126)
		{
			if (cursorEndPositionX != MAX_X || cursorEndPositionY != MAX_Y)
			{
				std::cout << char(key);
				//Inserting the charecter into the node list
				isCharKeyPressed = true;
				// Storing the previous information
				OperationControl<char>* newOperation = new OperationControl<char>(text, currentPosition.getX(), currentPosition.getY());
				operations.insert(currentOperation, *newOperation);
				currentOperation++;

				operationSize++;
				if (operationSize > operationsMaxSize)
				{
					operationSize--;
					operations.deleteAtHead();
				}

				currentPosition.incrementX(); //auto updates the x and y posiitons
				text.insert(currentPos, char(key));
				currentPos++; //updating the iterator


				//this just keeps the track of the latest cursor position
				if (cursorEndPositionX < MAX_X)
				{
					cursorEndPositionX++;
				}
				else if (cursorEndPositionY < MAX_Y)
				{
					cursorEndPositionY++;
					cursorEndPositionX = 0;
				}

				//You can change color of text by calling this function
				SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_Light_Blue | B_BLACK);   //ForeGround|BackGround
			}

		}
		else if (specialKey && key == LEFTKEY)
		{
			if (currentPosition.getX() != 0 || currentPosition.getY()!= 0)
			{
				currentPosition.decrementX();
				currentPos--;
			}
		}
		else if (specialKey && key == RIGHTKEY)
		{
			if (currentPosition.getX() < cursorEndPositionX && currentPosition.getY() == cursorEndPositionY)
			{
				currentPosition.incrementX();
				currentPos++;
			}
			else if (currentPosition.getY() < cursorEndPositionY)
			{
				currentPosition.incrementX();
				currentPos++;
			}

		}
		else if (specialKey && key == UPKEY)
		{
			if (currentPosition.getY() > 0)
			{
				for (int i = 0; i <= MAX_X; ++i)
				{
					--currentPos;
					currentPosition.decrementX();
				}
			}
		}
		else if (specialKey && key == DOWNKEY)
		{
			if (currentPosition.getY() == cursorEndPositionY - 1 && currentPosition.getX() <= cursorEndPositionX) {
				for (int i = 0; i <= MAX_X; ++i)
				{
					++currentPos;
					currentPosition.incrementX();
				}
			}
			else if (currentPosition.getY() < cursorEndPositionY - 1)
			{
				for (int i = 0; i <= MAX_X; ++i)
				{
					++currentPos;
					currentPosition.incrementX();
				}
			}

		}
		else if (key == ENTERKEY) 
		{
			/*std::cout << ('\n');
			text.insert(currentPos, char(key));
			currentPos++;
			cursorCurrentPositionX = 0;
			cursorCurrentPositionY++;
			cursorEndPositionX = 0;
			cursorEndPositionY++;
			currentPosition.setX(0);
			currentPosition.incrementY();*/
		}
		else if (key == DELKEY)
		{
			//call a function to handle 
		}
		else if (key == BACKSPACE)
		{

			if (currentPosition.getX() != 0 || currentPosition.getY() != 0)
			{
				OperationControl<char>* newOperation = new OperationControl<char>(text, currentPosition.getX(), currentPosition.getY());
				operations.insert(currentOperation, *newOperation);
				currentOperation++;

				operationSize++;
				if (operationSize > operationsMaxSize)
				{
					operationSize--;
					operations.deleteAtHead();
				}
				isCharKeyPressed = true;
				currentPosition.decrementX();// updating the cursor position
				text.deleteNode(currentPos); // updating the link list
				if (cursorEndPositionX == 0)
				{
					if (cursorEndPositionY > 0)
					{
						cursorEndPositionX = MAX_X;
						cursorEndPositionY--;
					}
				}
				else
				{
					cursorEndPositionX--;
				}
				PlaceCursor(cursorEndPositionX, cursorEndPositionY);
				cout << " ";
			}
		}
		else if (key == F1KEY || key == F2KEY || key == F3KEY)
		{
			//handle search here
			//you can take the cursor at the bottom of the screen and get some input
			//for searching
			int saveX = currentPosition.getX(), saveY = currentPosition.getY();
			PlaceCursor(0, MAX_Y+10);
			cout << "Enter Search Text: ";
			string toSearch;
			currentPosition.setX(0 + strlen("Enter Search Text: "));
			currentPosition.setY(MAX_Y);
			getline(cin, toSearch);
			if (key == F1KEY)
			{
				//Search for one instance of string and move cursor there
				int x = 0, y1 = 0;
				int length = 0;
				for (LinkList<char> ::iterator i = text.begin(); length < text.size(); ++i, ++length)
				{
					LinkList<char> ::iterator save = i;
					bool flag = false;
					for (int y = 0; y < toSearch.size(); ++y, save++)
					{
						if (toSearch[y] != *save)
							flag = true;
					}
					if (!flag)
					{
						break;
					}
					if (x < MAX_X)
					{
						x++;
					}
					else if (y1 < MAX_Y) {
						x = 0;
						y1++;
					}
				}
				currentPosition.setX(x);
				currentPosition.setY(y1);

				//update the iterator
				currentPos = text.extremeBegin();
				for (int i = 0; i < length; ++i)
				{
					++currentPos;
				}
			}
			if (key == F2KEY)
			{
				//Search for one instance of string and move cursor there
				int x = 0, y = 0, y1 = 0;
				int length = 0;
				for (LinkList<char> ::iterator i = text.begin(); length < text.size(); ++i, ++length)
				{
					y = 0;
					LinkList<char> ::iterator save = i;
					bool flag = false;
					for (; y < toSearch.size(); ++y, save++)
					{
						if (toSearch[y] != *save)
							flag = true;
					}
					if (!flag)
					{
						//Search for all instances of string and Highlight them
						int a = x, b = y1;
						for (int j = 0; j < toSearch.size(); ++j)
						{
							SetColorAtPoint(a, b, F_Yellow | B_BLACK);
							if (x < MAX_X)
							{
								a++;
							}
							else
							{
								a = 0;
								b++;
							}
						}
					}
					if (x < MAX_X)
					{
						x++;
					}
					else if (y1 < MAX_Y) {
						x = 0;
						y1++;
					}
				}
				currentPosition.setX(saveX);
				currentPosition.setY(saveY);
			}
			else
			{
				bool isInstanceFoundAndReplacedAndStored = false;
				string toReplace;
				cout << "Enter the string to Replace: ";
				getline(cin, toReplace);
				isCharKeyPressed = true;
				int x = 0, y1 = 0;
				int length = 0;
				for (LinkList<char> ::iterator i = text.begin(); length < text.size() && i != nullptr; ++i, ++length)
				{
					LinkList<char> ::iterator save = i;
					bool flag = false;
					for (int y = 0; y < toSearch.size(); ++y, save++)
					{
						if (toSearch[y] != *save)
						{
							flag = true;
							break;
						}
						if (save + 1 == nullptr)
						{
							if( y != toSearch.size()-1)
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						if (isInstanceFoundAndReplacedAndStored == false)
						{
							OperationControl<char>* newOperation = new OperationControl<char>(text, saveX, saveY);
							operations.insert(currentOperation, *newOperation);
							currentOperation++;
							operationSize++;
							if (operationSize > operationsMaxSize)
							{
								operationSize--;
								operations.deleteAtHead();
							}
							isInstanceFoundAndReplacedAndStored = true;
						}
						

						//Searched and now replace karo
						for (int k = 0; k < toSearch.size(); ++k)
						{						
							text.deleteNode(i);
							if (k + 1 != toSearch.size())
								i++;
							
						}
						for (int k = 0; k < toReplace.size(); ++k)
						{
							text.insert(i, toReplace[k]);
							if (k + 1 != toReplace.size())
								i++;
						}
						
					}
					if (x < MAX_X)
					{
						x++;
					}
					else if (y1 < MAX_Y) {
						x = 0;
						y1++;
					}
					
				}
				system("cls");
				PlaceCursor(0, 0);
				LinkList<char>::iterator j = text.begin();
				cursorEndPositionX = 0;
				cursorEndPositionY = 0;
				for (int a = 0; j != text.end(); a++, ++j)
				{
					cout << *j;
					if (a == MAX_X)
					{
						cout << endl;
						a = -1;
					}
					if (cursorEndPositionX < MAX_X)
					{
						cursorEndPositionX++;
					}
					else if (cursorEndPositionY < MAX_Y)
					{
						cursorEndPositionY++;
						cursorEndPositionX = 0;
					}
					currentPos = j;
				}
				currentPosition.setX(cursorEndPositionX);
				currentPosition.setY(cursorEndPositionY);
			}
		}
		else if (key == F4KEY)
		{
			ofstream out("data.txt");
			LinkList<char>::iterator i = text.begin();

			for (int a = 0; i != text.end(); a++, ++i)
			{
				out << *i;
				if (a == MAX_X)
				{
					out << endl;
					a = -1;
				}
			}
			out.close();
		}
		else if (key == CTRL_Z)
		{

			if (operationSize > 0) {
				text = (*currentOperation).operationText;
				currentPosition.setX((*currentOperation).cursorPositionX);
				currentPosition.setY((*currentOperation).cursorPositionY);
				currentPos = text.extremeBegin();
				for (int a = 0, b = 0; a != currentPosition.getX() || b != currentPosition.getY();)
				{
					if (a < MAX_X)
					{
						a++;
					}
					else
					{
						a = 0;
						b++;
					}
					currentPos++;
				}

				operations.deleteNode(currentOperation);
				operationSize--;

				system("Cls");
				LinkList<char>::iterator j = text.begin();
				cursorEndPositionX = 0;
				cursorEndPositionY = 0;
				for (int a = 0; j != text.end(); a++, ++j)
				{
					cout << *j;
					if (a == MAX_X)
					{
						cout << endl;
						a = -1;
					}
					if (cursorEndPositionX < MAX_X)
					{
						cursorEndPositionX++;
					}
					else if (cursorEndPositionY < MAX_Y)
					{
						cursorEndPositionY++;
						cursorEndPositionX = 0;
					}
					//currentPos = j;
				}
			}
		}
		PlaceCursor(currentPosition.getX(), currentPosition.getY());
		if (isCharKeyPressed)
		{
			LinkList<char>::iterator i = currentPos;
			i++;
			for (int a = currentPosition.getX(); i != text.end(); ++i)
			{
				cout << *i;
				if (a == MAX_X) {
					cout << endl;
					a = 0;
				}
				else
					a++;
			}
			isCharKeyPressed = false;
		}
	}
	/*cout << "\n\n\n\n";
	LinkList<char>::iterator i = text.begin();
	for (int a = 0; i != text.end(); ++i)
	{
		cout << *i;
		if (a == MAX_X) {
			cout << endl;
			a = 0;
		}
		else
			a++;
	}*/
	return 0;
}

//-------------------------------------------End Main Editor--------------------------//
void main()
{

	mainEditor();

	/*LinkList<char> l1;
	l1.insertAtHead('a');
	l1.insertAtHead('b');
	LinkList<char> l2(l1);
	l1.printTechnically();
	l2.printTechnically();*/

	/*
	l1.insertAtHead('d');
	l1.insertAtHead('c');
	l1.insertAtHead('b');
	l1.insertAtHead('a');
	l1.printTechnically();
	l1.swap(2, 3);
	l1.printTechnically();
	LinkList<char>::iterator i = l1.begin();
	i++; i++;
	LinkList<char>::iterator j = l1.begin();

	l1.insert(i, 'e');
	l1.printTechnically();
	char a[]{ "paodf" };
	l1.insertMultiple(i, a, 5);
	l1.printTechnically();
	++i, ++i;
	l1.deleteInRange(j, i);
	l1.printTechnically();
	l1.deleteNode(i);
	l1.printTechnically();
	LinkList <char>::iterator l2 = l1.searchFirst('f');
	cout << *l2 << endl;*/
	return;
}