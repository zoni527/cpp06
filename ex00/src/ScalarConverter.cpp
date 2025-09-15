/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:20:23 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/15 15:16:08 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cassert>
#include <cmath>

using std::string;
using std::cout;

enum	LiteralType : unsigned int
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	UNKNOWN,
};

static LiteralType	checkLiteralType( string const &str );
static bool			isCharacterLiteral( string const &str );
static bool			isIntLiteral( string const &str );
static bool			isFloatLiteral( string const &str );
static bool			isDoubleLiteral( string const &str );

void	ScalarConverter:: convert( string const &str )
{
	static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required for nan and infinity");

	LiteralType	type = checkLiteralType( str );
	if ( type == UNKNOWN )
	{
		cout << "Not a valid literal" << std::endl;
		return;
	}

	char	c = '\0',	*cPtr = nullptr;
	int		i = +0,		*iPtr = nullptr;
	float	f = 0.f,	*fPtr = nullptr;
	double	d = -.0,	*dPtr = nullptr;

	switch ( type )
	{
		case CHAR:
			cout << "Literal is a char";
			if ( str.size() == 3 )
				c = str[1];
			else
				c = str[0];
			i = static_cast<int>( c );
			iPtr = &i;
			f = static_cast<float>( c );
			fPtr = &f;
			d = static_cast<double>( c );
			dPtr = &d;
			break;
		case INT:
			cout << "Literal is an int";
			i = std::stoi( str );
			iPtr = &i;
			if ( i >= 0 && i <= 127 )
			{
				c = static_cast<char>( i );
				cPtr = &c;
			}
			f = static_cast<float>( i );
			fPtr = &f;
			d = static_cast<double>( i );
			dPtr = &d;
			break;
		case FLOAT:
			cout << "Literal is a float";
			if ( str.find( "inff" ) != string::npos )
			{
				if ( str.find( "-" ) != string::npos )
					f = -std::numeric_limits<float>::infinity();
				else
					f = std::numeric_limits<float>::infinity();
			}
			else if ( str.find( "nanf" ) != string::npos )
				f = std::numeric_limits<float>::quiet_NaN();
			else
				f = std::stof( str );
			fPtr = &f;
			d = static_cast<double>( f );
			dPtr = &d;
			if ( std::floor( f ) <= static_cast<float>( std::numeric_limits<int>::max() )
				&& std::floor( f ) >= static_cast<float>( std::numeric_limits<int>::min() ) )
			{
				i = static_cast<int>( std::floor( f ) );
				iPtr = &i;
			}
			if ( std::floor( f ) >= 0 && std::floor( f ) <= 127 )
			{
				c = static_cast<char>( std::floor( f ) );
				cPtr = &c;
			}
			break;
		case DOUBLE:
			cout << "Literal is a double";
			if ( str.find( "inf" ) != string::npos )
			{
				if ( str.find( "-" ) != string::npos )
					d = -std::numeric_limits<double>::infinity();
				else
					d = std::numeric_limits<double>::infinity();
			}
			else if ( str.find( "nan" ) != string::npos )
				d = std::numeric_limits<double>::quiet_NaN();
			else
				d = std::stod( str );
			dPtr = &d;
			if ( std::floor( d ) <= static_cast<double>( std::numeric_limits<float>::max() )
				&& std::floor( d ) >= static_cast<double>( std::numeric_limits<float>::min() ) )
			{
				f = static_cast<float>( d );
				fPtr = &f;
			}
			if ( std::floor( d ) <= static_cast<double>( std::numeric_limits<int>::max() )
				&& std::floor( d ) >= static_cast<double>( std::numeric_limits<int>::min() ) )
			{
				i = static_cast<int>( std::floor( d ) );
				iPtr = &i;
			}
			if ( std::floor( d ) >= 0 && std::floor( d ) <= 127 )
			{
				c = static_cast<char>( std::floor( d ) );
				cPtr = &c;
			}
			break;
		default :
			;
	}
	cout << std::endl;
	cout << "char: ";
	if ( cPtr )
		cout << c << "\n";
	else
		cout << "impossible" << "\n";
	cout << "int: ";
	if ( iPtr )
		cout << i << "\n";
	else
		cout << "impossible" << "\n";
	cout << "float: ";
	if ( fPtr )
		cout << f << "f\n";
	else
		cout << "impossible" << "\n";
	cout << "double: ";
	if ( dPtr )
		cout << d << "\n";
	else
		cout << "impossible" << "\n";
	cout << std::endl;
}

static LiteralType	checkLiteralType( string const &str )
{
	if ( str.empty() )
		return UNKNOWN;
	if ( isCharacterLiteral( str ) )
		return CHAR;
	if ( isIntLiteral( str ) )
		return INT;
	if ( isFloatLiteral( str ) )
		return FLOAT;
	if ( isDoubleLiteral( str ) )
		return DOUBLE;
	return UNKNOWN;
}

/**
 * Valid character literals: a, '1', 'a'
 */
static bool	isCharacterLiteral( string const &str )
{
	if ( str.size() > 3 || str.size() == 2 )
		return false;
	if (	str.size() == 3
			&& str[0] == '\''
			&& str[2] == '\''
			&& ( str[1] >= 0 && str[1] <= 127 ) )
		return true;
	if (	str.size() == 1
			&& !std::isdigit( str[0] )
			&& ( str[0] >= 0 && str[0] <= 127 ) )
		return true;
	return false;
}

/**
 * Valid int literals: +123, -456, 01, +001, -002
 */
static bool	isIntLiteral( string const &str )
{
	auto	i = str.begin();
	if ( *i == '+' || *i == '-' )
		++i;
	if ( i == str.end() || !std::isdigit( *( i++ ) ) )
		return false;
	for ( ; i != str.end(); ++i )
	{
		if ( !std::isdigit( *i ) )
			return false;
	}
	try
	{
		std::stoi( str );
	}
	catch ( std::exception const &e )
	{
		return false;
	}
	return true;
}

static bool	isDoubleLiteral( string const &str )
{
	bool	hasWholelPart		= false;
	bool	hasFractionalPart	= false;
	auto	i = str.begin();
	if ( *i == '+' || *i == '-' )	// Optional sign
		++i;
	auto	rest = string( i, str.end() );
	if ( rest == "inf" || str == "nan" )	// Pseudo-literals
		return true;
	if ( std::isdigit( *i ) )		// Possible whole part
		hasWholelPart = true;
	while ( i != str.end() && std::isdigit( *i ) )	// Skip digits
		++i;
	if ( i == str.end() || *i != '.' )	// Double literals need a dot
		return false;
	++i;
	if ( i != str.end() && std::isdigit( *i ) )	// Possible whole part
		hasFractionalPart = true;
	while ( i != str.end() && std::isdigit( *i ) )	// Skip digits
		++i;
	// Number must end and have digits at either or both sides of the dot
	if ( i != str.end() || ( !hasWholelPart && !hasFractionalPart ) )
		return false;
	try
	{
		std::stod( str );	// Does number fit in a double?
	}
	catch ( std::exception const &e )
	{
		return false;
	}
	return true;
}

/**
 * Valid float literals: 1.0f, .0f, 1.f
 */
static bool	isFloatLiteral( string const &str )
{
	if ( *( str.end() - 1 ) != 'f' )	// Float literals must end with and f
		return false;
	auto	doublePart = string( str.begin(), str.end() - 1 );	// Cut off f
	if ( !isDoubleLiteral( doublePart ) )
		return false;
	try
	{
		std::stof( str );	// Does number fit in a float?
	}
	catch ( std::exception const &e )
	{
		return false;
	}
	return true;
}
