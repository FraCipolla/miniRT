/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:31:13 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/23 17:55:44 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

void	cycle(){
	Contacts	contacts;

	std::cout << "Please, insert the First Name" << std::endl;
	contacts.get_FirstName(std::cin);

}

int	main()
{
	std::string		buff;
	PhoneBook		book;
	int			i;

	i = 0;
	while(1)
	{
		std::cout << "Type ADD to add a contact, Type SEARCH to search a contact, Type EXIT to quit the program" << std::endl;
		std::cin >> buff;
		if (buff.compare("ADD") == 0)
		{
			cycle();
		}
		else if (buff.compare("SEARCH") == 0)
		{
			
		}
		else if (buff.compare("EXIT") == 0)
			return (0);
		else
			std::cout << "WRONG COMMAND, PLEASE TYPE ONE OF THE FOLLOWING: ADD, SEARCH, EXIT" << std::endl;
	}
}