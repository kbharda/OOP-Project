#pragma once

// Final Project Milestone 3
//
// Version 1.0
// Date 11/30/2018
// Author Kashyap Bharda (140622176)
// Description A class that manages a non-perishable good object.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#ifndef AID_GOOD_H
#define AID_GOOD_H

#include <iostream>
#include <fstream>
#include "iGood.h"
#include "Error.h"

namespace aid {

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good : public iGood{

		//Private data members
	private:
		char m_goodType;
		char m_sku[max_sku_length + 1];
		char m_unit[max_unit_length + 1];
		char* m_name;
		int m_quantityOnHand;
		int m_quantityNeeded;
		double m_priceTaxesPre;
		bool m_taxable;
		

	protected:
	//protected Member Functions
		Error m_error;
		
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:

		//public Mmber Functions;

		Good(char type = 'N');
		Good(const char* sku, const char*nameGood, const char* unit, int quantityOnHand = 0, bool taxable = true, double priceTaxesPre = 0.0, int quantityNeeded = 0);
		Good(const Good& good);
		Good& operator=(const Good& good);
		~Good();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		void itemPrice(double);
		void needed(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int type() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);
	};

	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);

	double operator+=(double&, const iGood&);
}

#endif // !AID_GOOD_H
