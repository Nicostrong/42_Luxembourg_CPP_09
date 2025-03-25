/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:33 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/25 09:21:35 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <cstdlib>
# include <climits>
# include <exception>

# define RESET		"\033[0m"
# define RED		"\033[31m"

class   PmergeMe
{
	private:

		/*	PRIVATE METHOD	*/
		int		ft_atoi( std::string *toConvert );
		
		/*	LIST	*/
		std::list<int>			makeElementList( std::list<int> &lstToGroup );
		
		/*	VECTOR	*/
		std::vector<int>		makeElementVector( std::vector<int> &vecToGroup );

	
	public:

		/*	LIST	*/
		static std::list<int>	createList( char **argv, int argc );
		static void				sortList( std::list<int> &lstToSort );
		static void				printList( const std::list<int> &lstToPrint );

		/*	VECTOR	*/
		static std::vector<int>	createVector( char **argv, int argc );
		static void				sortVector( std::vector<int>& vecToSort );
		static void				printVector( const std::vector<int> vecToPrint );
	
		/*	Valid input integer positif	*/
		class	BadValueInput: public std::exception
		{

				public:

					const char	*what() const throw();

		};

};

#endif