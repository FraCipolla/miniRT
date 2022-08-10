#include "zombie.hpp"

void	randomChump(std::string name){
	Zombie randomChump = Zombie(name);
	randomChump.announce();
	std::cout << "DON'T LET HIM SURVIVE!!" << std::endl;
}