/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:23 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/21 14:21:03 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::list<int>	ft_sort( std::list<int> *listToSort)
{
	std::list<int>	listSorted;

	listSorted.push_back((*listToSort).front());
	(*listToSort).pop_front();
	if (listSorted.front() > (*listToSort).front())
		listSorted.push_front((*listToSort).front());
	else
		listSorted.push_back((*listToSort).front());
	(*listToSort).pop_front();

	std::cout << "List sorted" << std::endl;
	std::list<int>::iterator	it;
	for (it = listSorted.begin(); it != listSorted.end(); it++)
		std::cout << *it << " / ";
	std::cout << std::endl;
	return (listSorted);
}

int		main(int argc, char **argv)
{
	std::list<int>	toSort;
	std::list<int>	lst1;
	std::list<int>	lst2;
	std::list<int>	lst3;
	std::list<int>	lst4;

	if (argc == 1)
	{
		std::cerr << "Usage: ./PmergeMe [nbr1] [nbr2] ... [nbrn]" << std::endl;
		return (1);
	}
	for (int i = 1; i < argc; i++)
		toSort.push_back(atoi(argv[i]));

	std::cout << "List to sort" << std::endl;
	std::list<int>::iterator	it;
	for (it = toSort.begin(); it != toSort.end(); it++)
		std::cout << *it << " / ";
	std::cout << std::endl;
	lst1 = ft_sort(&toSort);
	lst2 = ft_sort(&toSort);
	lst3 = ft_sort(&toSort);
	return (0);
}