#include <string>
#include "iostream"
#include "NetworkManager.h"
#include <conio.h>

using namespace std;

int userPort;
string connectIP;
string userName;

int main()
{
	//Send String Vars
	string sendString;
	sendString[0] = '\0';

	//Rec String Vars
	char* recString = new char[65543];
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

	cout << "Type Q To Quit OR Type A Message To Send: " << endl;

	while (true)
	{

		cin >> sendString;
		cout << "Sent: " << sendString << endl;

		sendString = userName + ": " + sendString;

		if (sendString == "Q" || sendString == "q")
		{
			break;
		}

		NetworkInst->SendData(sendString.c_str());

		int rcvSize = NetworkInst->ReceiveData(recString);

		if (rcvSize > 0)
		{
			cout << recString << endl;
		}


		sendString = "";
	}


	NetworkInst->Shutdown();
	return 0;
}