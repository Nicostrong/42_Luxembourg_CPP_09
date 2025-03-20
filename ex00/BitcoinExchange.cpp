/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:03:48 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/20 10:04:56 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
BitcoinExchange::BitcoinExchange( void )
{
	BitcoinExchange::loadData("data.csv" );
	return ;
}

/*
 *	Copy constructor
 */
BitcoinExchange::BitcoinExchange( BitcoinExchange const &src_object )
{
	*this = src_object;
	return ;
}

/*
 *	Destructor
 */
BitcoinExchange::~BitcoinExchange( void )
{
	return ;
}

/*
 *	Assignment operator
 */
BitcoinExchange	&BitcoinExchange::operator=( BitcoinExchange const &src_object )
{
	if (this != &src_object)
		this->_data = src_object._data;
	return (*this);
}


/*******************************************************************************
 *							PRIVATE METHOD 									   *
 ******************************************************************************/

/*
 *	Load data from a file
 */
void			BitcoinExchange::loadData( std::string const &filename )
{
	std::ifstream		file(filename.c_str());
	std::string			line;
	std::string			date;
	double				rate;

	if (!file.is_open())
		throw BitcoinExchange::ErrorOpenFile(filename);
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);
		if (!(std::getline(ss, date, ',') && (ss >> rate)))
		{
			std::cerr << RED << "Warning:\tCSV file with malformed line -> " << line << RESET << std::endl;
			continue;
		}
		if (!BitcoinExchange::isValidDate(date))
		{
			std::cerr << RED << "Warning:\tCSV file with invalid date -> " << date << RESET << std::endl;
			continue;
		}
		this->_data[date] = rate;
	}
	file.close();
	return ;
}

/*
 *	Check if the date format is valid (YYYY-MM-DD) and if the date is valid
 */
bool			BitcoinExchange::isValidDate( const std::string &date ) const
{
	int					year;
	int					month;
	int					day;
	int					maxDays;
	char				dash1;
	char				dash2;
	std::stringstream	ss(date);
	static const int	daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	ss >> year >> dash1 >> month >> dash2 >> day;
	if (ss.fail() || dash1 != '-' || dash2 != '-')
		return (false);
	if (month < 1 || month > 12)
		return (false);
	maxDays = daysInMonth[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		maxDays = 29;
	return (day >= 1 && day <= maxDays);
}

/*
 *	Check if the number of bitcoin is valid
 */
bool			BitcoinExchange::isValidNbrbtc( const std::string &value ) const
{
	double				nbrbtc;
	std::stringstream	ss(value);
	ss >> nbrbtc;
	if (ss.fail() || !ss.eof())
		return (false);
	return (nbrbtc >= 0.0 && nbrbtc <= 1000.0);
}

/*******************************************************************************
 *								METHOD 										   *
 ******************************************************************************/

/*
 *	Get the exchange rate for a given date
 */
double			BitcoinExchange::getExchange( std::string const &date, std::string const &nbrbtc ) const
{
	std::map<std::string, double>::const_iterator	it;
	double											totalValue;
	double											btcAmount;
	std::stringstream								ss(nbrbtc);
	
	if (this->_data.empty())
		throw std::runtime_error(RED"Error:\tNo exchange data available"RESET);
	if (!BitcoinExchange::isValidDate(date))
		throw BitcoinExchange::BadDateInput(date);
	if (!BitcoinExchange::isValidNbrbtc(nbrbtc))
		throw BitcoinExchange::BadValueInput(nbrbtc);
	ss >> btcAmount;
	it = this->_data.lower_bound(date);
	if (it != this->_data.end() && it->first == date)
	{
		totalValue = it->second * btcAmount;
		return (totalValue);
	}
	if (it != this->_data.begin())
	{
		--it;
		totalValue = it->second * btcAmount;
		return (totalValue);
	}
	throw std::runtime_error(RED"Error:\tDate not found"RESET);
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	BadDateInput constructor
 */
BitcoinExchange::BadDateInput::BadDateInput( std::string const &date ) throw()
{
	_msg = RED"Error:\tInvalid date input => " + date + RESET;
	return ;
}

/*
 *	BadDateInput destructor
 */
BitcoinExchange::BadDateInput::~BadDateInput( void ) throw()
{
	return ;
}

/*
 *	Exception BasDateInput	
 */
const char		*BitcoinExchange::BadDateInput::what() const throw()
{
	return  (_msg.c_str());
}

/*
 *	BadValueInput constructor
 */
BitcoinExchange::BadValueInput::BadValueInput( std::string const &value ) throw()
{
	_msg = RED"Error:\tInvalid value input => " + value + RESET;
	return ;
}

/*
 *	BadValueInput destructor
 */
BitcoinExchange::BadValueInput::~BadValueInput( void ) throw()
{
	return ;
}

/*
 *	Exception BadValueInput
 */
const char		*BitcoinExchange::BadValueInput::what() const throw()
{
	return  (_msg.c_str());
}

/*
 *	ErrorOpenFile constructor
 */
BitcoinExchange::ErrorOpenFile::ErrorOpenFile( std::string const &filename ) throw()
{
	_msg = RED"Error:\tCannot open file => " + filename + RESET;
	return ;
}

/*
 *	ErrorOpenFile constructor
 */
BitcoinExchange::ErrorOpenFile::~ErrorOpenFile( void) throw()
{
	return ;
}

/*
 *	Exception ErrorOpenFile
 */
const char		*BitcoinExchange::ErrorOpenFile::what() const throw()
{
	return  (_msg.c_str());
}
