// Final Project Milestone 5
//
// Version 1.0
// Date 11/29/2018
// Author Kashyap Bharda (140622176)
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
		m_error.clear();
	}

	// this function calls its base class version inserts a comma into the file record and appends the expiry date to the file record.
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Good::store(file, false);
		file << ',';
		file << expiryDate;
		file << endl;

		return file;
	}

	// this functions calls its base class version passing as an argument, loads the expiry date, extracts a single character from the fstream object.
	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);
		file >> expiryDate;
		file.ignore();

		return file;
	}

	// Function does nothing if the current object is an error or safe empty state
	// if linear is true, adds the expiry date on the same line for an outcome that
	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		os.fill(' '); //Fill white spaces or 0(zeros) required for submitter
		Good::write(os, linear);

		if (isClear() && !isEmpty()) {

			if (linear == true)
			{
				expiryDate.write(os);
			}
			else
			{
				os << endl;
				os << " Expiry date: ";
				expiryDate.write(os);
			}
		}
		return os;
	}


	//This function will validate the base class object and prompt for expire date to be store.
	//In a temporary Date object d date object is also an eeror state it will store the appropiate
	
	std::istream& Perishable::read(std::istream& is)
	{
		Date tempDate;
		Good::read(is);

		if (is.good())
		{
			std::cout << " Expiry date (YYYY/MM/DD): ";
			tempDate.read(is);

			if (tempDate.bad() == true)
			{
				is.setstate(std::ios::failbit);

				switch (tempDate.errCode())
				{
				case CIN_FAILED:
					message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					message("Invalid Day in Date Entry");
					break;
				case PAST_ERROR:
					message("Invalid Expiry in Date Entry");
				}
			}
			else
			{
				expiryDate = tempDate;
			}
		}
		return is;
	}

	//Function returns the expiry date for the perishable good.
	const Date& Perishable::expiry() const
	{
		return expiryDate;
	}
}
