#include <string>
#include "iostream"
#include "NetworkManager.h"
#include <conio.h>
#include <thread>

using namespace std;

int userPort;
string connectIP;
string userName;
string tempString;
string sendString;
char* recString = new char[65543];

bool isThreadRunning = true;

void ListenForMessage(NetworkManager* net);
void ShutdownApplication(NetworkManager* net, thread& netThread);

int main()
{
	sendString[0] = '\0';
	recString[0] = '\0';

	cout << "=================" << endl;
	cout << "SKYNET SERVICES" << endl;
	cout << "=================" << endl << endl;

	cout << "Enter your username" << endl;
	cin >> userName;

	cout << "Enter a port to connect on" << endl;
	cin >> userPort;

	cout << endl << "Enter an IP Address to connect to" << endl;
	cin >> connectIP;

	cout << "=================" << endl;

	NetworkManager* NetworkInst = NetworkManager::GetInstance();

	NetworkInst->Init();

	NetworkInst->CreateUDPSockets();
	NetworkInst->BindUDP();
	NetworkInst->SetRemoteData(userPort, connectIP);

	thread listenThread = thread(ListenForMessage, NetworkInst);

	cout << "Type Q To Quit OR Type A Message To Send: " << endl;

	cin.ignore();

	while (true)
	{
		tempString = "";
		sendString = "";

		getline(cin, tempString);

		if (tempString == "Q" || tempString == "q")
		{
			break;
		}

		sendString.append(userName);
		sendString.append(": ");
		sendString.append(tempString);

		cout << sendString << endl;

		NetworkInst->SendData(sendString.c_str());
	}


	ShutdownApplication(NetworkInst, listenThread);
	return 0;
}

void ListenForMessage(NetworkManager* net)
{
	while (isThreadRunning)
	{
		int rcvSize = net->ReceiveData(recString);

		if (rcvSize > 0)
		{
			cout << recString << endl;
		}
	}
}

void ShutdownApplication(NetworkManager* net, thread& netThread)
{
	isThreadRunning = false;
	netThread.join();
	net->Shutdown();
}