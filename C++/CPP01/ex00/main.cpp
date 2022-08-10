#include "Zombie.hpp"

int	main(){
	std::cout << "A WILD ZOMBIE \"manually\" APPEARS!" << std::endl;
	{
		Zombie	robert("Robert");
		robert.announce();
		std::cout << "FAST! KILL HIM!!" << std::endl;
	}
	std::cout << "ANOTHER ZOMBIE IS APPEARING!, using the function"
		" newZombie"<< std::endl;
	{
		Zombie	*georges = newZombie("Georges");
		georges->announce();
		std::cout << "DON'T STOP SHOOTING!!" << std::endl;
		delete georges;
	}
	{
		std::cout << "A THIRD ONE IS COMING! using the function"
			" randomChump"<< std::endl;
		randomChump("Mark");
	}
	std::cout << "GG GUYS, we survived this time!!" << std::endl;
}