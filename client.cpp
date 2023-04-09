#include <iostream>
#include <string>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

int main()
{

	TcpSocket socket;
	socket.connect("192.168.220.186",55001);
	
	string login, pass;
	Packet packet;

	cout << "Ваш логин: ";
	cin >> login;
	
	cout << "\nВаш пароль: ";
	cin >> pass;
	cout << endl;
	
	packet << login << pass;
	socket.send(packet);
	
	string tmp;

	while(true)
	{
		if(socket.receive(packet) == Socket::Done)
		{
			packet >> tmp;
			cout << "\n" << tmp << "\n";
		}
	}

	return 0;
}
