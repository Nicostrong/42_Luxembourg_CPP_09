/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:33 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/24 10:23:26 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <cstdlib>
# include <exception>

# define RESET		"\033[0m"
# define RED		"\033[31m"

class   PmergeMe
{
	private:

		/*	LIST	*/
		std::list<int>			makeElementList( std::list<int> &lstToGroup );
		
		/*	VECTOR	*/
		std::vector<int>		makeElementVector( std::vector<int> &vecToGroup );

	
	public:

		/*	LIST	*/
		static std::list<int>	createList( std::string argv[] );
		static std::list<int>	sortList( const std::list<int> &lstToSort );
		static void				printList( const std::list<int> &lstToPrint );

		/*	VECTOR	*/
		static std::vector<int>	createVector( std::string argv[] );
		static std::vector<int>	sortVector( const std::vector<int> vecToSort );
		static void				printVector( const std::vector<int> vecToPrint );
	
		/*	Valid input integer positif	*/
		class	BadValueInput: public std::exception
		{

				public:

					const char	*what() const throw();

		};

};

#endif