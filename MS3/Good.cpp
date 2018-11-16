// Final Project Milestone 2
//
// Version 1.0
// Date 11/21/2018
// Author Kashyap Bharda
// Description A class that manages a non-perishable good object.
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

#include "Good.h"
#include "Error.h"

using namespace std;

namespace aid {

	void Good::name(const char*) {

	}
	const char * Good::name() const
	{
		return nullptr;
	}
	const char * Good::sku() const
	{
		return nullptr;
	}
	const char * Good::unit() const
	{
		return nullptr;
	}
	bool Good::taxed() const
	{
		return false;
	}
	double Good::itemPrice() const
	{
		return 0.0;
	}
	double Good::itemCost() const
	{
		return 0.0;
	}
	void Good::message(const char *)
	{

	}

	bool Good::isClear() const
	{
		return false;
	}

	Good::Good(char type)
	{

	}
	Good::Good(const char * sku, const char * nameGood, const char * unit, int quantityOnHand, bool taxable, double priceTaxesPre, int quantityNeeded)
	{

	}

	Good::Good(const Good & good)
	{

	}

	Good & Good::operator=(const Good & good)
	{
		// TODO: insert return statement here
	}

	Good::~Good()
	{

	}

	std::fstream & Good::store(std::fstream & file, bool newLine) const
	{
		// TODO: insert return statement here
	}

	std::fstream & Good::load(std::fstream & file)
	{
		// TODO: insert return statement here
	}

	std::ostream & Good::write(std::ostream & os, bool linear) const
	{
		// TODO: insert return statement here
	}

	std::istream & Good::read(std::istream & is)
	{
		// TODO: insert return statement here
	}

	bool Good::operator==(const char *) const
	{
		return false;
	}

	double Good::total_cost() const
	{
		return 0.0;
	}

	void Good::quantity(int)
	{
	}

	bool Good::isEmpty() const
	{
		return false;
	}

	int Good::qtyNeeded() const
	{
		return 0;
	}

	int Good::quantity() const
	{
		return 0;
	}

	bool Good::operator>(const char *) const
	{
		return false;
	}

	bool Good::operator>(const Good &) const
	{
		return false;
	}

	int Good::operator+=(int)
	{
		return 0;
	}

	std::ostream & operator<<(std::ostream &, const Good &)
	{
		// TODO: insert return statement here
	}

	std::istream & operator>>(std::istream &, Good &)
	{
		// TODO: insert return statement here
	}

	double operator+=(double &, const Good &)
	{
		return 0.0;
	}

}