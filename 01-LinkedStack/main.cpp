/**
*
* @author Stefani Nikolova
* @compiler VC
*
*/


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "MyVector.h"
#include "LinkedStack.h"
#include "Operator.h"


using namespace std;

//Creating a vector of objects which hold the representation and the actual value of the opeartors
MyVector<Operator> ConvertOperators(MyVector<string> operations) {

	MyVector<Operator> convertedOperators;

	for (int i = 0; i < operations.GetSize() - 1; i += 3)
	{
		Operator obj = Operator();
		obj.setRep(operations[i]);
		obj.setActual(operations[i + 1]);
		convertedOperators.Push(obj);
	}
	return convertedOperators;
}

// Taking the actual operator from the vector
string CheckOperation(string currentToken, MyVector<Operator> ops)
{
	for (int i = 0; i < ops.GetSize(); i++)
	{
		if (currentToken == ops[i].getRep())
		{
			return ops[i].getActual();
		}
	}
	return "Invalid";
}



void ConvertNotatiton(MyVector<string> tokens, MyVector<Operator> convertedOperators)
{
	LinkedStack<string> convertionStack;

	LinkedStack<float> calculationStack;

	for (int i = tokens.GetSize() - 1; i >= 0; i--)
	{
		// This variable represents the current element which is passed by the tokens vector
		string currentInputValue = tokens[i];

		//Check if the current value of the expression is a number
		try
		{
			float numValue = stof(currentInputValue);
			convertionStack.Push(currentInputValue);
			calculationStack.Push(numValue);
		}
		catch (exception e)
		{
			// Check if the expression is valid
			if (convertionStack.GetSize() < 2 || calculationStack.GetSize() < 2)
			{
				cout << "Error" << endl;
				return;
			}

			//**********CONVERSION*************

			string firstElement = convertionStack.Peek();

			convertionStack.Pop();

			string secondElement = convertionStack.Peek();

			convertionStack.Pop();

			string concat = string(firstElement) + " " + string(secondElement) + " " + string(currentInputValue);

			convertionStack.Push(concat);


			//**********CALCULATION************

			float firstElementCalc = calculationStack.Peek();

			calculationStack.Pop();

			float secondElementCalc = calculationStack.Peek();

			calculationStack.Pop();

			float result;


			string currentOperation = CheckOperation(currentInputValue, convertedOperators);
			
			//Check if the current operatoin is invalid
			if (currentOperation == "Invalid")
			{
				cout << "Error" << endl;
				return;
			}


			if (currentOperation == "+")
			{
				result = firstElementCalc + secondElementCalc;
			}
			else if (currentOperation == "-")
			{
				result = firstElementCalc - secondElementCalc;
			}
			else if (currentOperation == "*")
			{
				result = firstElementCalc * secondElementCalc;
			}
			else if (currentOperation == "/")
			{
				result = firstElementCalc / secondElementCalc;
			}
			else
			{
				cout << "Error" << endl;
				return;
			}

			calculationStack.Push(result);
		}
	}

	// Print result
	cout << convertionStack.Peek() << endl;
	printf("%.5f\n", calculationStack.Peek());

	return;
}

int main(int argc, char * argv[])
{
	// Uncomment to write the path to the files in the console
	/*cout << "Expression file: ";
	string expressionFile;
	cin >> expressionFile;
	cout << "Operator file: ";
	string operatorFile;
	cin >> operatorFile;*/

	//Creating a vector to store the elements from the expression 
	MyVector<string> expressionVector;

	//Reading the expression file
	ifstream prefixNotation(argv[1]);

	for (string elem; prefixNotation >> elem;)
	{
		expressionVector.Push(elem);
	}

	//Creating a vector to store the elements from the operator's file
	MyVector<string> operatorVector;

	//Reading the operator's file
	ifstream operators(argv[2]);

	for (string current; operators >> current;)
	{
		operatorVector.Push(current);
	}

	// Convert the current vector into a vector of objects
	MyVector<Operator> convertedOperators = ConvertOperators(operatorVector);

	// Convert notation and calculate
	 ConvertNotatiton(expressionVector, convertedOperators);

	return 0;
}


