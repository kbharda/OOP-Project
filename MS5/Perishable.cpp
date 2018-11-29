// Final Project Milestone 5
//
// Version 1.0
// Date 11/29/2018
// Author Kashyap Bharda
// Description A class that manages a perishable good object. This class inherits the structure of the “Good” class and manages a date.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Perishable.h"
#include "Date.h"

using namespace std;

namespace aid {

	// No argument constructor
	Perishable::Perishable() : Good('P')
	{

	}

	// calls its base class version inserts a comma into the file record and appends the expiry date to the file record.
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Good::store(file, false);
		file << ',';
		file << m_ExpiryDate;
		;
		file << endl;

		return file;
	}

	// calls its base class version passing as an argument, loads the expiry date, extracts a single character from the fstream object.
	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);
		file >> m_ExpiryDate;
		file.ignore();

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		os.fill(' '); // Require ffor fill the white space
		Good::write(os, linear);

	}
}
