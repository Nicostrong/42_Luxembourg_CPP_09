/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:33 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/28 10:10:53 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <set>
# include <cstdlib>
# include <climits>
# include <exception>
# include <ctime>

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"

class	PmergeMe
{
	private:

		/*	CANONICAL FORM	*/
		PmergeMe( void );
		PmergeMe( PmergeMe const &obj_src );
		~PmergeMe( void );
		PmergeMe				&operator=( PmergeMe const &obj_src );
		
		/*	PRIVATE METHOD	*/
		static int				ft_atoi( char *toConvert );
		
	public:

		/*	LIST	*/
		static std::list<int>	createList( char **argv, int argc );
		static void				sortList( std::list<int> &lstToSort );
		static void				printList( const std::list<int> &lstToPrint );

		/*	VECTOR	*/
		static std::vector<int>	createVector( char **argv, int argc );
		static void				sortVector( std::vector<int>& vecToSort );
		static void				printVector( const std::vector<int> vecToPrint );
	
		/*	Exception for not numeric input	*/
		class	NoNumericValueInput: public std::exception
		{

				public:

					const char	*what() const throw();

		};

		/*	Exception for negative input value */
		class	NegativeValueInput: public std::exception
		{

				public:

					const char	*what() const throw();

		};

		/*	Exception for int overflow input value */
		class	NotIntegerValue: public std::exception
		{

				public:

					const char	*what() const throw();

		};
};

#endif