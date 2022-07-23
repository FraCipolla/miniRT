#ifndef HEADER_HPP
#define HEADER_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <sstream>

class Contacts{
	private:
	int		index;

	std::string	FirstName;
	std::string	LastName;
	std::string	Nickname;
	std::string	Phone;
	std::string	Secret;

	public:

	// Set
	void		setFirstName(std::istream& str){
		FirstName = str.good();
	}
	void		setLastName(std::istream& str){
		LastName = str.good();
	}
	void		setNickname(std::istream& str){
		Nickname = str.good();
	}
	void		setPhone(std::istream& str){
		Phone = str.good();
	}
	void		setSecret(std::istream& str){
		Secret = str.good();
	}

	// Get
	std::string	get_FirstName(){
		return (FirstName);
	}
	std::string	get_LastName(){
		return (LastName);
	}
	std::string	get_Nickname(){
		return (Nickname);
	}
	std::string get_Phone(){
		return (Phone);
	}
	std::string get_Secret(){
		return (Secret);
	}
};

class PhoneBook{
	public:
		Contacts	contacts[8];
};

#endif