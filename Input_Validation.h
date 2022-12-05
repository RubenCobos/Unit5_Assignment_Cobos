// Validates user input by making sure the input requested is of the correct type and format.
// Based on Dr. T's input validation code.

#include <iostream>
#include <string>


using namespace std;


// Function prototypes for each type of input.

int Validate_Integer(int&);
double Validate_Rational(double&);
char Validate_Character(char&);
string Validate_Word(string&);


/* A polymorphic function the validates user input. Checks if any error flags have been set
 and for extraneous input. If an error is found, the flags are reset, the input stream is
 cleared, and the error is reported. */

template<typename T> T Validate_Input()
{
	T input = {};

	cin >> input;

	if (cin.fail() || cin.get() != '\n')
	{
		cin.clear();

		while (cin.get() != '\n')
		{
			;
		}

		throw ios_base::failure("invalid input");
	}

	return input;
}

// Requested input is of type int.

int Validate_Integer(int& integer)
{
	while (true)
	{
		try
		{
			integer = Validate_Input<int>();
		}
		catch (exception error)
		{
			cerr << error.what() << endl;
			cout << "Enter an integer: ";
			continue;
		}

		break;
	}

	return integer;
}

// Requested input is of type double.

double Validate_Rational(double& rational)
{
	while (true)
	{
		try
		{
			rational = Validate_Input<double>();
		}
		catch (exception error)
		{
			cerr << error.what() << endl;
			cout << "Enter a number: ";
			continue;
		}

		break;
	}

	return rational;
}

// Requested input is of type char.

char Validate_Character(char& character)
{
	while (true)
	{
		try
		{
			character = Validate_Input<char>();
		}
		catch (exception error)
		{
			cerr << error.what() << endl;
			cout << "Enter a single keyboard character: ";
			continue;
		}

		break;
	}

	return character;
}

// Requested input is of type string (no spaces).

string Validate_Word(string& word)
{
	while (true)
	{
		try
		{
			word = Validate_Input<string>();
		}
		catch (exception error)
		{
			cerr << error.what() << endl;
			cout << "Enter a word (no spaces): ";
			continue;
		}

		break;
	}

	return word;
}