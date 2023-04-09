#include <iostream>
#include <string>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

void entrance(TcpSocket& sock)
{
	string login, pass;
	
	cout << "Ваш логин: ";
	cin >> login;
	
	cout << "\nВаш пароль: ";
	cin >> pass;
	
	Packet packet;
	packet << login << pass;
	
	sock.send(packet);

	return;
}

int main()
{
	//Подключаемся к серверу
	//Просим выбрать \"войти/зарегистрироваться\"
	//После, отправляем данные на сервер для проверки

	TcpSocket socket;
	socket.connect("192.168.220.186",55001);
	
	entrance(socket);
	
	return 0;
}
