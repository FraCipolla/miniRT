#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>

class Harl{
	private:
		void debug( void );
		void info( void );
		void warning( void );
		void error( void );
	public:
		enum filterLevel {
			levelError = 0,
			levelWarning,
			levelInfo,
			levelDebug,
		};
		void complain( std::string level );
};

#endif