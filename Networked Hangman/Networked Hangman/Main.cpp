#include <string>
#include "iostream"
#include "NetworkManager.h"

using namespace std;

int userPort;
string connectIP;

int main()
{
	//Send String Vars
	string sendString;
	sendString[0] = '\0';

	//Rec String Vars
	char* recString = new char[65543];
	recString[0] = '\0';

	cout << "Enter a port to connect on" << endl;
	cin >> userPort;

	cout << endl << "Enter an IP Address to connect to" << endl;
	cin >> connectIP;

	NetworkManager* NetworkInst = NetworkManager::GetInstance();

	NetworkInst->Init();

	NetworkInst->CreateUDPSockets();
	NetworkInst->BindUDP();
	NetworkInst->SetRemoteData(userPort, connectIP);

	cin.clear();

	cout << "Type Q To Quit OR Type A Message To Send: " << endl;
	getline(cin, sendString);

	NetworkInst->SendData(sendString.c_str());

	int rcvSize = NetworkInst->ReceiveData(recString);

	if (rcvSize > 0)
	{
		cout << "Received: " << recString << endl;
	}

	NetworkInst->Shutdown();
	return 0;
}