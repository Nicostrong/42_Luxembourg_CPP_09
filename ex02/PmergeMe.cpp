/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:43 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/24 13:10:32 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*******************************************************************************
 *							PRIVATE METHOD 									   *
 ******************************************************************************/

int		ft_atoi( std::string *toConvert )
{
	
	char		*s;
	long long	nb;

	s = (char *)toConvert->c_str();
	nb = 0;
	while (std::isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (std::isdigit(*s))
	{
		nb = (nb * 10) + (*s - '0');
		s++;
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

static std::list<int>	createList( std::string argv[], int &argc )
{
	std::list<int>	lstToReturn;
	int				value;

	for (size_t i = 1; i < argc; i++)
	{
		value = -1;
		value = ft_atoi(&argv[i]);
		if (value < 0)
			throw PmergeMe::BadValueInput();
		lstToReturn.push_back(value);
	}
	return (lstToReturn);
}

static std::list<int>	sortList( const std::list<int> &lstToSort );
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

static std::vector<int>	createVector( std::string argv[], int &argc );
static std::vector<int>	sortVector( const std::vector<int> vecToSort );
static void				printVector( const std::vector<int> vecToPrint );
	
/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

const char	*PmergeMe::BadValueInput::what() const throw()
{
	return (RED"Error: bad value input"RESET);
}