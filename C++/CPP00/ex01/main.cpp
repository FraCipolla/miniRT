#include "phone.hpp"

std::string	return_str(std::string str){
	if (str.length() < 11){
		for (int i = str.length(); i < 10; i++)
			str.insert(0, " ");
		return (str);
	}
	else{
		str = str.substr(0, 9);
		str.push_back('.');
		return (str);
	}
}

void	cycle(Contacts *phone){
	
	std::string	buff;

	std::cout << "First Name: "; std::cin.ignore(); getline(std::cin, buff); phone->setFirstName(buff);
	std::cout << "Last Name: "; getline(std::cin, buff); phone->setLastName(buff);
	std::cout << "NickName: "; getline(std::cin, buff); phone->setNickName(buff);
	std::cout << "Phone Number: "; std::cin >> buff; 
	while (is_digit(buff) != 1){
		std::cout << "Invalid Number, please insert only digit!" << std::endl;
		std::cout << "Phone Number: ";
		std::cin >> buff;
	}
	phone->setPhone(buff);
	std::cout << "Secret: "; std::cin.ignore(); getline(std::cin, buff); phone->setSecret(buff);
}

void	display_contact(Contacts *contact){
	std::cout << "First Name: " << contact->get_FirstName() << std::endl;
	std::cout << "Last Name: " << contact->get_LastName() << std::endl;
	std::cout << "NickName: " << contact->get_Nickname() << std::endl;
	std::cout << "Phone Number: " << contact->get_Phone() << std::endl;
}

void	search_print(PhoneBook *phone, Contacts *contacts){
	if (contacts->get_n_contcts() == 0){
		std::cout << "No contacts to display, please run ADD before!" << std::endl;
		return ;
	}
	for (int i = 0; i < contacts->get_n_contcts() & i < 8; i++){
		std::cout << "Index: "; std::cout << i; std::cout << "  |";
		std::cout << return_str(phone->phone_book[i].get_FirstName()); std::cout << "|";
		std::cout << return_str(phone->phone_book[i].get_LastName()); std::cout << "|";
		std::cout << return_str(phone->phone_book[i].get_Nickname());
		std::cout << std::endl;
	}
	std::string	buff;
	int	i;

	while (1){
		std::cout << "Insert the desired index or type EXIT to quit : ";
		std::cin >> buff;
		if (buff == "EXIT"){
			break ;
		}
		else if (isdigit(buff[0])){
			i = std::stoi(buff);
			if (i <= contacts->get_n_contcts() & (i >= 0 & i <= 7)){
				std::cout << "ENTRA" << std::endl;
				display_contact(&phone->phone_book[i]);
				break ;
			}
		}
		std::cout << "Invalid Input"; std::cout << std::endl;
	}
}

int	main()
{
	std::string	buff;
	PhoneBook	phone;
	Contacts	contacts;
	int			i;

	i = 0;
	while(1)
	{
		std::cout << "Type ADD to add a contact, Type SEARCH to search a contact, Type EXIT to quit the program" << std::endl;
		std::cout << "> ";
		std::cin >> buff;
		if (buff == "ADD")
		{
			cycle(&phone.phone_book[phone.index]);
			contacts.increase_contact_n();
			if (phone.index == 7)
				phone.index = 0;
			else
				phone.index++;
		}
		else if (buff == "SEARCH")
		{
			search_print(&phone, &contacts);
		}
		else if (buff == "EXIT")
			return (0);
		else
			std::cout << "WRONG COMMAND, PLEASE TYPE ONE OF THE FOLLOWING: ADD, SEARCH, EXIT" << std::endl;
	}
}
