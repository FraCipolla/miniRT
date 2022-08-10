#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <string>
#include <iostream>
#include <fstream>

class Filename{
	private:
		std::fstream	my_file;
		std::fstream	outfile;
		std::string		search;
		std::string		replace;
	public:
		Filename(void);
		~Filename(void);

		bool	set_infile_outfile(std::string in, std::string out);
		void	search_replace(std::string search, std::string replace);
};

#endif