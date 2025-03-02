/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:03:48 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/02/28 14:28:49 by nfordoxc         ###   Luxembourg.lu     */
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
 *								METHOD 										   *
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
		throw std::runtime_error("Cannot open file.csv");
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);
		if (std::getline(ss, date, ',') && (ss >> rate))
			_data[date] = rate;
	}
	file.close();

}

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