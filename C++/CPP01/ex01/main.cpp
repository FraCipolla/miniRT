#include "Zombie.hpp"

bool    is_digit(const std::string& str){
    return (str.find_first_not_of("0123456789") == std::string::npos);
}

int	main(){
	std::string	name;
	std::string	size;

	std::cout << "Welcome to this Zombie Horde simulation, insert the size of the Horde and the name of the Zombies!" << std::endl;
	std::cout << "Zombies Name: "; getline(std::cin, name);
	std::cout << "Zombies Number: "; std::cin >> size;
	while (is_digit(size) != 1){
		std::cout << "Invalid Number, please insert only digit!" << std::endl;
		std::cout << "Zombies Number: ";
		std::cin >> size;
	}
	Zombie	*horde = zombieHorde(std::stoi(size), name);
	delete[] horde;
}