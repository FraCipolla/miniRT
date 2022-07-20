/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:57:04 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/20 21:55:43 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char *argv[])
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	if (argc > 2)
	{
		for(int	x = 1; x < argc; x++)
			for(size_t i = 0; i < strlen(argv[x]); i++)
				std::cout << (char)toupper(argv[x][i]);
		std::cout << std::endl;
	}
	return (0);
}