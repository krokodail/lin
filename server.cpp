#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "user.h"

using namespace std;
using namespace sf;

int main()
{
	cout << "Server is running on: " << IpAddress::getLocalAddress() << endl;

	
	TcpListener listener;
	SocketSelector selector;

	vector<User*> clients;

	listener.getLocalPort();
	listener.listen(55001);

	selector.add(listener);
	
	while(true)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				//Тут идея такая, что сделал промежуточный сокет
				//Чтобы получить пакет и построить класс пользователь
				//Из данных, что пришли в пакете
				TcpSocket * socket = new TcpSocket;
				
				Packet packet;
				
				string log, pas;

				socket -> receive(packet);
				packet >> log >> pas;
				delete socket;

				User *person = new User(log, pas);

				listener.accept(*((*person).get_socket()));
				
				
			/*	if(socket -> receive(packet) == Socket::Done)
				{	
					
					packet >> tmp;
					packet << tmp;
					for (vector<TcpSocket*>::iterator it = clients.begin();it != clients.end();it++)
					{
						(*it) -> send(packet);
					}
				}  */

				cout << "\nClient's connection: " << (*(person -> get_socket())).getLocalPort() << endl;
				clients.push_back(person);
				selector.add(*(person->get_socket()));
			}
//Вот тут буду смотреть пришли ли сообщения от клиента
//и кому они направлены(всем или определенному лицу)
//Сообщения будут отправляться с указанием от кого и кому

			for (vector<User*>::iterator it = clients.begin();it != clients.end();it++);
		}
	}
	
	for (vector<User*>::iterator it = clients.begin();it != clients.end();it++) delete *it;
	
	return 0;
}
