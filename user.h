#pragma once
#include <string>
#include <SFML/Network.hpp>

class User final
{
	private:
		std::string	_name_user;
		std::string	_pass_user;
		sf::TcpSocket _socket;
	
	public:
		User(std::string, std::string);
		std::string get_name() const;
		sf::TcpSocket* get_socket() ;

};
