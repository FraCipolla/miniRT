#include "replace.hpp"

int	main(int argc, char **argv){

	Filename	file;
	if (argc != 4){
		std::cout << "Invalid arguments" << std::endl;
		return (0);
	}
	if (!file.set_infile_outfile(argv[1], "outfile.txt")){
		std::cout << "Invalid arguments" << std::endl;
		return (0);
		}
	file.search_replace(argv[2], argv[3]);
}