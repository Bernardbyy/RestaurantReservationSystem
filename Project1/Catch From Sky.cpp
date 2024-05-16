#define NOMINMAX
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<sstream>
#include<vector>
#include<stdlib.h>

using namespace std;

ifstream inData;
ofstream outData;

vector<string> records;
string record;


int numOfReserv = 0;

struct customer
{
	string name, phone, remarks, id;
	int pax, startTime, date;

}customerDetails[100];



struct regfil		//structure for save staff acc
{
	string fullname = " ";
	string word = "";
	string userName = " ";
	string passWord = "";
};

regfil userDT;		//structure variable
int spc = 0;

//========Ong Ker Jing & Jia Wei Function=========
void login();
void reg();
void forgot();
int validinput4();
int validinput2();
void header();
void login();
void viewheader1();
void bye();
//=========Boon Yong Yeow Functions========
int updateArray();
int mainMenu();
void clearData();
bool availability(int& dateWanted, int& timeWanted, int z);
void create(int x, int y, int z);
void sortArray(int z);
void sortedList(int z);
void view(int z);
//===========Lim Meng Fu Function=========
int readRec();
void deleteRecords(int numOfReserv, int delRecDay, int delRecTime);
void editOptions(int numOfReserv, int edtRecDay, int edtRecTime);
void anyKey();



int main()
{
	//Declare Variables for 'Main'
	char charYN;
	int numOfReserv = 0, menuSelection = 0, reqDate = 0, reqTime = 0, counter = 0, delRecTime = 0, delRecDay = 0, edtOpt = 0, edtRecTime = 0, edtRecDay = 0, i = 0, j = 0, date = 0;
	bool status = false;

	//Before Running Program load data from file to array of struct 1st and Get Number of Existing Reservation
	numOfReserv = updateArray(); //once updateArray() is executed details will be loaded into customerDetails[]

	int option = 0;
	header();
	cout << " \t\t\t\t[1] Login\n";
	cout << " \t\t\t\t[2] Register New Account\n";
	cout << " \t\t\t\t[3] Forgot Username/Password\n";
	cout << " \t\t\t\t[4] Exit\n\n";
	cout << "\t\t\t><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><" << endl;

	cout << endl;
	cout << " \t\t\t\tEnter option: ";
	option = validinput4();

	switch (option)
	{
	case 1:
		login();
		break;

	case 2:
		reg();
		break;

	case 3:
		system("CLS");
		forgot();

		break;

	case 4:
		system("cls");
		bye();
		anyKey();
		exit(1);
		break;

	default:
		system("CLS");
		cout << "\t\t\tInvalid Option \n";
		main();
	}



	//Main Menu Section
	do {

		//Main Menu
		menuSelection = mainMenu();

		//After User input for Menu Selection
		switch (menuSelection)
		{
			//View Reservation Menu
		case 1:
			sortArray(numOfReserv);
			view(numOfReserv); //This fuction is view array (customerDetails[x]) not view file
			break;

			//Create Reservation Menu
		case 2:
			status = availability(reqDate, reqTime, numOfReserv);

			if (status == false) //if "availability return 'rejectedFlag == 0'
			{
				create(reqDate, reqTime, numOfReserv);
				numOfReserv = updateArray(); //After created new reservation update the array
				clearData(); //Clear Contents of the text file
				sortArray(numOfReserv); //Sort array according to date
				sortedList(numOfReserv); //Write sorted array to text file
			}

			break;

			//Remove Reservation Menu
		case 3:
			readRec();
			system("cls");
			header();

			cout << "\n\t\t\t\t\t\t<Delete Record Section>\n";

			counter = 0;
			cout << "\n\t\t\t\tYou are about to delete a record u sure? (Y / Other) >> ";
			cin >> charYN;

			while (counter != 1)   //if "availability return 'rejectedFlag == 0' //if (status == false)
			{

				if (charYN == 'Y' || charYN == 'y')
				{
					system("cls");
					header();
					viewheader1();

					for (int i = 0; i < numOfReserv; i++)
					{
						cout << "\t\t| " << left << setw(3) << customerDetails[i].date << "|" << left << setw(2) << customerDetails[i].startTime << left << setw(3) << "00" << "|" << left << setw(17) << customerDetails[i].name << "|" << left << setw(12) << customerDetails[i].phone << "|" << left << setw(3) << customerDetails[i].pax << "|" << left << setw(40) << customerDetails[i].remarks << "|" << endl;
					}
					cout << "\t\t========================================================================================" << endl;
					cout << "\n\t\t\tFor which day and time of reservation that you want to delete?";
					cout << "\n\t\t\tFor what day >> ";
					cin >> delRecDay;

					for (i = 0; i < numOfReserv; i++)
					{
						counter = 0;

						if (delRecDay != customerDetails[i].date)
						{
							counter = 1;
						}
						else
						{
							date = i;
							counter = 0;
							break;
						}
					}

					if (counter == 1)
					{
						cout << "\n\t\t\t\tNo reservations are made on that day.\n";
					}
					else if (counter == 0)
					{
						cout << "\n\t\t\tFor what Time for day " << delRecDay << "? >>";
						cin >> delRecTime;

						for (i = date; i < numOfReserv; i++)
						{
							if (customerDetails[date].date == delRecDay)
							{
								for (j = date; j < numOfReserv; j++)
								{
									if (delRecTime == customerDetails[j].startTime && delRecDay == customerDetails[j].date)
									{
										counter = 0;
										deleteRecords(numOfReserv, delRecDay, delRecTime);
										break;
									}
									else
									{
										counter = 1;
									}
								}
							}
							break;
						}
						if (counter == 1)
						{
							cout << "\n\t\t\tNo reservations made on that day on that time.\n";
						}
					}

					numOfReserv = updateArray();
					records.clear();

					cin.ignore();
					anyKey();

					counter = 1;
				}
				else
				{
					system("cls");
					counter = 1;
					break;
				}
			}
			break;

			//edit reservation menu
		case 4:
			system("cls");
			header();

			cout << "\n\t\t\t\t\t\t<Edit Record Section>\n";

			counter = 0;
			cout << "\n\t\t\tYou are about to edit a record u sure? (Y / Other) >> ";
			cin >> charYN;

			while (counter != 1)   //if "availability return 'rejectedFlag == 0' //if (status == false)
			{

				if (charYN == 'Y' || charYN == 'y')
				{
					system("cls");
					header();
					viewheader1();

					for (int i = 0; i < numOfReserv; i++)
					{
						cout << "\t\t| " << left << setw(3) << customerDetails[i].date << "|" << left << setw(2) << customerDetails[i].startTime << left << setw(3) << "00" << "|" << left << setw(17) << customerDetails[i].name << "|" << left << setw(12) << customerDetails[i].phone << "|" << left << setw(3) << customerDetails[i].pax << "|" << left << setw(40) << customerDetails[i].remarks << "|" << endl;
					}

					cout << "\t\t========================================================================================" << endl;
					cout << "\n\t\t\tFor which day and time of reservation that you want to edit?";
					cout << "\n\t\t\tFor which day >> ";
					cin >> edtRecDay;

					for (i = 0; i < numOfReserv; i++)
					{
						counter = 0;

						if (edtRecDay != customerDetails[i].date)
						{
							counter = 1;
						}
						else
						{
							date = i;
							counter = 0;
							break;
						}
					}

					if (counter == 1)
					{
						cout << "\n\t\t\t\t\tNo reservations are made on that day.\n";
					}
					else if (counter == 0)
					{
						cout << "\n\t\t\tFor what Time for day " << edtRecDay << "? >>";
						cin >> edtRecTime;

						for (i = 0; i < numOfReserv; i++)
						{
							if (customerDetails[date].date == edtRecDay)
							{
								for (j = date; j < numOfReserv; j++)
								{
									if (edtRecTime == customerDetails[j].startTime && edtRecDay == customerDetails[j].date)
									{
										counter = 0;
										editOptions(numOfReserv, edtRecDay, edtRecTime);
										break;
									}
									else
									{
										counter = 1;
									}
									//break;
								}
								break;
							}
							//break;
						}
						if (counter == 1)
						{
							cout << "\n\t\t\tNo reservations made on that day on that time.\n";
						}
					}

					anyKey();

					counter = 1;
				}
				else
				{
					system("cls");
					counter = 1;
					break;
				}
			}
			break;

			//Exit program
		case 5:
			system("cls");
			bye();
			anyKey();
			main();
			break;

		default:
			cout << "Please Enter Valid Menu Selection";
		}
	} while (menuSelection != 5);

	return 0;
}

//=========Ong Ker Jing and Chuah Jia Wei Functions========
void login()
{
	system("CLS");	//clear screen
	header();
	cout << endl;
	ifstream infile;
	infile.open("namepass.txt", ios::in); //open namepass.txt

	string uname;
	string pw;
	char ch;
	int opt;


	if (!infile)		//check file condition
	{
		cout << "\t\t\t\t\tError opening file";
	}
	else
	{
		cin.clear();
		cout << " \t\t\t\t\t\tUsername: ";	//get username password
		getline(cin, uname);

		cout << " \t\t\t\t\t\tPassword: ";

		HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE); //create a restore point mode, is know 503
		DWORD mode = 0;

		GetConsoleMode(hStdInput, &mode); //create a restore point mode, is know 503

		SetConsoleMode(
			hStdInput,
			mode & (~ENABLE_ECHO_INPUT) //enable echo input, set to 499
		);

		getline(cin, pw); //take input

		cout << endl;
		SetConsoleMode(hStdInput, mode); //restore the mode

		while (!infile.eof())	//compare username and password, stop when end of file
		{
			getline(infile, userDT.fullname);
			infile >> userDT.word >> userDT.userName >> userDT.passWord;
			infile.get(ch);

			if (userDT.userName == uname && userDT.passWord == pw)
			{
				cout << "\n\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
				cout << "\n\t\t\t\t!!!!!!!!!!!!!!!| Login Succcessful |!!!!!!!!!!!!!!\n";
				cout << "\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				anyKey();

				goto inner;
			}
		}
		infile.close();

		cout << "\n\t\t\t\t\t!!!!!!!!!!Login Unsuccessful!!!!!!!!!!.\n\n";

		//If Login Failed menu
		cout << "\t\t\t==================================================================\n" << endl;
		cout << "\t\t\t\t[1] Retry Login\n";
		cout << "\t\t\t\t[2] Reset Username/Password\n";
		cout << "\t\t\t\t[3] Register New Account\n";
		cout << "\t\t\t\t[4] Exit\n";
		cout << "\n\t\t\t><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><>\n" << endl;
		cout << " \t\t\t\t\Enter Option:"; //login fail, output menu
		opt = validinput4();

		switch (opt)
		{
		case 1:
			login();
			break;

		case 2:
			forgot();
			break;

		case 3:
			reg();
			break;

		case 4:
			cout << " \t\t\t\t\t\tThank You~ \n";
			exit(0);

		inner:
			break;
		}
	}
}

void reg()
{

	system("CLS");	//clear screen
	header();
	cout << endl;
	ofstream infile;
	infile.open("namepass.txt", ios::app);//to append into file

	if (!infile)
	{
		cout << "Error opening file";
	}

	else
	{
		system("CLS");
		header();
		ofstream infile;
		infile.open("namepass.txt", ios::app);
		string passw;

		//get fullname, username,password, hint word(for changing password or username)
		cin.clear();
		cout << " \t\t\t\tFull Name: ";
		getline(cin, userDT.fullname);

		do {
			spc = 0;
			cout << " \t\t\t\tEnter a hint word: ";

			getline(cin, userDT.word);

			if (userDT.word.length() <= 50)
			{
				for (int i = 0; i < userDT.word.length(); i++) //to prevent space
				{
					if (userDT.word[i] == ' ')
					{
						spc++;
					}
				}
				if (spc > 0)
				{
					cout << " \t\t\t\t\tCannot have space inside word \n";
				}
			}
			else	//to prevent exceed word limit
			{
				cout << "\t\t\t\t\twords can't exceed 50 letter\n";
			}
			cin.clear();
		} while (userDT.word.length() > 50 || spc > 0);
		//reenter if exceed word limit or have space

		do {
			spc = 0;

			cout << " \t\t\t\tUsername: ";

			getline(cin, userDT.userName);

			if (userDT.userName.length() <= 25)
			{
				for (int i = 0; i < userDT.userName.length(); i++) //to prevent space
				{
					if (userDT.userName[i] == ' ')
					{
						spc++;
					}
				}
				if (spc > 0)
				{
					cout << " \t\t\t\t\tCannot have space inside username \n";
				}
			}
			else		//to prevent exceed word limit
			{
				cout << "\t\t\t\t\tusername can't exceed 25 letter\n";
			}
			cin.clear();
		} while (userDT.userName.length() > 25 || spc > 0);
		//reenter if exceed word limit or have space


		do {

			do {
				spc = 0;
				cout << " \t\t\t\tPassword: ";
				getline(cin, userDT.passWord);

				if (userDT.passWord.length() <= 25)
				{
					for (int i = 0; i < userDT.passWord.length(); i++)
					{
						if (userDT.passWord[i] == ' ')
						{
							spc++;
						}
					}
					if (spc > 0)
					{
						cout << " \t\t\t\t\tCannot have space inside password \n";
					}
				}
				else
				{
					cout << " \t\t\t\t\tpassword can't exceed 25 letter\n";
				}
				cin.clear();
			} while (userDT.passWord.length() > 25 || spc > 0);

			cout << " \t\t\t\tRe-enter password: ";
			cin.clear();
			getline(cin, passw);

			if (passw != userDT.passWord)	// to ensure user know the password
			{
				cout << "\t\t\t\t\tPassword not match\n";
			}
			cin.clear();
		} while (passw != userDT.passWord);

		infile << userDT.fullname << "\n" << userDT.word << " " << userDT.userName << " " << userDT.passWord << endl;
		//write into file
	}
	infile.close();
	cout << "\n\n\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	cout << "\n\t\t\t\t!!!!!!!!!!!!| Registration Succcessful |!!!!!!!!!!\n";
	cout << "\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	anyKey();

	main();
}

void forgot()
{
	system("CLS");
	header();
	cout << endl;
	string fName = " ", passw;
	string hword, chname, chpass, chusername;
	char ch;
	int select;
	bool inputvalid = false;

	ifstream infile;	//reading record
	infile.open("namepass.txt"); //to read file

	ofstream temp;		//write in record for temporary use
	temp.open("tempp.txt");

	if (!infile)
	{
		cout << "\t\t\tError opening file\n";
	}
	if (!temp)
	{
		cout << "\t\t\tError opening file\n";
	}
	else
	{
		cin.clear();
		cout << " \t\t\t\tEnter your fullname: ";	//get user fullname and hint word & check with the input when user register
		getline(cin, fName);

		cout << " \t\t\t\tEnter your hint word: ";
		getline(cin, hword);

		cout << endl;

		string line;
		while (!infile.eof()) {		//while not end of file
			while (getline(infile, line, '\n'))	//get namepass.txt line by line
			{

				infile >> userDT.word >> userDT.userName >> userDT.passWord;
				infile.get(ch);

				if (line == fName && userDT.word == hword)
					//if full name & hint word are correct
				{
					cout << "\t\t\t------------------------------------------------------------------\n" << endl;
					cout << " \t\t\t\tWhich would you like to reset ? \n\n";
					cout << " \t\t\t\t[1] Reset Username\n";
					cout << " \t\t\t\t[2] Reset Password\n\n";
					cout << "\t\t\t------------------------------------------------------------------\n" << endl;
					cout << " \t\t\t\tEnter option: ";
					select = validinput2();
					cin.clear();

					switch (select)
					{
					case 1:
						do {
							spc = 0;

							cout << " \n\t\t\t\tEnter New Username: ";

							getline(cin, userDT.userName);

							if (userDT.userName.length() <= 25)
							{
								for (int i = 0; i < userDT.userName.length(); i++) //to prevent space
								{
									if (userDT.userName[i] == ' ')
									{
										cout << " \t\t\t\t\tCannot have space inside username \n";
										spc++;
									}
								}
							}
							else		//to prevent exceed word limit
							{
								cout << "\t\t\t\t\tusername can't exceed 25 letter\n";
							}
							cin.clear();
						} while (userDT.userName.length() > 25 || spc > 0);
						cout << "\t\t\t\tReset successfully! \n";
						break;

					case 2:
						do {

							do {//to check if the password got space or exceed 25 letters
								spc = 0;

								cout << "\n\t\t\t\tEnter new password: ";

								getline(cin, userDT.passWord);

								if (userDT.passWord.length() <= 25)
								{
									for (int i = 0; i < userDT.passWord.length(); i++)
									{
										if (userDT.passWord[i] == ' ')
										{
											cout << " \t\t\t\t\tCannot have space inside password \n";
											spc++;
										}
									}
								}
								else
								{
									cout << " \t\t\t\t\tpassword can't exceed 25 letter\n";
								}
								cin.clear();
							} while (userDT.passWord.length() > 25 || spc > 0);
							//to ensure user know the password
							cout << "\t\t\t\tRe-enter password: ";
							cin.clear();
							getline(cin, passw);

							if (passw != userDT.passWord)
							{
								cout << " \t\t\t\t\tPassword not match\n";
							}
							cin.clear();
						} while (passw != userDT.passWord);
						cout << "\t\t\t\tReset successfully! \n";
						break;
					}

					temp << line << "\n" << userDT.word << " " << userDT.userName << " " << userDT.passWord << endl;
					inputvalid = true;		//input inside tempp.txt
				}
				else
				{
					temp << line << "\n" << userDT.word << " " << userDT.userName << " " << userDT.passWord << endl;
				}
			}
		}

		if (inputvalid == false)
		{
			cout << " \t\t\t\t\tinput error!\n";
		}

		infile.close();
		temp.close();
		if (remove("namepass.txt"))
		{
			perror("file delete fail\n");
		}

		if (rename("tempp.txt", "namepass.txt") != 0)
		{
			perror("file rename error\n");

		}

		cout << "\t\t\t------------------------------------------------------------------\n" << endl;
		cout << " \t\t\t\t[1] Reset again\n";
		cout << " \t\t\t\t[2] Main Menu\n\n";
		cout << "\t\t\t------------------------------------------------------------------\n" << endl;
		cout << " \t\t\t\tEnter option: ";
		select = validinput2();

		switch (select)
		{
		case 1:
			forgot();
			break;

		case 2:
			system("CLS");
			main();
			break;
		}
	}
}

int validinput2()
{
	int x = 0;

	do {
		//This for loop is to ensure input validation for 2 option
		for (;;) {
			if (cin >> x) {
				cin.ignore(10000, '\n'); //Ignore after "."
				break;
			}
			else {
				cout << "\n\t\t\t\tBad input !!! \n\t\t\t\tPlease enter an integer." << endl;
				cout << "\t\t\t\tEnter option: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		if (x < 1 || x > 2)
		{
			cout << "\t\t\t\tPlease Enter Valid Sub-Menu Selection ( 1 - 2)\n";
			cout << "\t\t\t\tEnter option: ";
		}
	} while (x < 1 || x >2);
	return x;
}

int validinput4()
{
	int x = 0;

	do {
		//This for loop is to ensure input validation for 4 option
		for (;;) {
			if (cin >> x) {
				cin.ignore(10000, '\n'); //Ignore after "."
				break;
			}
			else {
				cout << "\n\t\t\t\tBad input !!! \n\t\t\t\tPlease enter an integer." << endl;
				cout << "\t\t\t\tEnter option: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		if (x < 1 || x > 4)
		{
			cout << "\t\t\t\tPlease Enter Valid Sub-Menu Selection ( 1 - 4)\n";
			cout << "\t\t\t\tEnter option: ";
		}

	} while (x < 1 || x >4);
	return x;
}

void header()
{
	cout << "\t\t                          _           ___                         _           " << endl;
	cout << "\t\t                 _       | |         / __)                       | |          " << endl;
	cout << "\t\t    ____ _____ _| |_ ____| |__     _| |__ ____ ___  ____      ___| |  _ _   _ " << endl;
	cout << "\t\t   / ___|____ (_   _) ___)  _ \\   (_   __) ___) _ \\|    \\    /___) |_/ ) | | |" << endl;
	cout << "\t\t  ( (___/ ___ | | |( (___| | | |    | | | |  | |_| | | | |  |___ |  _ (| |_| |" << endl;
	cout << "\t\t   \\____)_____|  \\__)____)_| |_|    |_| |_|   \\___/|_|_|_|  (___/|_| \\_)\\__  |" << endl;
	cout << "\t\t                                                                       (____/" << endl;

	cout << endl;
	cout << "\t\t\t==================================================================" << endl;
	cout << "\t\t\t||\tCATCH FROM SKY HOT POT RESTAURANT RESERVATION SYSTEM\t||" << endl;
	cout << "\t\t\t==================================================================" << endl;
	cout << endl;
}

void viewheader1()
{
	cout << "\n\t\t\t\t\t<Customer Restaurant Reservation Details>\n\n";
	cout << "\t\t----------------------------------------------------------------------------------------" << endl;
	cout << "\t\t|Date" << "|" << left << setw(5) << "Time" << "|" << left << setw(17)
		<< "Name" << "|" << left << setw(12) << "Phone No." << "|" << left << setw(3) << "Pax" << "|" << left << setw(40) << "Remarks" << "|" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------" << endl;

}

void bye()
{
	/*cout << "\t\t\t\t    _                  _" << endl;
	cout << "\t\t\t\t    | |__  _   _  ___  | |__  _   _  ___" << endl;
	cout << "\t\t\t\t    | '_ \\| | | |/ _ \\ | '_ \\| | | |/ _ \\ " << endl;
	cout << "\t\t\t\t    | |_) | |_| |  __/ | |_) | |_| |  __/" << endl;
	cout << "\t\t\t\t    |_.__/\\__,  |\\___|  |_.__/\\__, |\\__|" << endl;
	cout << "\t\t\t\t           |___/              |___/" << endl;*/

	cout << "\n\n\n\n\n\n";
	cout << "\t\t   _____           _            _         _    _     _                _                     _ " << endl;
	cout << "\t\t  / ____|         | |          | |       | |  | |   | |              | |                   | |" << endl;
	cout << "\t\t | |        __ _  | |_    ___  | |__     | |  | |   | |        __ _  | |_    ___   _ __    | |" << endl;
	cout << "\t\t | |       / _` | | __|  / __| | '_ \\    | |  | |   | |       / _` | | __|  / _ \\ | '__|   | |" << endl;
	cout << "\t\t | |____  | (_| | | |_  | (__  | | | |   | |__| |   | |____  | (_| | | |_  |  __/ | |      |_|" << endl;
	cout << "\t\t  \\_____|  \\__,_|  \\__|  \\___| |_| |_|    \\____/    |______|  \\__,_|  \\__|  \\___| |_|      (_)" << endl;
	cout << "\t\t                                                                                              " << endl;
	cout << "\t\t                                                                                              " << endl;


}

//=========Boon Yong Yeow Functions========

int updateArray()
{
	string line, strDate, strTime, strPax; //For class use (Loading info from file)
	int x = 0, howManyReserv = 0;

	//Opening File and loading info into array of struct (comma) #############################################
	inData.open("sample.txt",ios::app);
	if (!inData.is_open()) {
		cout << "File failed to open, \"sample.txt\" does not exist yet " << endl;
		exit(1);
	}

	while (getline(inData, line)) {
		stringstream ss(line);
		getline(ss, strDate, ',');
		customerDetails[x].date = stoi(strDate);
		getline(ss, strTime, ',');
		customerDetails[x].startTime = stoi(strTime);
		getline(ss, customerDetails[x].name, ',');
		getline(ss, customerDetails[x].phone, ',');
		getline(ss, strPax, ',');
		customerDetails[x].pax = stoi(strPax);
		getline(ss, customerDetails[x].remarks, ',');
		x++;
	}
	inData.close();

	howManyReserv = x;

	return howManyReserv;
	//End of loading information ##############################################################################
}

int mainMenu()
{
	int x = 0;

	header();
	cout << " \t\t\t\t\t\t   < MAIN MENU >\n\n" << endl;
	cout << " \t\t\t\t\t    [1] View Reservation Table\n";
	cout << " \t\t\t\t\t    [2] Create Reservation\n";
	cout << " \t\t\t\t\t    [3] Remove Reservation\n";
	cout << " \t\t\t\t\t    [4] Edit Reservation\n";
	cout << " \t\t\t\t\t    [5] Log Out\n\n\n";
	cout << "\t\t\t><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><\n" << endl;
	cout << " \t\t\t\t\tEnter Option:";

	do {
		//This for loop is to ensure input validation
		for (;;) {
			if (cin >> x) {
				cin.ignore(10000, '\n'); //Ignore after "."
				break;
			}
			else {
				cout << "\n\t\t\t\t\tBad input !!! \n\t\t\t\t\tPlease enter an integer :";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		if (x <= 0 || x > 5)
		{
			cout << "\n\t\t\t\tPlease Enter Valid Sub-Menu Selection ( 1 - 5) :";
		}
	} while (x <= 0 || x > 5);
	return x;
}

void view(int z)
{
	char check;
	system("cls");
	header();
	viewheader1();

	for (int i = 0; i < z; i++)
	{
		cout << "\t\t| " << left << setw(3) << customerDetails[i].date << "|" << left << setw(2) << customerDetails[i].startTime << left << setw(3) << "00" << "|" << left << setw(17) << customerDetails[i].name << "|" << left << setw(12) << customerDetails[i].phone << "|" << left << setw(3) << customerDetails[i].pax << "|" << left << setw(40) << customerDetails[i].remarks << "|" << endl;
	}

	cout << "\t\t----------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "\t\t\t\tPress [Enter] to go back.......";
	cout << endl;
	while (1)
	{
		if (cin.get() != 'n')
		{
			system("cls");
			break;
		}
	}
}

bool availability(int& dateWanted, int& timeWanted, int z)
{
	system("cls");
	//Declare Local Variables For "Availability"
	int requestDate = 0, requestStart = 0, unavailableIndex = 0, allTime[14] = { 8,9,10,11,12,13,14,15,16,17,18,19,20,21 }, unavailable[14] = { 0 };
	bool rejectedFlag = false, invalid = false;
	char cont;

	//Ask for User input, pass back to main using reference for later use
	header();

	cout << "\t\t\t\t\t    < Check for Availability > \n\n";

	//Ask for date of reservation
	do {
		//This for loop is to ensure input validation
		for (;;) {
			cout << "\t\t\tPlease Enter Date of Reservation : ";
			if (cin >> requestDate) {
				cin.ignore(10000, '\n'); //Ignore after "."
				break;
			}
			else {
				cout << "\n\t\t\tBad input !!! \n\t\t\tPlease enter an integer " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		if (requestDate < 0 || requestDate > 31)
		{
			cout << "\n\t\t\tDays in a month : ( 1 - 31)\n\n";
		}
	} while (requestDate < 0 || requestDate > 31);
	dateWanted = requestDate;

	//Stores unavaible times into an array
	for (int i = 0; i < z; i++)
	{
		if (customerDetails[i].date == requestDate)
		{
			unavailable[unavailableIndex] = customerDetails[i].startTime;
			unavailableIndex++;
		}
	}

	//Print out available times
	cout << "\n\t\t\tAvailable slots for " << requestDate << "(th) are : ";
	for (int index = 0; index < 14; index++)
	{
		bool taken = false;
		for (int jndex = 0; jndex < unavailableIndex; jndex++)
		{
			if (allTime[index] == unavailable[jndex])
			{
				taken = true;
				continue;
			}
		}
		if (taken == false)
		{
			cout << allTime[index] << "| ";
		}
	}

	do
	{
		invalid = false;
		cout << "\n\n\t\t\tDo you wish to continue ? [Y/N} : ";
		cin >> cont;

		if (cont == 'y' || cont == 'Y')
		{
			//Ask for time of reservation
			do {
				for (;;) {
					cout << "\n\n\t\t\tWhat time are you dining in : ";
					if (cin >> requestStart) {
						cin.ignore(10000, '\n'); //Ignore after "."
						break;
					}
					else {
						cout << "\n\t\t\tBad input !!! \n\t\t\tPlease enter an integer " << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}

				if (requestStart < 8 || requestStart > 21)
				{
					cout << "\n\t\t\tOur Operation Hours are between 0800 to 2200 (#LAST Rerservation = 2100) \n";
				}
			} while (requestStart < 8 || requestStart > 21);
			timeWanted = requestStart;

			//Loop through array of struct of member : 'date' to find similiar reservation
			for (int i = 0; i < z; i++)
			{
				if (customerDetails[i].date == requestDate)
				{
					if (customerDetails[i].startTime == requestStart)
					{
						cout << "\n\n\t\t\tSlot for " << requestDate << "(th) , " << requestStart << " o'clock is taken. \nRequest reservation rejected.\n\n";
						rejectedFlag = true;
						cout << "\n\n\n\t\t\t\t\tPress [enter] to go back........";

						while (1)
						{
							if (cin.get() != 'n')
							{
								system("cls");
							}
							break;
						}
					}
				}
			}
		}
		else if (cont == 'n' || cont == 'N')
		{
			rejectedFlag = true;
			system("cls");
			cout << "\n\t\t\t\t\tCreate operation voided\n";
		}

		else {
			cout << "\n\t\t\tPlease Enter Valid choice Y/N !!!\n";
			invalid = true;
		}
	} while (invalid == true);

	return rejectedFlag; //Return value indicating if request is rejected or not
}

void create(int x, int y, int z)//x is date , y is time and z is no. of reservations
{
	int c = z + 1, number = 0;
	bool reject = false;
	string numstr = "";


	customerDetails[c].date = x;
	customerDetails[c].startTime = y;


	system("cls");
	header();

	cout << "\t\t\t\t\t    < Create Reservation Section > \n\n";

	//Request is not rejected, therefore ask for more customer details
	do {
		//This for loop is to ensure input validation
		for (;;) {
			cout << "\t\t\t\tPlease Enter PAX : ";
			if (cin >> customerDetails[c].pax) {
				break;
			}
			else {
				cout << "\n\t\t\t\tBad Input ! Please enter a valid integer" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		if (customerDetails[c].pax > 10)
		{
			cout << "\n\t\t\t\tLimit Exceed ! Maximum of 10 pax.\n";
		}
	} while (customerDetails[c].pax > 10);

	do {
		reject = false;
		cout << "\t\t\t\tPlease Enter Name : ";
		cin.get();
		getline(cin, customerDetails[c].name);

		if (customerDetails[c].name.length() > 15)
		{
			reject = true;
			cout << "\n\t\t\t\tName is too long\n";
			customerDetails[c].name = "";
		}
	} while (reject);

	do {
		reject = false;
		for (;;) {
			cout << "\t\t\t\tPlease Enter Phone Number : ";
			if (cin >> number) {
				break;
			}
			else {
				cout << "\t\t\t\tBad Input ! Please enter a valid integer" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		stringstream ss;
		ss << number;
		ss >> numstr;
		customerDetails[c].phone = "0" + numstr;

		if (customerDetails[c].phone.length() != 10)
		{
			reject = true;
			cout << "\n\t\t\t\tInvalid Phone number !!\n";
			customerDetails[c].phone = "";
		}
	} while (reject);

	do {
		reject = false;
		cout << "\t\t\t\tAny remarks ? : ";
		cin.get();
		getline(cin, customerDetails[c].remarks);

		if (customerDetails[c].remarks.length() > 50)
		{
			reject = true;
			cout << "\n\t\t\t\tPlease Shorten your remark.\n";
			customerDetails[c].remarks = "";
		}
	} while (reject);

	//Reservation Summary
	cout << "\n\t\t\t<><><><><><><><><><><><><>><><><><><><><><><><><><>><><><><><>><><\n\t\t\t\tReservation Summary :"
		<< "\n\t\t\t\tDate : " << customerDetails[c].date << "\n\t\t\t\tStart Time: " << customerDetails[c].startTime
		<< "\n\t\t\t\tName : " << customerDetails[c].name << "\n\t\t\t\tPhone Number : " << customerDetails[c].phone
		<< "\n\t\t\t\tPAX : " << customerDetails[c].pax << "\n\t\t\t\tCustomer Remarks : " << customerDetails[c].remarks
		<< "\n\t\t\t<><><><><><><><><><><><><>><><><><><><><><><><><><>><><><><><>><><" << endl;

	anyKey();

	//Open file to append customer details
	outData.open("sample.txt", ios::app);
	if (outData.fail())
	{
		cout << "Error Opening File ";
		exit(1);
	}

	outData << customerDetails[c].date << "," << customerDetails[c].startTime << "," << customerDetails[c].name << "," << customerDetails[c].phone << ","
		<< customerDetails[c].pax << "," << customerDetails[c].remarks << "," << endl;

	outData.close();

	c++;
}

void clearData()
{
	outData.open("sample.txt", ofstream::out | ofstream::trunc); //Clear Contents in File
	outData.close();
}

void sortArray(int z)
{
	bool swapped;

	do
	{
		swapped = false;
		for (int count = 0; count < (z - 1); count++)
		{
			if (customerDetails[count].date > customerDetails[count + 1].date)
			{
				swap(customerDetails[count], customerDetails[count + 1]);
				swapped = true;
			}
			else if (customerDetails[count].date == customerDetails[count + 1].date)
			{
				if (customerDetails[count].startTime > customerDetails[count + 1].startTime)
				{
					swap(customerDetails[count], customerDetails[count + 1]);
					swapped = true;
				}
			}
		}
	} while (swapped); //Loop again is swapped action occured on this pass
}

void sortedList(int z)
{
	//Open file to append customer details
	outData.open("sample.txt");
	if (outData.fail())
	{
		cout << "Error Opening File ";
		exit(1);
	}
	for (int count = 0; count < z; count++)
	{
		outData << customerDetails[count].date << "," << customerDetails[count].startTime << "," << customerDetails[count].name << ","
			<< customerDetails[count].phone << "," << customerDetails[count].pax << "," << customerDetails[count].remarks << "," << endl;
	}
	outData.close();
}



//=========Lim Meng Fu Functions========

int readRec()
{
	inData.open("sample.txt");

	if (inData.fail())
	{
		cout << "\t\t\t\t\tError opening file !" << endl;
		return 1;
	}

	while (getline(inData, record))
		records.push_back(record);

	inData.close();
}

void deleteRecords(int numOfReserv, int delRecDay, int delRecTime)
{
	clearData();

	numOfReserv = updateArray();

	outData.open("sample.txt");
	for (int i = 0; i < records.size(); i++)
	{
		if (customerDetails[i].date != delRecDay)
			outData << records[i] << endl;
		else if (customerDetails[i].startTime != delRecTime)
			outData << records[i] << endl;
	}

	cout << "\n\t\t\t\tRecord has been deleted.";

	outData.close();
}

void editOptions(int numOfReserv, int edtRecDay, int edtRecTime)
{
	system("cls");
	header();

	int c = numOfReserv + 1, number = 0;
	bool reject = false;
	string numstr = "";

	int edtOpt = 0;
	for (int i = 0; i < numOfReserv; i++)
	{
		if (customerDetails[i].date == edtRecDay && customerDetails[i].startTime == edtRecTime)
		{
			//cout << customerDetails[i].date << customerDetails[i].startTime << customerDetails[i].name << customerDetails[i].phone << customerDetails[i].pax << customerDetails[i].remarks << endl;
			cout << "\t\t\t\t<What would you like to edit?>\n";
			cout << " \t\t\t\t[1] Name\n";
			cout << " \t\t\t\t[2] Phone Number\n";
			cout << " \t\t\t\t[3] Pax\n";
			cout << " \t\t\t\t[4] Remarks\n";
			cout << " \t\t\t\t[5] Main Menu\n";
			cout << "\t\t\t==================================================================" << endl;
			cout << " \t\t\t\t\Enter Option:";;

			do {
				//This for loop is to ensure input validation
				for (;;) {
					if (cin >> edtOpt) {
						cin.ignore(10000, '\n'); //Ignore after "."
						break;
					}
					else {
						cout << "\n\t\t\t\t\tBad input !!! \n\t\t\t\t\tPlease enter an integer :";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
				if (edtOpt <= 0 || edtOpt > 5)
				{
					cout << "\n\t\t\t\tPlease Enter Valid Sub-Menu Selection ( 1 - 5 ) :";
				}
			} while (edtOpt <= 0 || edtOpt > 5);

			switch (edtOpt)
			{
			case 1:
				do {
					reject = false;
					cout << "\t\t\t\tEnter the new name >> ";
					getline(cin, customerDetails[i].name);

					if (customerDetails[i].name.length() > 15)
					{
						reject = true;
						cout << "\t\t\t\t\tName is too long\n";
						customerDetails[i].name = "";
					}
				} while (reject);
				cout << "\t\t\t\t\tRecord has been edited\n";
				break;

			case 2:
				do {
					reject = false;
					for (;;) {
						cout << "\t\t\t\tEnter the new Phone Number >> ";
						if (cin >> number) {
							break;
						}
						else {
							cout << "\t\t\t\t\tBad Input ! Please enter a valid integer" << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					}
					stringstream ss;
					ss << number;
					ss >> numstr;
					customerDetails[i].phone = "0" + numstr;

					if (customerDetails[i].phone.length() != 10)
					{
						reject = true;
						cout << "\n\t\t\t\tInvalid Phone number !!\n";
						customerDetails[i].phone = "";
					}
				} while (reject);
				cin.ignore();
				cout << "\t\t\t\t\tRecord has been edited\n";
				break;

			case 3:
				do {
					//This for loop is to ensure input validation
					for (;;) {
						cout << "\t\t\t\tPlease Enter New PAX >> ";
						if (cin >> customerDetails[i].pax) {
							break;
						}
						else {
							cout << "\t\t\t\t\tBad Input ! Please enter a valid integer" << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					}
					if (customerDetails[i].pax > 10)
					{
						cout << "\t\t\t\t\tLimit Exceed ! Maximum of 10 pax.\n";
					}
				} while (customerDetails[i].pax > 10);
				cin.ignore();
				cout << "\t\t\t\t\tRecord has been edited\n";
				break;

			case 4:
				do {
					reject = false;
					cout << "\t\t\t\tPlease Enter New Remarks >> ";
					getline(cin, customerDetails[i].remarks);

					if (customerDetails[i].remarks.length() > 50)
					{
						reject = true;
						cout << "\t\t\t\t\tPlease Shorten your remark.\n";
						customerDetails[i].remarks = "";
					}
				} while (reject);
				cout << "\t\t\t\t\tRecord has been edited\n";
				break;

			default:
				cout << "\t\t\t\t\tGoing Back to Main Menu\n";
				break;
			}
		}
	}

	clearData();
	sortedList(numOfReserv);
}


void anyKey()
{
	cout << "\n\n\n\t\t\t\tPress [Enter] to proceed ........";
	while (1)
	{
		if (cin.get() != 'n')
		{
			system("cls");
			break;
		}
	}
}





