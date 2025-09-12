/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2025/09/11 16:20:23 by jvarila           #+#    #+#             */ /*   Updated: 2025/09/11 18:26:28 by jvarila          ###   ########.fr       */ /*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

enum	LiteralType : unsigned int
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	UNKNOWN,
};

using string = std::string;

static LiteralType	checkLiteralType( string const &str );
bool				isCharacterLiteral( string const &str );
bool				isIntLiteral( string const &str );
bool				isFloatLiteral( string const &str );
bool				isDoubleLiteral( string const &str );

void	ScalarConverter:: convert( string const &str )
{
	LiteralType	type = checkLiteralType( str );
}

static LiteralType	checkLiteralType( string const &str )
{
	if ( str.empty() )
		return UNKNOWN;
	if ( isCharacterLiteral( str ))
		return CHAR;
	return UNKNOWN;
}

/**
 * Valid character literals: a, '1', 'a'
 */
bool	isCharacterLiteral( string const &str )
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
bool	isIntLiteral( string const &str )
{
	auto	i = str.begin();
	if ( *i == '+' || *i == '-' )
		++i;
	if ( i == str.end() || !std::isdigit( *(i++)) )
		return false;
	for ( ; i != str.end(); ++i )
	{
		if ( !std::isdigit( *i ) )
			return false;
	}
	return true;
}

bool	isFloatLiteral( string const &str )
{
	bool	hasWholelPart		= false;
	bool	hasFractionalPart	= false;
	if ( *( str.end() - 1 ) != 'f' )
		return false;
	auto	i = str.begin();
	if ( *i == '+' || *i == '-' )
		++i;
	if ( i == str.end() )
		return false;
	if ( std::isdigit( *i ) )
		hasWholelPart = true;
	while ( i != str.end() && std::isdigit( *i ) )
		++i;
	if ( i == str.end() || *i != '.' )
		return false;
	++i;
	if ( i != str.end() && std::isdigit( *i ) )
		hasFractionalPart = true;
	while ( i != str.end() && std::isdigit( *i ) )
		++i;
	if ( i + 2 != str.end() || ( !hasWholelPart && !hasFractionalPart ) )
		return false;
	return true;
}

