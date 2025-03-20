/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:23:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/20 11:40:51 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int		main(int argc, char **argv)
{
	RPN		rpn;

	if (argc != 2)
	{
		std::cerr	<< RED
					<< "Usage:\t./RPN \"nbr nbr operator nbr operator nbr operator ...\" 0 <= nbr <= 9"
					<< RESET << std::endl;
		return (1);
	}
	try
	{
		std::cout << rpn.evaluate(argv[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;;
	}
	return (0);
}