#pragma once
#include <string>

class User final
{
	private:
		unsigned _id_user = 0;
		std::string	_name_user;
		std::string	_pass_user;
	
	public:
		User() = default;
		User(std::string, std::string, unsigned);
		unsigned get_id() const;
		std::string get_name() const;

};
