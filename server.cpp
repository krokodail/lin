#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "user.h"
#include "message.h"

using namespace std;
using namespace sf;

int main()
{
	cout << "Server is running on: " << IpAddress::getLocalAddress() << endl;

	
	TcpListener listener;
	
	SocketSelector selector;

	vector<User*> clients;

	listener.listen(55001);
	selector.add(listener);
	
	while(true)
	{
		if(selector.wait())
		{ //Часть отвечающая за создание нового пользователя
		  //Когда есть входящее соединение
		  //И если передан логин и пароль
		  //
		  //Сюда же нужно добавить проверку на существующего с таким именем пользователя
			if(selector.isReady(listener))
			{
				TcpSocket *socket = new TcpSocket;
				
				listener.accept(*socket);
				Packet packet;
				string log, pas;

				if(socket -> receive(packet) == Socket::Done)
				{
					packet >> log >> pas;
					User *usr = new User(log, pas);
					usr -> set_socket(socket);
					
					clients.push_back(usr);
					selector.add(*(usr -> get_socket()));

				}
				
				socket = nullptr;
				delete socket;
				
			}
		//конец 'создания(проверки) пользователя'
			
			//часть проверки запросов от пользователя
			else
			{
				for(int i = 0; i < clients.size(); i++)
				{
					if(selector.isReady(*(clients[i] -> get_socket())))
					{
						Packet packet;
						if(clients[i] -> get_socket() -> receive(packet) == Socket::Done)
						{
							Message message;
							packet >> message;
							if (message._text_message == "list_of_users")
							{
								packet.clear();
								message.clear();

								for(int j = 0; j < clients.size(); j++)
								{
									message._text_message += clients[j] -> get_name() + ' ';
								}
								
								message._sender = "server";
								message._recipient = clients[i] -> get_name();

								packet << message;
								(*clients[i]).get_socket() -> send(packet);
								packet.clear();
							}
							
							if(message._recipient == "all")
							{
								packet << message;

								for(int i = 0; i < clients.size(); i++)
								{
									if((message._sender) == (clients[i] -> get_name())) continue;
									(*clients[i]).get_socket() -> send(packet);
								}

								packet.clear();
							}
							
							if (message._text_message == "delete")
							{//очищает вектор от офлайн юзеров
								for(int i = 0; i < clients.size(); i++)
								{
									if((clients[i] -> get_name()) == message._sender) clients.erase(clients.begin() + i);
									packet.clear();
									message.clear();
									break;
								}
							//Конец очистки
							}
							
							else
							{
								for(int i = 0; i < clients.size(); i++)
								{
									if(message._recipient == clients[i] -> get_name())
									{
										packet.clear();
										packet << message;
										(*clients[i]).get_socket() -> send(packet);
										packet.clear();
										break;
									}
								}

							}
						}
					}
				}
			}
			//Конец проверки запросов пользователя
		}		

	}
			
	return 0;
}
