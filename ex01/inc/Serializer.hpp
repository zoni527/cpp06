/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:56:29 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/16 12:23:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>

class Data;

class Serializer
{
public:
	Serializer( void ) = delete;
	Serializer( Serializer const &other ) = delete;
	~Serializer( void ) = default;

	Serializer	&operator=( Serializer const &rhs ) = delete;

	static uintptr_t	serialize( Data *ptr );
	static Data			*deserialize( uintptr_t raw );
};
