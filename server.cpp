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

	vector<TcpSocket*> clients;
	vector<User*> user;

	listener.getLocalPort();
	listener.listen(55001);

	selector.add(listener);
	
	while(true)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				TcpSocket * socket = new TcpSocket;
				listener.accept(*socket);
				
				Packet packet;
				socket -> receive(packet);

				cout << "\nClient's connection: " << socket -> getLocalPort() << endl;
				clients.push_back(socket);
				selector.add(*socket);
				
				string log, pas;
				packet >> log >> pas;
				User *usr = new User(log, pas, user.size());
				user.push_back(usr);
				cout << "log: " << usr -> get_name() << endl << "Id: " << usr -> get_id() << endl;

			}
		}
	}
	
	for (vector<TcpSocket*>::iterator it = clients.begin();it != clients.end();it++) delete *it;
	
	for (vector<User*>::iterator it = user.begin();it != user.end();it++) delete *it;

	return 0;
}
