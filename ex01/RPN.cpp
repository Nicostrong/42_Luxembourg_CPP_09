/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:18:32 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/20 15:57:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*******************************************************************************
 *							CANONICAL FORM									   *
 ******************************************************************************/

/*
 *	Default constructor
 */
RPN::RPN( void )
{
	return ;
}

/*
 *	Copy constructor
 */
RPN::RPN( RPN const &src_object )
{
	*this = src_object;
	return ;
}

/*
 *	Destructor
 */
RPN::~RPN( void )
{
	return ;
}

/*
 *	Assignment constructor
 */
RPN		&RPN::operator=( RPN const &src_object )
{
	if (this != &src_object)
		this->_stack = src_object._stack;
	return (*this);
}

/*******************************************************************************
 *							PRIVATE METHOD 									   *
 ******************************************************************************/

/*
 *	check if the token evaluated is an operator
 */
bool	RPN::isOperator( const std::string &token ) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

/*
 *	check if the value is an interger between 0 and 9 included
 */
bool	RPN::isValidValue( const int value ) const
{
	return (value >= 0 && value <= 9);
}

/*
 *	Apply the operator to the two last values in the stack
 */
void	RPN::applyOperator( const std::string &op )
{
	if (this->_stack.size() < 2)
		throw NotEnougtOperands();
	if (!isOperator(op))
		throw BadOperator();
	int		second;
	int		first;

	second = this->_stack.top();
	this->_stack.pop();
	first = this->_stack.top();
	this->_stack.pop();
	if (op == "+")
		this->_stack.push(first + second);
	else if (op == "-")
		this->_stack.push(first - second);
	else if (op == "*")
		this->_stack.push(first * second);
	else if (op == "/")
	{
		if (second == 0)
			throw DivByZero();
		this->_stack.push(first / second);
	}
	return ;
}

/*
 *	Process a token number or operator
 */
void	RPN::processToken( const std::string &token )
{
	std::stringstream	ss(token);
	int					value;

	if (ss >> value && ss.eof())
	{
		if (!isValidValue(value))
			throw BadValue();
		this->_stack.push(value);
	}
	else if (isOperator(token))
		applyOperator(token);
	else
		throw BadArg();
	return ;
}

/*******************************************************************************
 *								METHOD 										   *
 ******************************************************************************/

int			RPN::evaluate( const std::string &expression )
{
	std::istringstream	iss(expression);
	std::string			token;

	while (iss >> token)
		processToken(token);
	if (_stack.size() != 1)
		throw BadArg();
	return (_stack.top());
}

/*******************************************************************************
 *								EXCEPTION 									   *
 ******************************************************************************/

/*
 *	Division by zero exception
 */
const char	*RPN::DivByZero::what() const throw()
{
	return (RED"Error:\tDivision by zero."RESET);
}

/*
 *	Bad operator exception
 */
const char	*RPN::BadOperator::what() const throw()
{
	return (RED"Error:\tBad operator => [+, -, *, /]."RESET);
}

/*
 *	Bad value exception
 */
const char	*RPN::BadValue::what() const throw()
{
	return (RED"Error:\tBad value => [o ; 9]."RESET);
}

/*
 *	Not enougt operands exception
 */
const char	*RPN::NotEnougtOperands::what() const throw()
{
	return (RED"Error:\tNot enougt operands."RESET);
}

/*
 *	Bad argument exception
 */
const char	*RPN::BadArg::what() const throw()
{
	return (RED"Error:\tBad argument number."RESET);
}