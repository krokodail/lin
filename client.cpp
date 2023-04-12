#include <iostream>
#include <string>
#include <csignal>
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
		cout << "Для получения ответа на запрос или проверки входящих выберите 4-ый вариант"
		     << "\n1) Получить список онлайн пользователей\n"
		     << "2) Отправить личное сообщение\n"
		     << "3) Отправить сообщение всем\n"
		     << "4) Проверить входящие сообщения\n"
		     << "5) Выход(Закрыть приложение)\n"
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
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, message._text_message);
					
					packet << message;
					socket.send(packet);

					break;
				}
			
			case 3:
				{
					packet.clear();
					
					message._recipient = "all";
					
					cout << "\nВаше послание?: ";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, message._text_message);
					
					packet << message;
					socket.send(packet);
					break;
				}
			
			case 4:
				{
					if(socket.receive(packet) == Socket::Done)
					{
						packet >> message;
						cout  <<  message << "\n";
						packet.clear();
						message.clear();
					}
					else cout << "\nВходящих пока не было\n";
					
					break;
				}

			case 5:
				{
					packet.clear();
					
					message._text_message = "delete";
					message._recipient = "Server";
					
					packet << message;
					socket.send(packet);
					socket.disconnect();

					return 0;
				}

			default:
				cout << "Нет такого варианта\n";
				break;
		}
		
	}
	
	return 0;
}
