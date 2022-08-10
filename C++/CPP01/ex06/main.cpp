#include "Harl.hpp"

int main(int argc, char **argv){
	Harl harl;

	if (argc != 2){
		std::cout << "invalid arguments" << std::endl;
	}
	harl.complain(argv[1]);
}
