/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:43 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/25 09:44:23 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*******************************************************************************
 *							PRIVATE METHOD 									   *
 ******************************************************************************/

int		ft_atoi( char *toConvert )
{
	
	char		*s;
	long long	nb;

	nb = 0;
	while (std::isspace(*toConvert))
		toConvert++;
	if (*toConvert == '-' || *s == '+')
		toConvert++;
	while (std::isdigit(*toConvert))
	{
		nb = (nb * 10) + (*toConvert - '0');
		toConvert++;
	}
	if (nb > INT_MAX || nb < INT_MIN)
		return (-1);
	return ((int)nb);
}

/*******************************************************************************
 *							PRIVATE LIST									   *
 ******************************************************************************/

std::list<int>			makeElementList( std::list<int> &lstToGroup );



/*******************************************************************************
 *							PRIVATE VECTOR									   *
 ******************************************************************************/

std::vector<int>		makeElementVector( std::vector<int> &vecToGroup );


/*******************************************************************************
 *								LIST 										   *
 ******************************************************************************/

static std::list<int>	createList( char **argv, int argc )
{
	std::list<int>	lstToReturn;
	int				value;

	for (size_t i = 1; i < argc; i++)
	{
		value = -1;
		value = ft_atoi(argv[i]);
		if (value < 0)
			throw PmergeMe::BadValueInput();
		lstToReturn.push_back(value);
	}
	return (lstToReturn);
}

static void	sortList( std::list<int> &lstToSort )
{
	std::list<int>	sorted;
	std::list<int>	pendings;

	if (lstToSort.size() <= 1)
		return;

	for (std::list<int>::iterator it = lstToSort.begin(); it != lstToSort.end(); )
	{
		int first = *it;
		++it;
		if (it != lstToSort.end())
		{
			int second = *it;
			++it;
			if (first > second) std::swap(first, second);
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

static void				printList( const std::list<int> &lstToPrint )
{
	std::list<int>::iterator	it;

	for (it = lstToPrint.begin(); it != lstToPrint.end(); it++)
		std::cout << *it << " / ";
	std::cout << std::endl;
	return ;
}


/*******************************************************************************
 *								VECTOR										   *
 ******************************************************************************/

static std::vector<int>	createVector( char **argv, int argc );

static void				sortVector( std::vector<int>& vecToSort )
{
	std::vector<int> sorted;
	std::vector<int> pendings;

	if (vecToSort.size() <= 1)
		return;

	for (size_t i = 0; i < vecToSort.size(); i += 2)
	{
		if (i + 1 < vecToSort.size())
		{
			if (vecToSort[i] > vecToSort[i + 1])
				std::swap(vecToSort[i], vecToSort[i + 1]);
			sorted.push_back(vecToSort[i]);
			pendings.push_back(vecToSort[i + 1]);
		}
		else
			sorted.push_back(vecToSort[i]);
	}
	sortVector(sorted);
	
	for (size_t i = 0; i < pendings.size(); ++i)
		sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), pendings[i]), pendings[i]);
	
	vecToSort = sorted;
	return ;
}

static void				printVector( const std::vector<int> vecToPrint );
	
/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

const char	*PmergeMe::BadValueInput::what() const throw()
{
	return (RED"Error: bad value input"RESET);
}