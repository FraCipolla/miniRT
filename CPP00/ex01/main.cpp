/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:31:13 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/24 18:13:13 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

void	cycle(){
	Contacts	contacts;

	std::cout << "First Name: ";
	contacts.setFirstName(std::cin);
	// std::cout << "FIRST NAME: " << str << std::endl;

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
		if (buff == "ADD")
		{
			cycle();
		}
		else if (buff == "SEARCH")
		{
			
		}
		else if (buff == "EXIT")
			return (0);
		else
			std::cout << "WRONG COMMAND, PLEASE TYPE ONE OF THE FOLLOWING: ADD, SEARCH, EXIT" << std::endl;
	}
}