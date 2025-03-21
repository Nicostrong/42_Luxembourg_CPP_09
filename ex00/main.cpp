/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:02:56 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/20 09:53:44 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	readInputFile( const std::string &filename, BitcoinExchange &btc )
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
	{
		std::cerr << RED << "Error:\tCannot open input file => " << filename << RESET << std::endl;
		return ;
	}
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::string		date;
		std::string		value;
		std::stringstream	ss(line);

		if (!(std::getline(ss, date, '|') && std::getline(ss, value)))
		{
			std::cerr << RED << "Error:\tInvalid format in line => " << line << RESET << std::endl;
			continue ;
		}
		date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
		try
		{
			double	totalValue;

			totalValue = btc.getExchange(date, value);
			std::cout << GREEN << date << " => " << value << " = " << totalValue << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
}

int	main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cout << GREEN << "Usage:\n\t./btc [file to evaluate].txt" << RESET << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange	btc;
		readInputFile(argv[1], btc);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
