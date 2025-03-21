/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:23 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/21 11:24:15 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int		main(int argc, char **argv)
{
	std::list<int>	toSort;

	if (argc == 1)
	{
		std::cerr << "Usage: ./PmergeMe [nbr1] [nbr2] ... [nbrn]" << std::endl;
		return (1);
	}
	for (int i = 0; i < argc; i++)
		toSort.push_back(atoi(argv[i + 1]));
	
	std::list<int>::iterator	it;
	for (it = toSort.begin(); it != toSort.end(); it++)
		std::cout << *it << " / ";
	std::cout << std::endl;
	return (0);
}