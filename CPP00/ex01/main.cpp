/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 21:31:13 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/20 21:52:30 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <iostream>

using namespace std;

int	main()
{
	char		*buff;
	PhoneBook	book;
	int			i;

	i = 0;
	while(1)
	{
		cout << "Type ADD to add a contact, Type SEARCH to search a contact, Type EXIT to quit the program" << endl;
		cin >> buff;
		if (strcmp(buff, "ADD") == 0)
		{
			cout << "Please, type FIRST NAME: ";
			cin >> book.contacts[i].name;
			cout << "Please, type LAST NAME: ";
			cin >> book.contacts[i].lastname;
			cout << "Please, type NICKNAME: ";
			cin >> book.contacts[i].nickname;
			cout << "Please, type PHONE NUMBER: ";
			cin >> book.contacts[i].number;
			cout << "Please, type DARKEST SECRET: ";
			cin >> book.contacts[i].secret;
			if (i == 7)
				i = 0;
			else
				i++;
		}
		else if (strcmp(buff, "SEARCH") == 0)
		{
			
		}
		else if (strcmp(buff, "EXIT") == 0)
		{
			cout << "See you next time, have a nice day!!" << endl;
			break ;
		}
		else
			cout << "WRONG COMMAND, PLEASE TYPE ONE OF THE FOLLOWING: ADD, SEARCH, EXIT" << endl;
	}
}