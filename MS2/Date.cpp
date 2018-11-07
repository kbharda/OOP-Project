// Final Project Milestone 2
//
// Version 1.0
// Date 11/09/2018
// Author Kashyap Bharda
// Description THE ERROR MODULE
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#include <iostream>
#include <cstring>
#include "Date.h"

using namespace std;

namespace aid {

	//Default Constructor
	Error::Error() {
		this->errorMessage = '\0';
	}
	//One Argument Constructor
	Error::Error(const char * errorMessage)
	{
		if (errorMessage == nullptr || errorMessage == " ")
		{
			this->errorMessage = '\0';
		}
		else if (errorMessage != " ")
		{
			Error::message(errorMessage);
		}

		//	errorMessage = nullptr;
		//	Error::message(errorMessage);
	}

	//Destructor
	Error::~Error()
	{
		delete[] errorMessage;
	}

	//Thiss Function clears message stored by current object and initializes the object to safe emptystate.
	void Error::clear()
	{
		delete[] errorMessage;
		this->errorMessage = '\0';
		errorMessage = nullptr;
	}

	//This Function returns true if the current object is in safe empty state;
	bool Error::isClear() const
	{
		if (this->errorMessage == '\0')
		{
			return true;
		}
		return false;
	}

	// This Function stores a copy of the CStyled String Pointed to by str;
	void Error::message(const char* str)
	{
		int length = strlen(str);

		delete[] errorMessage;

		if (str != nullptr)
		{
			errorMessage = new char[length + 1];
			strncpy(errorMessage, str, length);

		}
		else if (str == " ")
		{
			this->errorMessage = '\0';
		}
	}

	const char * Error::message() const
	{
		if (this->errorMessage != '\0')
		{
			return errorMessage;
		}
		else
		{
			return nullptr;
		}

	}

	std::ostream& operator<<(std::ostream& ostr, const Error & err)
	{
		if (err.message() == nullptr)
		{
			return ostr;
		}
		else
		{
			ostr << err.message();
			return ostr;
		}
	}

}