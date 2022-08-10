#include "Harl.hpp"
#include <iostream>

void	Harl::complain( std::string level )
{
	void	(Harl::*complaint[])( void ) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	std::string complaintLevels[] = {
		"debug",
		"info",
		"warning",
		"error"
	};
	int c = 3;
	int i;
	switch (c){
		case 0:
			if (level == "DEBUG")
				i = 0;
			break;
		case 1:
			if (level == "INFO")
				i = 1;
			break;
		case 2:
			if (level == "WARNING")
				i = 2;
			break;
		case 3:
			if (level == "ERROR")
				i = 3;
			break;
		default:{
			i = 4;
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
		}
	}
	while (i < 4)
	{
		void (Harl::*selectedComplaint)( void ) = complaint[i];
		if (level == complaintLevels[i])
			(this->*selectedComplaint)();
		i++;
	}
}

void Harl::debug( void ){
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!";
	std::cout << std::endl;
}

void Harl::info( void ){
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!";
	std::cout << std::endl;
}

void Harl::warning( void ){
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.";
	std::cout << std::endl;
}

void Harl::error( void ){
	std::cout << "This is unacceptable! I want to speak to the manager now.";
	std::cout << std::endl;
}