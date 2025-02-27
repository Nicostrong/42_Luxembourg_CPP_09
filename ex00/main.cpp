/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:02:56 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/02/27 14:12:35 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int	main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cout << "Usage:\n\t./btc [data_bitcoin].csv" << std::endl;
		return (1);
	}
	std::ifstream	inFile(argv[1]);
	if (!inFile)
	{
		std::cerr << "Error: Unable to read " << argv[1] << std::endl;
		return (1);
	}

	return (0);
}