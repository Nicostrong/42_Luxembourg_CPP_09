/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:23 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/20 16:10:07 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "Usage: ./PmergeMe [nbr1] [nbr2] ... [nbrn]" << std::endl;
		return (1);
	}
	return (0);
}