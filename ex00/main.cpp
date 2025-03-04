/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:02:56 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/04 15:53:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main( int argc, char **argv )
{
	std::string	date;
	double		rate;

	if (argc != 2)
	{
		std::cout << "Usage:\n\t./btc [file to evaluate].txt" << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange	btc;
		(void)argv;
		std::cout << "Enter a date to know the rate at this date (YYYY-MM-DD): ";
		std::cin >> date;
		rate = btc.getExchangeRate(date);
		std::cout << "The rate at " << date << " is " << rate << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}