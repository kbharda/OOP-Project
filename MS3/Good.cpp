
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

	void Good::name(const char* nameGood) {

		if (nameGood == nullptr)
		{
			this->m_name = nullptr;
		}
		else
		{
			this->m_name = new char[max_name_length + 1];
			strncpy(m_name, nameGood, max_name_length + 1);
			this->m_name[max_name_length] = '\0';
		}

	}
	const char* Good::name() const
	{
		return this->m_name;
	}
	const char* Good::sku() const
	{
		return this->m_sku;
	}
	const char * Good::unit() const
	{
		return this->m_unit;
	}
	bool Good::taxed() const
	{
		return this->m_taxable;
	}
	double Good::itemPrice() const
	{
		return this->m_priceTaxesPre;
	}
	double Good::itemCost() const
	{
		if (m_taxable)
		{
			return m_priceTaxesPre + (m_priceTaxesPre*tax_rate);
		}
		else
		{
			return m_priceTaxesPre;
		}

	}
	void Good::message(const char* errorMessage)
	{
		this->m_errorState.message(errorMessage);
	}

	bool Good::isClear() const
	{
		if (m_errorState.isClear() == NULL)
		{
			return true;
		}
		return false;
	}
	// One argument Constructor
	Good::Good(char type)
	{
		this->m_goodType = type;
		this->m_sku[0] = '\0';
		this->m_unit[0] = '\0';
		this->m_name = nullptr;
		this->m_quantityOnHand = 0;
		this->m_quantityNeeded = 0;
		this->m_priceTaxesPre = 0.0;
		this->m_taxable = false;
	}
	// Seven Argument Constructor
	Good::Good(const char * sku, const char * nameGood, const char * unit, int quantityOnHand, bool taxable, double priceTaxesPre, int quantityNeeded)
	{
		strcpy(m_sku, sku);
		name(nameGood);
		strcpy(m_unit, unit);
		m_quantityOnHand = quantityOnHand;
		m_taxable = taxable;
		m_priceTaxesPre = priceTaxesPre;
		m_quantityNeeded = quantityNeeded;
	}
	// Copy Constructor
	Good::Good(const Good& good)
	{
		if (good.m_name != '\0')
		{
			name(good.m_name);
		}

		strcpy(m_sku, good.m_sku);
		strcpy(m_unit, good.m_unit);
		strncpy(m_name, good.m_name, max_name_length + 1);

		this->m_quantityOnHand = good.m_quantityOnHand;
		this->m_quantityNeeded = good.m_quantityNeeded;
		this->m_priceTaxesPre = good.m_priceTaxesPre;
		this->m_taxable = good.m_taxable;
	}
	// Copy Assignment Operator.
	Good& Good::operator=(const Good& good)
	{
		// TODO: insert return statement here
		if (this != &good)// Self Assignment Check
		{
			strcpy(m_sku, good.m_sku);
			strcpy(m_unit, good.m_unit);

			this->m_quantityOnHand = good.m_quantityOnHand;
			this->m_quantityNeeded = good.m_quantityNeeded;
			this->m_priceTaxesPre = good.m_priceTaxesPre;
			this->m_taxable = good.m_taxable;

			delete[] m_name;
			name(good.m_name);
		}

		return *this;
	}
	// Destructor deallocates memory
	Good::~Good()
	{
		delete[] m_name;
	}

	std::fstream& Good::store(std::fstream& file, bool newLine) const
	{
		// TODO: insert return statement here

		file << m_goodType << ", "
			<< m_name << ", "
			<< m_taxable << ", "
			<< m_priceTaxesPre << ", "
			<< m_quantityOnHand << ", "
			<< m_quantityNeeded;

		if (newLine)
		{
			file << endl;
		}
		return file;
	}

	std::fstream& Good::load(std::fstream& file)
	{
		// TODO: insert return statement here

		Good temp;
		temp.m_name = new char[max_name_length + 1];

		if (file.is_open())
		{
			file >> temp.m_goodType
				>> temp.m_sku
				>> temp.m_unit
				>> temp.m_name
				>> temp.m_quantityOnHand
				>> temp.m_quantityNeeded
				>> temp.m_priceTaxesPre
				>> temp.m_taxable;

			*this = temp;
		}

		delete[] temp.m_name;
		temp.m_name = nullptr;

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		// TODO: insert return statement here

		if (linear)
		{
			os << setw(max_sku_length) << left << m_sku << "|"
				<< setw(20) << left << m_name << "|"
				<< setw(7) << right << fixed << setprecision(2) << itemCost() << "|"
				<< setw(4) << right << m_quantityOnHand << "|"
				<< setw(10) << left << m_unit << "|"
				<< setw(4) << right << m_quantityNeeded << "|";
		}
		else
		{
			os << "Sku: " << m_sku << "|" << endl
				<< "Name: " << m_name << "|" << endl
				<< "Price: " << m_priceTaxesPre << "|" << endl;
			if (m_taxable)
			{
				os << "Price after tax: " << itemCost() << "|" << endl;
			}
			else
			{
				os << "N/A" << "|" << endl;
			}
			os << "Quantity on hand: " << m_quantityOnHand << "|" << endl
				<< "Quantity needed: " << m_quantityNeeded << "|" << endl;
		}
		return os;
	}

	std::istream& Good::read(std::istream& is)
	{
		// TODO: insert return statement here
		char f_sku[max_sku_length + 1];
		char* f_name = new char[max_name_length + 1];
		char f_unit[max_unit_length + 1];
		int f_quantityOnHand;
		int f_quantityNeeded;
		int f_priceTaxesPre;
		char f_taxed;
		bool f_taxable;
		Error f_errorState;

		cout << " Sku: ";
		is >> f_sku;
		cout << " Name (no spaces): ";
		is >> f_name;
		cout << " Unit: ";
		is >> f_unit;
		cout << " Taxed? (y/n): ";
		is >> f_taxed;

		if (f_taxed == 'y' || f_taxed == 'Y')
		{
			f_taxable = true;
		}
		else if (f_taxed == 'n' || f_taxed == 'N')
		{
			f_taxable = false;
		}
		else
		{
			is.setstate(std::ios::failbit); //Input- Output stream error State flag set for operation faileed.
			f_errorState.message("Only (Y)es or (N)o are acceptable");
		}

		if (!is.fail())
		{
			cout << " Price: ";
			is >> f_priceTaxesPre;
			if (is.fail())
			{
				f_errorState.message("Invalid Price Entry");
			}
		}

		if (!is.fail())
		{
			cout << " Quatinty on hand: ";
			is >> f_quantityOnHand;
			if (is.fail())
			{
				f_errorState.message("Invalid Quantity Entry");
			}
		}

		if (!is.fail())
		{
			cout << "Quatinty needed: ";
			is >> f_quantityNeeded;
			if (is.fail())
			{
				f_errorState.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail())
		{
			Good t = Good(f_sku, f_name, f_unit, f_quantityNeeded, f_quantityOnHand, f_taxable, f_priceTaxesPre);
			*this = t;
		}

		delete[] f_name;
		f_name = nullptr;
		return is;
	}

	bool Good::operator==(const char* sku) const
	{
		if (strcmp(sku, m_sku) == 0)
		{
			return true;
		}
		return false;
	}

	double Good::total_cost() const
	{
		double totalCost;

		if (m_taxable)
		{
			totalCost = m_quantityOnHand * m_priceTaxesPre * (1 + tax_rate);
		}
		else
		{
			totalCost = m_quantityOnHand * m_priceTaxesPre;
		}

		return totalCost;
	}

	void Good::quantity(int qtyGoodOnHand)
	{
		if (qtyGoodOnHand > 0)
		{
			m_quantityOnHand = qtyGoodOnHand;
		}
	}


	bool Good::isEmpty() const
	{
		if (m_name[0] == '\0')
		{
			return true;
		}
		return false;
	}

	int Good::qtyNeeded() const
	{
		return this->m_quantityNeeded;
	}

	int Good::quantity() const
	{
		return this->m_quantityOnHand;
	}

	bool Good::operator>(const char* sku) const
	{
		if (strcmp(m_sku, sku) > 0)
		{
			return true;
		}
		return false;
	}

	bool Good::operator>(const Good& good) const
	{
		if (strcmp(m_name, good.m_name) > 0)
		{
			return true;
		}
		return false;
	}

	int Good::operator+=(int quantityAdded)
	{
		if (quantityAdded > 0)
		{
			m_quantityOnHand += quantityAdded;
			return m_quantityOnHand;
		}
		else
		{
			return m_quantityOnHand;
		}

	}

	std::ostream& operator<<(std::ostream& ostr, const Good& good)
	{
		// TODO: insert return statement here
		good.write(ostr, true);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Good& good)
	{
		// TODO: insert return statement here
		good.read(istr);
		return istr;
	}

	double operator+=(double& totalCost, const Good& good)
	{
		totalCost += good.total_cost();
		return totalCost;
	}
}