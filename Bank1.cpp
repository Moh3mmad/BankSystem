#include<iostream>
#include<string>
#include<iomanip>
#include <fstream>
#include <vector>

using namespace std;

const string ClientFileNameForBankP = "ClientFileNameForBankP.txt";

void PressKey()
{
	cout << "\nPress any key to go back main menu ...\n\n";
	system("pause ");
}

void ClearScreen()
{
	system("cls");
}

struct stClient // client info of bank
{
	string AccountNumber;
	string  PinCode;
	string Name;
	string phone;
	double AccountBalance;
	bool MarkClientDelte = false;

};

string ReadAccountNumber()
{
	string AccountNumber = "";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}

string ConvertRecordToLine(stClient& Client, string Seperator = "#//#")
{
	string Line = "";
	Line += Client.AccountNumber + Seperator;
	Line += Client.PinCode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.phone + Seperator;
	Line += to_string(Client.AccountBalance);

	return Line;
}

vector<string> SplitString(string Line, string Seperator = "#//#")
{
	vector <string> vClient;
	string LWords;
	int pos;
	while ((pos = Line.find(Seperator)) != std::string::npos)
	{
		LWords = Line.substr(0, pos);
		if (LWords != "")
		{
			vClient.push_back(LWords);
		}

		Line.erase(0, pos + Seperator.length());
	}
	if (Line != "")
		vClient.push_back(Line);

	return vClient;
}

stClient ConvertLineToRecord(string Line)
{
	stClient LoadClient;
	vector <string> vClientData = SplitString(Line);

	LoadClient.AccountNumber = vClientData[0];
	LoadClient.PinCode = vClientData[1];
	LoadClient.Name = vClientData[2];
	LoadClient.phone = vClientData[3];
	LoadClient.AccountBalance = stod(vClientData[4]);

	return LoadClient;
}

void LoadDataFromClientToFile(vector <stClient>& vClient)
{
	fstream MyFile;
	MyFile.open(ClientFileNameForBankP, ios::out);// | ios::app

	string Line = "";
	if (MyFile.is_open())
	{
		for (stClient& C : vClient)
		{
			if (C.MarkClientDelte == false)
			{
				MyFile << ConvertRecordToLine(C) << endl;
			}

		}
		MyFile.close();
	}
}

vector<stClient> LoadDataFromFileToClient()
{
	fstream MyFile;
	MyFile.open(ClientFileNameForBankP, ios::in);

	string Line;
	vector <stClient> vClient;
	stClient Client;

	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}


string CheckAccountNumber()
{
	vector <stClient> Client = LoadDataFromFileToClient();// LoadDataFromFileToCheckIT accN
	string AccountNumber = ReadAccountNumber();

	bool existclient = true;
	while (existclient)
	{
		existclient = false;

		for (stClient& C : Client)
		{
			if (C.AccountNumber == AccountNumber)
			{
				existclient = true;

				cout << "Client with [" << AccountNumber << "] already exists,";
				cout << "Enter another Account Number ?";
				AccountNumber = ReadAccountNumber();
				break;// ‰ﬂ”— «·Õ·ﬁ… ·‰»œ√ „‰ ÃœÌœ »«·ﬁÌ„… «·ÃœÌœ…
			}
		}

	}
	return AccountNumber;
}

stClient ReadNewClient()
{
	stClient Client;


	cout << "Enter Account Number ?";
	Client.AccountNumber = CheckAccountNumber();

	cout << "Enter PinCode ?";
	getline(cin, Client.PinCode);

	cout << "Enter Name ?";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.phone);

	cout << "Enter Account Balance ?";
	cin >> Client.AccountBalance;

	return Client;

}





// req 1
void ShowClientsData()
{
	ClearScreen();

	vector <stClient> vClient = LoadDataFromFileToClient();
	cout << "\n--------------------------------------------------------------------------------------\n";
	cout << "|" << left << setw(16) << " Account Number " << "|" << left << setw(15) << " Pin Code " << "|" << left << setw(30) << " Client Name " << "|" << left << setw(10) << " Phone " << "|" << left << setw(9) << " Balance" << "|";
	cout << "\n--------------------------------------------------------------------------------------\n";

	for (stClient& C : vClient)
	{
		cout << "|" << left << setw(16) << C.AccountNumber << "|" << left << setw(15) << C.PinCode << "|" << left << setw(30) << C.Name << "|" << left << setw(10) << C.phone << "|" << left << setw(9) << C.AccountBalance << "|" << endl;

	}
	cout << "--------------------------------------------------------------------------------------\n";

	PressKey();


}


//req 2 done
void AddNewClient()
{
	ClearScreen();

	cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n"; 
	cout << "\t\Add Client Screen";
	cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

	stClient Client = ReadNewClient();

	vector <stClient> vClient = LoadDataFromFileToClient(); //  Õ„Ì· «·ﬁœ«„Ï ÊÌ÷Ì› ⁄·ÌÂ„ · Ã‰» «Ì „‘ﬂ·…
	vClient.push_back(Client);
	LoadDataFromClientToFile(vClient);

	cout << "Client Adding Successfully :) \n";

	PressKey();

}

void PrintClientCard(stClient& Client)
{
	cout << "The Following Are The Client Details :";
	cout << "\n------------------------------------------------\n";
	cout << "Account Number :" << Client.AccountNumber << endl;
	cout << "Pin Code       :" << Client.PinCode << endl;
	cout << "Name           :" << Client.Name << endl;
	cout << "Phone          :" << Client.phone << endl;
	cout << "Account Balance :" << Client.AccountBalance << endl;
	cout << "\n------------------------------------------------\n";

}

bool MarkClientDeleted(string AccountNumber, vector <stClient>& vClient)
{

	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkClientDelte = true;
			return true;

		}
	}
	return false;
}

//req 3
void DeleteClient()
{
	ClearScreen();


	cout << "Please Enter Account Number To Deletting Its Information ?";
	string AccountNumber = ReadAccountNumber();

	vector <stClient> vClient = LoadDataFromFileToClient();


	cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	cout << "\t\tDelete Client Screen";
	cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

	if (MarkClientDeleted(AccountNumber, vClient))
	{
		for (stClient& C : vClient)
		{
			if (C.MarkClientDelte == true)
			{
				PrintClientCard(C);

				char delClient = 'Y';
				cout << "Are you sure you want delete this client ? y/n ?";
				cin >> delClient;

				if (toupper(delClient) == 'Y') // (y / Y)
				{
					LoadDataFromClientToFile(vClient);

					cout << "Client Deleting Successfully \n\n";
					PressKey();
				}
				else
				{
					PressKey();
				}
			}

		}
	}
	else
	{
		cout << "Account Number (" << AccountNumber << ") is not found !\n";
		PressKey();

	}

}

stClient ReadClientUpdatting(stClient Client)
{
	cout << "Enter PinCode ?";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ?";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.phone);

	cout << "Enter Account Balance ?";
	cin >> Client.AccountBalance;

	PressKey();

	return Client;
}


//req 4
void UpdateClient()
{
	ClearScreen();


	cout << "Please Enter Account Number To Updatting Its Information ?";
	string AccountNumber = ReadAccountNumber();

	vector <stClient> vClient = LoadDataFromFileToClient();


	cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	cout << "\t\tUpdate Client Screen";
	cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

	if (MarkClientDeleted(AccountNumber, vClient))
	{

		for (stClient& C : vClient)
		{
			if (C.MarkClientDelte == true)
			{
				PrintClientCard(C);

				char updClient = 'Y';
				cout << "Are you sure you want update this client? y/n ?";
				cin >> updClient;

				if (toupper(updClient) == 'Y')
				{
					C = ReadClientUpdatting(C); // any updatting of C direct refelcting of vClient
					C.MarkClientDelte = false; // very important 'dont forget' to print the result and not ignorancing it
					LoadDataFromClientToFile(vClient);
					cout << "Client Updating Successfully \n";
					PressKey();

				}
				else
				{
					PressKey();
				}
			}

		}
	}
	else
	{
		cout << "Account Number (" << AccountNumber << ") is not found !\n";
		PressKey();

	}

}

//req 5
void FindClient()
{

	ClearScreen();

	cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	cout << "\t\tFind Client Screen";
	cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

	cout << "Please enter AccountNumber ?";
	string AccountNumber = ReadAccountNumber();
	vector <stClient> vClient = LoadDataFromFileToClient();

	bool isFound = false;

	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			isFound = true;

			PrintClientCard(C);
			PressKey();
		}
	}

	if (!isFound)
	{
		cout << "Account Number (" << AccountNumber << ") is not found !\n";
		PressKey();
	}
}
//req 6
void End()
{
	ClearScreen();

	cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	cout << "\t\tEnd Screen";
	cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

	PressKey();
}


void SwitchFunctions(short choice)
{
	switch (choice) {
	case 1:
	{
		ShowClientsData();

		break;
	}
	case 2:
	{
		AddNewClient();

		break;
	}
	case 3:
	{
		DeleteClient();
		break;
	}
	case 4:
	{
		UpdateClient();
		break;
	}


	case 5:
	{

		FindClient();
		break;
	}
	case 6:
	{
		End();
		break;
	}

	}
}

void ShowMainMenu()
{

	cout << "\n==============================================\n";
	cout << setw(25) << "Main Menu";
	cout << "\n==============================================\n";

	short choice = 0;
	do
	{


		cout << "\t[" << 1 << "] Show Client List.\n";
		cout << "\t[" << 2 << "] Add New Client.\n";
		cout << "\t[" << 3 << "] Delete Client.\n";
		cout << "\t[" << 4 << "] Update Client Info.\n";
		cout << "\t[" << 5 << "] Find Client.\n";
		cout << "\t[" << 6 << "] Exit.\n";
		cout << "\n==============================================\n";
		cout << "Choose what do you want to do? [1 to 6]?";
		cin >> choice;


		SwitchFunctions(choice);
		ClearScreen();


	} while (choice != 6);
}

int main()
{

	ShowMainMenu();

}