#include <string>
#include "iostream"
#include "NetworkManager.h"
#include <conio.h>

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

	cout << "Type Q To Quit OR Type A Message To Send: " << endl;
	while (true)
	{
		if (!_kbhit())
		{
			cin >> sendString;

			if (sendString == "Q" || sendString == "q")
			{
				break;
			}
		}
		else 
		{
			int rcvSize = NetworkManager::GetInstance()->ReceiveData(recString);

			if (rcvSize > 0)
			{
				cout << " user : " << recString << endl;
			}

		}

		sendString = "";
	}


	NetworkInst->Shutdown();
	return 0;
}