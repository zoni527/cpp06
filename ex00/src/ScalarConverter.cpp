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
#include <cassert>
#include <cmath>
#include <iomanip>

enum	LiteralType : unsigned int
{
	UNKNOWN,
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
};

static LiteralType	checkLiteralType( std::string const &str );
static bool			isCharLiteral( std::string const &str );
static bool			isIntLiteral( std::string const &str );
static bool			isFloatLiteral( std::string const &str );
static bool			isDoubleLiteral( std::string const &str );
static void			convertChar( std::string const &str );
static void			convertInt( std::string const &str );
static void			convertFloat( std::string const &str );
static void			convertDouble( std::string const &str );

char	c = '\0',	*cPtr = nullptr;
int		i = +0,		*iPtr = nullptr;
float	f = 0.f,	*fPtr = nullptr;
double	d = -.0,	*dPtr = nullptr;

void	ScalarConverter:: convert( std::string const &str )
{
	static_assert( std::numeric_limits<float>::is_iec559, "IEEE 754 required for nan and infinity" );

	LiteralType	type = checkLiteralType( str );
	switch ( type )
	{
		case CHAR:
			convertChar( str );
			break;
		case INT:
			convertInt( str );
			break;
		case FLOAT:
			convertFloat( str );
			break;
		case DOUBLE:
			convertDouble( str );
			break;
		default :
			std::cout << "Not a valid literal" << std::endl;
			return;
	}

	std::cout << "char: ";
	if ( cPtr && std::isprint( c ) )
		std::cout << c << "\n";
	else if ( cPtr && c >= 0 && c <= 127 )
		std::cout << "Non displayable" << "\n";
	else
		std::cout << "impossible" << "\n";
	std::cout << "int: ";
	if ( iPtr )
		std::cout << i << "\n";
	else
		std::cout << "impossible" << "\n";
	std::cout << "float: ";
	if ( fPtr )
		std::cout << std::fixed << std::setprecision( 1 ) << f << "f\n";
	else
		std::cout << "impossible" << "\n";
	std::cout << "double: ";
	if ( dPtr )
		std::cout << std::fixed << std::setprecision( 1 ) << d << "\n";
	else
		std::cout << "impossible" << "\n";
}

static LiteralType	checkLiteralType( std::string const &str )
{
	if ( str.empty() )
		return UNKNOWN;
	if ( isCharLiteral( str ) )
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
static bool	isCharLiteral( std::string const &str )
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
static bool	isIntLiteral( std::string const &str )
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

static bool	isDoubleLiteral( std::string const &str )
{
	bool	hasWholelPart		= false;
	bool	hasFractionalPart	= false;
	auto	i = str.begin();
	if ( *i == '+' || *i == '-' )	// Optional sign
		++i;
	auto	rest = std::string( i, str.end() );
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
static bool	isFloatLiteral( std::string const &str )
{
	if ( *( str.end() - 1 ) != 'f' )	// Float literals must end with and f
		return false;
	auto	doublePart = std::string( str.begin(), str.end() - 1 );	// Cut off f
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

static void	convertChar( std::string const & str )
{
	if ( str.size() == 3 )
		c = str[1];
	else
		c = str[0];
	cPtr = &c;
	i = static_cast<int>( c );
	iPtr = &i;
	f = static_cast<float>( c );
	fPtr = &f;
	d = static_cast<double>( c );
	dPtr = &d;
}

static void	convertInt( std::string const & str )
{
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
}

static void	convertFloat( std::string const & str )
{
	f = std::stof( str );
	fPtr = &f;
	d = static_cast<double>( f );
	dPtr = &d;
	if ( std::trunc( f ) <= static_cast<float>( std::numeric_limits<int>::max() )
		&& std::trunc( f ) >= static_cast<float>( std::numeric_limits<int>::min() ) )
	{
		i = static_cast<int>( std::trunc( f ) );
		iPtr = &i;
	}
	if ( std::trunc( f ) >= 0 && std::trunc( f ) <= 127 )
	{
		c = static_cast<char>( std::trunc( f ) );
		cPtr = &c;
	}
}

static void	convertDouble( std::string const & str )
{
	d = std::stod( str );
	if ( str == "nan" )
	{
		f = std::numeric_limits<float>::quiet_NaN();
		fPtr = &f;
	}
	if ( str.find( "inf" ) != std::string::npos )
	{
		f = std::numeric_limits<float>::infinity();
		if ( str.find( "-" ) != std::string::npos )
			f = -f;
		fPtr = &f;
	}
	dPtr = &d;
	if ( d <= static_cast<double>( std::numeric_limits<float>::max() )
		&& d >= static_cast<double>( std::numeric_limits<float>::lowest() ) )
	{
		f = static_cast<float>( d );
		fPtr = &f;
	}
	if ( std::trunc( d ) <= static_cast<double>( std::numeric_limits<int>::max() )
		&& std::trunc( d ) >= static_cast<double>( std::numeric_limits<int>::min() ) )
	{
		i = static_cast<int>( std::trunc( d ) );
		iPtr = &i;
	}
	if ( std::trunc( d ) >= 0 && std::trunc( d ) <= 127 )
	{
		c = static_cast<char>( std::trunc( d ) );
		cPtr = &c;
	}
}
