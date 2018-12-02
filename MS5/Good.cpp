
// Final Project Milestone 5
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
			delete[] m_name;
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
		if (m_name != nullptr)
		{
			return this->m_name;
		}
		else
		{
			return nullptr;
		}

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
		if (errorMessage != nullptr)
		{
			m_error.message(errorMessage);
		}
	}

	bool Good::isClear() const
	{
		return this->m_error.isClear();
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
		bool notnull = sku != nullptr && nameGood != nullptr && unit != nullptr;

		if (notnull)
		{
			strncpy(m_sku, sku, strlen(sku));
			m_sku[strlen(sku)] = '\0';

			Good::name(nameGood);

			strncpy(m_unit, unit, strlen(unit));
			m_unit[strlen(unit)] = '\0';
		}

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
		this->m_taxable = good.m_taxable;
		this->m_priceTaxesPre = good.m_priceTaxesPre;
		this->m_quantityNeeded = good.m_quantityNeeded;


	}
	// Copy Assignment Operator.
	Good& Good::operator=(const Good& good)
	{
		// TODO: insert return statement here
		if (this != &good)// Self Assignment Check
		{
			int skuu = strlen(good.m_sku);
			int unitt = strlen(good.m_unit);

			this->m_goodType = good.m_goodType;
			this->m_quantityOnHand = good.m_quantityOnHand;
			this->m_quantityNeeded = good.m_quantityNeeded;
			this->m_priceTaxesPre = good.m_priceTaxesPre;
			this->m_taxable = good.m_taxable;

			name(good.m_name);

			strncpy(m_sku, good.m_sku, skuu);
			m_sku[skuu] = '\0';

			strncpy(m_unit, good.m_unit, unitt);
			m_unit[unitt] = '\0';
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

		file << m_goodType << ","
			<< m_sku << ","
			<< m_name << ","
			<< m_unit << ","
			<< m_taxable << ","
			<< m_priceTaxesPre << ","
			<< m_quantityOnHand << ","
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

		char f_sku[max_sku_length + 1];
		char* f_name = new char[max_name_length + 1];
		char f_unit[max_unit_length + 1];
		int f_qtyOnHand;
		int f_qtyNeeded;
		double f_pricePreTax;
		char f_taxed;
		bool f_taxable;
		Good load;

		if (file.is_open())
		{
			file.getline(f_sku, max_sku_length, ',');
			f_sku[strlen(f_sku)] = '\0';

			file.getline(f_name, max_name_length, ',');
			f_name[strlen(f_name)] = '\0';

			file.getline(f_unit, max_unit_length, ',');
			f_unit[strlen(f_unit)] = '\0';

			file >> f_taxed;

			if (f_taxed == '0')
			{
				f_taxable = false;
			}
			else
			{
				f_taxable = true;
			}

			file.ignore();

			file >> f_pricePreTax;
			file.ignore();

			file >> f_qtyOnHand;
			file.ignore();

			file >> f_qtyNeeded;
			file.ignore();

			load = Good(f_sku, f_name, f_unit, f_qtyOnHand, f_taxable, f_pricePreTax, f_qtyNeeded);

			*this = load;
		}

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (!(m_error.isClear()))
		{
			os << m_error.message();
		}

		else if (linear)
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
			os << " Sku: " << m_sku << endl
				<< " Name (no spaces): " << m_name << endl
				<< " Price: " << m_priceTaxesPre << endl;
			if (m_taxable)
			{
				os << " Price after tax: " << itemCost() << endl;
			}
			else
			{
				os << " Price after tax: " << " N/A" << endl;
			}
			os << " Quantity on Hand: " << m_quantityOnHand << " " << m_unit << endl
				<< " Quantity needed: " << m_quantityNeeded << endl;
		}
		return os;
	}

	std::istream& Good::read(std::istream& is)
	{
		char taxes;
		char* addres = new char[max_name_length + 1];
		int quantity;
		int neededQty;
		double price;

		if (!is.fail())
		{
			cout << " Sku: ";
			is >> m_sku;
			cin.ignore();

			cout << " Name (no spaces): ";
			is >> addres;
			name(addres);

			cout << " Unit: ";
			is >> m_unit;

			cout << " Taxed? (y/n): ";
			is >> taxes;


			if (!is.fail())
			{
				m_error.clear();

				if (taxes)
				{
					bool valid = taxes == 'y' || taxes == 'Y';
					bool not_valid = taxes == 'n' || taxes == 'N';

					if (valid)
					{
						m_taxable = true;
					}
					if (not_valid)
					{
						m_taxable = false;
					}

					if (!(valid || not_valid))
					{
						is.setstate(std::ios::failbit);
						m_error.message("Only (Y)es or (N)o are acceptable");
						return is;
					}
				}
			}
			else {
				is.setstate(std::ios::failbit);
				m_error.message("Only (Y)es or (N)o are acceptable");
				return is;
			}

			/*while (valid)
			{
				cout << " Taxed? (y/n): ";
				is >> f_taxed;

				if (f_taxed == 'y' || f_taxed == 'Y' || f_taxed == 'n' || f_taxed == 'N')
				{
					if (f_taxed == 'n' || f_taxed == 'N')
					{
						f_taxable = false;
					}
					else
					{
						f_taxable = true;
					}
					break;
				}
				else
				{
					valid = false;
					is.setstate(std::ios::failbit);
					message("Only (Y)es or (N)o are acceptable");
					break;
				}
			}*/

			cout << " Price: ";
			is >> price;

			if (is.fail())
			{
				m_error.clear();
				is.setstate(std::ios::failbit);
				m_error.message("Invalid Price Entry");
				return is;
			}
			else
			{
				itemPrice(price);
			}

			cout << " Quantity on hand: ";
			is >> quantity;

			if (is.fail())
			{
				m_error.clear();
				m_error.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else
			{
				Good::quantity(quantity);
			}

			cout << " Quantity needed: ";
			is >> neededQty;
			cin.ignore();

			if (is.fail())
			{
				m_error.clear();
				m_error.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else
			{
				needed(neededQty);
			}

			if (!is.fail())
			{
				m_error.clear();
			}
		}
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

	void Good::itemPrice(double iprice)
	{
		m_priceTaxesPre = iprice;
	}

	void Good::needed(int needqty)
	{
		m_quantityNeeded = needqty;
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

	int Good::type() const
	{
		return m_goodType;
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

	bool Good::operator>(const iGood& good) const
	{
		if (strcmp(m_name, good.name()) > 0)
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

	std::ostream& operator<<(std::ostream& ostr, const iGood& good)
	{
		// TODO: insert return statement here
		good.write(ostr, true);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, iGood& good)
	{
		// TODO: insert return statement here
		good.read(istr);
		return istr;
	}

	double operator+=(double& totalCost, const iGood& good)
	{
		totalCost += good.total_cost();
		return totalCost;
	}
}