#include <iostream>
#include <string>
#include "message.h"
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

int main()
{

	TcpSocket socket;
	socket.setBlocking(false);
	socket.connect("192.168.0.149", 55001);
	
	string login(""), pass("");
	Message message;

	Packet packet;

	cout << "Ваш логин: ";
	cin >> login;
	
	cout << "\nВаш пароль: ";
	cin >> pass;
	cout << endl;
	
	message._sender = login;

	packet << login << pass;
	socket.send(packet);
	
	short select(0); // переменная Для switch

	while(true)
	{
		cout << "\n1) Получить список онлайн пользователей\n"
		     << "2) Отправить личное сообщение\n"
		     << "3) Отправить сообщение всем\n"
		     << "Введите номер: ";

		cin >> select;
		cout << endl;

		switch(select)
		{
			case 1:
				{
					packet.clear();
					
					message._text_message = "list_of_users";
					message._recipient = "Server";
					
					packet << message;
					socket.send(packet);
					
					break;
				}
			
			case 2:
				{
					packet.clear();
					
					cout << "\nКому отправим(ник)?: ";
					cin >> message._recipient;
					
					cout << "\nВаше послание?: ";
					cin >> message._text_message;
					
					packet << message;
					socket.send(packet);

					break;
				}
			
			case 3:
				{
					packet.clear();
					
					message._recipient = "all";
					
					cout << "\nВаше послание?: ";
					cin >> message._text_message;
					
					packet << message;
					socket.send(packet);
					break;
				}

			default:
				cout << "Нет такого варианта\n";
				break;
		}
		
		if(socket.receive(packet) == Socket::Done)
		{
			packet >> message;
			cout << message << "\n";
			packet.clear();
		}
	}
	message.clear();
	packet.clear();

	message._sender = login;
	message._recipient = "Server";
	message._text_message = "delete";	
	
	packet << message;	
	socket.send(packet);

	socket.disconnect();

	return 0;
}
