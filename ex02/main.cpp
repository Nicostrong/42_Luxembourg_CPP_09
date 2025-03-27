/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:23 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/27 17:23:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
 *	print all argument 
 *	sort all argument passed in argument with the Ford-Johnson algorithme
 */
int		main(int argc, char **argv)
{
	std::list<int>		lstArg;
	std::list<int>		lstToSort;
	std::vector<int>	vecToSort;
	clock_t				lstStartChrono;
	clock_t				lstEndChrono;
	clock_t				vecStartChrono;
	clock_t				vecEndChrono;

	if (argc == 1)
	{
		std::cerr << "Usage: ./PmergeMe [nbr1] [nbr2] ... [nbrn]" << std::endl;
		return (1);
	}
	lstArg = PmergeMe::createList(argv, argc);
	if (lstArg.empty())
		return (1);
	/*	Print initial values	*/
	std::cout << GREEN << "Initial value to sort :\t" << RESET;
	PmergeMe::printList(lstArg);

	/*	Creation and sorting with list	*/
	lstStartChrono = clock();
	lstToSort = PmergeMe::createList(argv, argc);
	if (lstToSort.empty())
		return (1);
	PmergeMe::sortList(lstToSort);
	lstEndChrono = clock();

	/*	Creation and sorting with vector	*/
	vecStartChrono = clock();
	vecToSort = PmergeMe::createVector(argv, argc);
	if (vecToSort.empty())
		return (1);
	PmergeMe::sortVector(vecToSort);
	vecEndChrono = clock();

	/*	Print sorted value	*/
	std::cout << YELLOW << "Sorted value :\t" << RESET;
	/*
	 *	You can check if the sort with list or vector is correct.
	 *	Uncomment the result you want to check.
	 *	Comment the other line
	 */
	PmergeMe::printList(lstToSort);
	//PmergeMe::printVector(vecToSort);

	/*	Printing result of time using to sort	*/
	std::cout	<< YELLOW
				<< "Time to sort with list : "
				<< (double)(lstEndChrono - lstStartChrono) * 1000 / CLOCKS_PER_SEC
				<< " ms"
				<< RESET << std::endl;
	std::cout	<< BLUE
				<< "Time to sort with vector : "
				<< (double)(vecEndChrono - vecStartChrono) * 1000 / CLOCKS_PER_SEC
				<< " ms"
				<< RESET << std::endl;
	
	return (0);
}