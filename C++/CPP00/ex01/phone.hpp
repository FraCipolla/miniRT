#ifndef HEADER_HPP
#define HEADER_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <sstream>

class Contacts{
	private:
    int n_contacts = 0;
	std::string	FirstName;
	std::string	LastName;
	std::string	Nickname;
	std::string	Phone;
	std::string	Secret;

	public:

	// Set
    void    increase_contact_n(){
        if (n_contacts < 8)
            n_contacts += 1;
    }
	void		setFirstName(std::string& str){
		FirstName = str;
	}
	void		setLastName(std::string& str){
		LastName = str;
	}
	void		setNickName(std::string& str){
		Nickname = str;
	}
	void		setPhone(std::string& str){
		Phone = str;
	}
	void		setSecret(std::string& str){
		Secret = str;
	}

	// Get
    int get_n_contcts(){
        return (n_contacts);
    }
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
		Contacts	phone_book[8];
        int         index = 0;
};

bool    is_digit(const std::string& str){
    return (str.find_first_not_of("0123456789") == std::string::npos);
}

#endif