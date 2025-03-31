/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:43 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/31 07:15:34 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*******************************************************************************
 *							PRIVATE METHOD 									   *
 ******************************************************************************/

int					PmergeMe::ft_atoi( char *toConvert )
{
	long long	nb;
	int			len;

	nb = 0;
	len = 0;
	if (!toConvert || !*toConvert)
		throw PmergeMe::NoNumericValueInput();
	while (std::isspace(*toConvert))
		toConvert++;
	if (*toConvert == '-')
		throw PmergeMe::NegativeValueInput();
	if (*toConvert == '+')
		toConvert++;
	if (!std::isdigit(*toConvert))
		throw PmergeMe::NoNumericValueInput();
	while (std::isdigit(*toConvert))
	{
		nb = (nb * 10) + (*toConvert - '0');
		toConvert++;
		len++;
	}
	if (nb > INT_MAX || nb < INT_MIN || len > 10)
		throw PmergeMe::NotIntegerValue();
	if (*toConvert)
		throw PmergeMe::NoNumericValueInput();
	return (static_cast<int>(nb));
}

/*******************************************************************************
 *								LIST 										   *
 ******************************************************************************/

std::list<int>		PmergeMe::createList( char **argv, int argc )
{
	int				value;
	std::list<int>	lstToReturn;

	for (int i = 1; i < argc; i++)
	{
		value = -1;
		try
		{
			value = PmergeMe::ft_atoi(argv[i]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return (std::list<int>());
		}
		lstToReturn.push_back(value);
	}
	return (lstToReturn);
}

void				PmergeMe::sortList( std::list<int> &lstToSort )
{
	std::list<std::pair<int, int> >	pairs;
	std::list<int>					sorted;
	std::list<int>					pendings;

	if (lstToSort.size() <= 1)
		return ;
	for (std::list<int>::iterator it = lstToSort.begin(); it != lstToSort.end(); )
	{
		int first = *it;
		++it;
		if (it != lstToSort.end())
		{
			int second = *it;
			++it;
			if (first > second)
				std::swap(first, second);
			pairs.push_back(std::make_pair(first, second));
			sorted.push_back(first);
			pendings.push_back(second);
		}
		else
			sorted.push_back(first);
	}
	sortList(sorted);

	for (std::list<int>::iterator it = pendings.begin(); it != pendings.end(); ++it)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), *it), *it);
	
	lstToSort = sorted;
	return ;
}

void				PmergeMe::printList( const std::list<int> &lstToPrint )
{
	std::list<int>::const_iterator	it;

	if (lstToPrint.empty())
		return ;
	for (it = lstToPrint.begin(); it != lstToPrint.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return ;
}

/*******************************************************************************
 *								VECTOR										   *
 ******************************************************************************/

std::vector<int>	PmergeMe::createVector( char **argv, int argc )
{
	int					value;
	std::vector<int>	vecToReturn;

	for (int i = 1; i < argc; i++)
	{
		value = -1;
		try
		{
			value = PmergeMe::ft_atoi(argv[i]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return (std::vector<int>());
		}
		vecToReturn.push_back(value);
	}
	return (vecToReturn);
}

void				PmergeMe::sortVector( std::vector<int>& vecToSort )
{
	std::vector<std::pair<int, int> >	pairs;
	std::vector<int>					sorted;
	std::vector<int>					pendings;

	if (vecToSort.size() <= 1)
		return;
	for (size_t i = 0; i < vecToSort.size(); i += 2)
	{
		if (i + 1 < vecToSort.size())
		{
			if (vecToSort[i] > vecToSort[i + 1])
				std::swap(vecToSort[i], vecToSort[i + 1]);
			pairs.push_back(std::make_pair(vecToSort[i], vecToSort[i + 1]));
			sorted.push_back(vecToSort[i]);
			pendings.push_back(vecToSort[i + 1]);
		}
		else
			sorted.push_back(vecToSort[i]);
	}
	sortVector(sorted);
	
	for (size_t i = 0; i < pendings.size(); ++i)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), pendings[i]), pendings[i]);
	
	vecToSort.swap(sorted);
	return ;
}

void				PmergeMe::printVector( const std::vector<int> vecToPrint )
{
	if (vecToPrint.empty())
		return ;
	for (size_t i = 0; i < vecToPrint.size(); i++)
		std::cout << vecToPrint[i] << " ";
	std::cout << std::endl;
	return ;
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Exception for not numeric input
 */
const char			*PmergeMe::NoNumericValueInput::what() const throw()
{
	return (RED"Error: no numeric value input"RESET);
}

/*
 *	Exception for negative input value
 */
const char			*PmergeMe::NegativeValueInput::what() const throw()
{
	return (RED"Error: negative value input"RESET);
}

/*
 *	Exception for int overflow input value
 */
const char			*PmergeMe::NotIntegerValue::what() const throw()
{
	return (RED"Error: int overflow value input"RESET);
}