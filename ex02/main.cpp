/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:23 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/25 09:12:33 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
 *	1) verifier le nombre d arguments
 *	2) lire les arguments et les enregistrer dans une list
 *	3) lire les arguments et les enregistrer dans un vecteur
 *	4) Afficher la liste initiale
 *	5) lancer le chrono
 *	6) trier la list
 *	7) arreter le chrono et afficher la liste avec le temps
 *	8) Afficher le vecteur initiale
 *	9) lancer le chrono
 *	10) trier le vecteur
 *	11) arreter le chrono et afficher le vecteuravec le temps
 */
int		main(int argc, char **argv)
{
	std::list<int>		lstToSort;
	std::vector<int>	vecToSort;

	//	check number of arguments
	if (argc == 1)
	{
		std::cerr << "Usage: ./PmergeMe [nbr1] [nbr2] ... [nbrn]" << std::endl;
		return (1);
	}
	//	put arg on list
	lstToSort = PmergeMe::createList(&argv, argc);

	//	put args on vector
	vecToSort = PmergeMe::createVector(argv, argc);

	//	print initial list
	PmergeMe::printList(lstToSort);
	//	print initial vector
	PmergeMe::printVector(vecToSort);

	return (0);
}