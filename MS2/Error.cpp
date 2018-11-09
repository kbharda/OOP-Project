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
#include "Error.h"

using namespace std;

namespace aid {

	//One Argument Constructor
	Error::Error(const char * errorMessage)
	{
		if (errorMessage == nullptr || errorMessage == "")
		{
			this->errorMessage = '\0';
		}
		else
		{

			int length = std::strlen(errorMessage);
			this->errorMessage = new char[length + 1];
			strncpy(this->errorMessage, errorMessage, length);
			this->errorMessage[length] = '\0';
		}
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
		delete[] this->errorMessage;
		if (str != nullptr && str != "")
		{
			int length = std::strlen(str);
			this->errorMessage = new char[length + 1];
			strncpy(this->errorMessage, str, length);
			this->errorMessage[length] = '\0';

		}
		else
		{
			this->errorMessage = '\0';
		}
	}

	const char * Error::message() const
	{
		if (this->errorMessage != '\0')
		{
			return this->errorMessage;
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