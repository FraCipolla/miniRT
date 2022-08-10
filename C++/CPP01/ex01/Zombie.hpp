#ifndef ZOMBIE_HPP
#define	ZOMBIE_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <sstream>
# include <vector>

class	Zombie{
	private:
		std::string	name;
	public:
		Zombie(void);
		~Zombie(void);

		void	announce( void ) const;
		std::string	getName( void ) const;
		void		setName( std::string newName );
};

Zombie* zombieHorde( int N, std::string name );

#endif