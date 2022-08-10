#include "zombie.hpp"

Zombie::Zombie( void ){
}

void	Zombie::announce(void) const{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::~Zombie(void){
	std::cout << name << ": I'm dying...again!" << std::endl;
}

void	Zombie::setName( std::string newName ){
	name = newName;
}

std::string	Zombie::getName( void ) const
{
	return (name);
}