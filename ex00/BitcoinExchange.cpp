/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:03:48 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/04 15:52:10 by nfordoxc         ###   Luxembourg.lu     */
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
	loadData("data.csv" );
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
	{
		this->_data = src_object._data;
	}
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
		if (std::getline(ss, date, ',') && (ss >> rate))
			_data[date] = rate;
		if (!isValidDate(date))
		{
			throw BitcoinExchange::BadDateInput(date);
			continue;
		}
	}
	file.close();

}

/*
 *	Check if the date format is valid (YYYY-MM-DD)
 */
bool			BitcoinExchange::isValidDate(const std::string &date) const
{
	int					year;
	int					month;
	int					day;
	char				dash1;
	char				dash2;
	std::stringstream	ss(date);

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	ss >> year >> dash1 >> month >> dash2 >> day;
	if (ss.fail() || dash1 != '-' || dash2 != '-')
		return (false);
	if (year < 2000 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);

	return (true);
}

/*******************************************************************************
 *								METHOD 										   *
 ******************************************************************************/

/*
 *	Get the exchange rate for a given date
 */
double			BitcoinExchange::getExchangeRate( std::string const &date ) const
{
	std::map<std::string, double>::const_iterator	it;
	
	it = _data.lower_bound(date);
	if (it != _data.end() && it->first == date)
		return (it->second);
	if (it != _data.begin())
	{
		--it;
		return (it->second);
	}
	throw std::runtime_error("Date not found");
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
 *	Exception ErrorOpenFile
 */
const char		*BitcoinExchange::ErrorOpenFile::what() const throw()
{
	return  (_msg.c_str());
}