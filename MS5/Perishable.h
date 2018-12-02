#pragma once

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

#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H

#include <iostream>
#include "Good.h"
#include "Date.h"


namespace aid {

	class Perishable : public Good
	{
		//private data member
	private:

		Date expiryDate;

		//public data member
	public:

		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
}
#endif // !AID_PERISHABLE_H
