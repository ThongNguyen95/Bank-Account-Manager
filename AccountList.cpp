#include "AccountList.h"



AccountList::AccountList()
{
	admin.ID = "admin";
	admin.password = "admin";
}


AccountList::~AccountList()
{
	if (list.size() > 0)
		clear();
}

void AccountList::init() {
	loadFromFile();
}

double AccountList::getAmount() {
	string amtString;
	bool passed;
	//Check to make sure the user enter a valid amount
	do {
		cout << "Amount: $";
		getline(cin, amtString);
		int dotCount = 0;
		passed = true;
		if (amtString.length() == 0)
			passed = false;
		for (unsigned int i = 0; i < amtString.length(); i++) {
			if (amtString[i] == '.') {
				dotCount++;
				if (dotCount < 2)
					continue;
			}
			if (amtString[i] < '0' || amtString[i] > '9' || dotCount > 1) {
				passed = false;
				break;
			}
		}
		if (passed == false)
			cout << "Invalid input. Please try again!" << endl;
	} while (passed == false);

	//After this point input is valid
	string::size_type size;
	double amt = stod(amtString, &size);
	return amt;
}

void AccountList::accountMenu(Account * account) {
	int option;
	double amt;
	do {
		cout << "\n\n\n\n*******************************************\n"
			"        Hello, " << account->getName() << "\n"
			"*         What would you like to do?      *\n"
			"* 1: Deposit                              *\n"
			"* 2: Withdraw                             *\n"
			"* 3: Check Account Balance                *\n"
			"* 4: End your session                     *\n"
			"*                                         *\n"
			"*******************************************\n\n"
			"Enter an option (1-4): ";
		cin >> option;
		cin.clear();
		while (cin.get() != '\n');
		switch (option) {
		case 1:
			cout << "\n\n*****************************************************\n"
				"*                       DEPOSIT                     *\n"
				"*****************************************************" << endl;
			amt = getAmount();
			if (account->deposit(amt))
			cout << "\n\n*****************************************************\n"
				"*       Transaction Was Successful!                 *\n"
				"*****************************************************" << endl;
			else
			cout << "\n\n*****************************************************\n"
				"*     Invalid Input. Transaction Was Cancelled!     *\n"
				"*****************************************************" << endl;
			break;
		case 2:
			cout << "\n\n*****************************************************\n"
				"*                      WITHDRAW                     *\n"
				"*****************************************************" << endl;
			amt = getAmount();
			if (account->withdraw(amt))
				cout << "\n\n*****************************************************\n"
				"*       Transaction Was Successful!                 *\n"
				"*****************************************************" << endl;
			else
				cout << "\n\n*****************************************************\n"
				"*  Insufficient Funds. Transaction Was Cancelled!   *\n"
				"*****************************************************" << endl;
			break;
		case 3:
			cout << "\n\n*****************************************************\n"
				 << "YOUR BALANCE: $" << account->getBalance() << "\n"
				"*****************************************************" << endl;
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	} while (option != 4);
}

void AccountList::signIn() {
	if (!list.empty()) {
		Account * user = nullptr;
		while (true) {
			bool found = false;
			string ID;
			string password;
			cout << "\n\n\n\n\n\n*****************************************************\n"
					"*                       SIGNING IN                  *\n"
					"*   Please enter your ID and Password below         *\n"
					"*****************************************************\n";
			//Get ID and PW from User
			cout << "ID: ";
			getline(cin, ID);
			cout << "Password: ";
			getline(cin, password);
			for (unsigned int i = 0; i < list.size(); i++) {
				if (ID == list[i]->getID() && password == list[i]->getPassWord()) {
					user = list[i];
					found = true;
					break;
				}
			}
			if (found)
				break;
			else {
				int option;
				cout << "\n\n\n\n\n\n*****************************************************\n"
					"*       ERROR: INCORRECT ID OR PASSWORD             *\n"
					"*        CHOOSE ONE OF THESE OPTIONS                *\n"
					"*   1: Retry                                        *\n"
					"*   2: Back to Main Menu                            *\n"
					"*****************************************************\n";
				while (true){
					cout << "Your option (1 or 2): ";
					cin >> option;
					cin.clear();
					while (cin.get() != '\n');
					if (option == 1 || option == 2)
						break;
					else
						cout << "invalid option!" << endl;
				}
				if (option == 1)
					continue;
				else
					return;
			}
		}
		//Successfully signed in so get here
		cout << "\n\n*****************************************************\n"
			"*             SUCCESSFULLY SIGNED IN...             *\n"
			"*****************************************************" << endl;
		accountMenu(user);
	}
	else {
		cout << "\n\n*****************************************************\n"
			"*       PLEASE SIGN UP FOR AN ACCOUNT FIRST.        *\n"
			"*****************************************************" << endl;
	}
}

void AccountList::signUp() {
	string ID;
	string password;
	while (true) {
		bool failed = false;
		cout << "\n\n\n\n\n\n*****************************************************\n"
			"*             SIGNING UP FOR AN ACCOUNT             *\n"
			"*                        NOTE                       *\n"
			"* Enter -1 at anytime to get back to MAIN MENU      *\n"
			"* ID and password must be at least 5-character long *\n"
			"*****************************************************\n";
		cout << "Enter a new ID: ";
		getline(cin, ID);
		cout << "ID entered: " << ID << endl;
		if (ID == "-1") {
			cout << "\n\n*****************************************************\n"
				"*                    BACK TO MAIN MENU              *\n"
				"*****************************************************" << endl;
			return;
		}
		cout << "Enter a new password: ";
		getline(cin, password);
		cout << "Password entered: " << password << endl;
		if (password == "-1") {
			cout << "\n\n*****************************************************\n"
				"*                    BACK TO MAIN MENU              *\n"
				"*****************************************************" << endl;
			return;
		}
		if (ID.length() < 5 || (ID.find(" ") != string::npos) || password.length() < 5 || (password.find(" ") != string::npos)) {
			cout << "\n\n*****************************************************\n "
				"Invalid input! ID or password is too short or contains \"SPACE\". Try again!\n"
				"*****************************************************" << endl;
			continue;
		}
		for (size_t i = 0; i < list.size(); i++) {
			if (ID == list[i]->getID()) {
				failed = true;
				break;
			}
		}
		if (failed) {
			cout << "\n\n*****************************************************\n "
				"This username has already been used.Try another one.\n"
				"*****************************************************" << endl;
			continue;
		}
		break; //at this point ID and password is valid
	}
	try {
		string name;
		while (true) {
			cout << "Enter your Full Name: ";
			getline(cin, name);
			if (name.size() < 5) {
				cout << "Name is too short! Retry" << endl;
				continue;
			}
			break;
		}
		Account * temp = new Account(ID, password, name);
		list.push_back(temp);
		cout << "\n\n*****************************************************\n "
				"Account successfully created! Back to Main Menu...\n"
				"*****************************************************" << endl;
		return;
	}
	catch (bad_alloc) {
		cout << "Memory is full. Unable to create account. Back to main Menu..." << endl;
		return;
	}
}

void AccountList::adminSignIn() {
	string aID;
	string aPassword;
	while (true) {
		cout << "\n\n\n\n\n\n*****************************************************\n"
			"*                SIGNING IN AS ADMIN                *\n"
			"*   Please enter your ID and Password below         *\n"
			"*****************************************************\n";
		cout << "Admin ID: ";
		getline(cin, aID);
		cout << "Admin Password: ";
		getline(cin, aPassword);
		if ((aID == admin.ID) && (aPassword == admin.password))
			break;
		int option;
		cout << "\n\n\n\n\n\n*****************************************************\n"
			"*       ERROR: INCORRECT ID OR PASSWORD             *\n"
			"*        CHOOSE ONE OF THESE OPTIONS                *\n"
			"*   1: Retry                                        *\n"
			"*   2: Back to Main Menu                            *\n"
			"*****************************************************\n";
		while (true) {
			cout << "Your option (1 or 2): ";
			cin >> option;
			cin.clear();
			while (cin.get() != '\n');
			if (option == 1 || option == 2)
				break;
			else
				cout << "invalid option!" << endl;
		}
		if (option == 1)
			continue;
		else {
			cout << "\n\n*****************************************************\n"
				"*                    BACK TO MAIN MENU              *\n"
				"*****************************************************" << endl;
			return;
		}
	}
	//Successfully Signed in as Admin
	cout << "\n\n*****************************************************\n"
		"*             SUCCESSFULLY SIGNED IN...             *\n"
		"*****************************************************" << endl;
	adminMenu();
}

void AccountList::adminMenu() {
	int option;
	do {
		cout << "\n\n\n\n**********************************\n"
			"*          ADMIN MENU            *\n"
			"* 1: Change admin ID/Password    *\n"
			"* 2: Access existing account     *\n"
			"* 3: Quit                        *\n"
			"**********************************\n"
			"Your option? ";
		cin >> option;
		cin.clear();
		while (cin.get() != '\n');
		switch (option) {
		case 1:
			changeAdminInfo();
			break;
		case 2:
			accessAccount();
			break;
		case 3:
			cout << "\n\n*****************************************************\n "
				"*                 Back to Main Menu...              *\n"
				"*****************************************************" << endl;
			break;
		default:
			cout << "Invalid option!" << endl;
			break;
		}
	} while (option != 3);
}

void AccountList::changeAdminInfo() {
	string tempID;
	string tempPW;
	while (true) {
		cout << "\n\n\n\n\n\n*****************************************************\n"
			"*           CHANGING ADMIN ID AND PASSWORD          *\n"
			"*                        NOTE                       *\n"
			"* Enter -1 at anytime to get back to MAIN MENU      *\n"
			"* ID and password must be at least 5-character long *\n"
			"*****************************************************\n";
		cout << "New admin ID: ";
		getline(cin, tempID);
		if (tempID == "-1") {
			cout << "Process was cancelled!" << endl;
			return;
		}
		cout << "New admin Password: ";
		getline(cin, tempPW);
		if (tempPW == "-1") {
			cout << "Process was cancelled!" << endl;
			return;
		}
		if (tempID.size() < 5 || tempPW.size() < 5 || tempID.find(" ") != string::npos || tempPW.find(" ") != string::npos) {
			cout << "\n\n*****************************************************\n "
				"Invalid input! ID or password is too short or contains \"SPACE\". Try again!\n"
				"*****************************************************" << endl;
			continue;
		}
		int option;
		cout << "\n\n\n\n\n\n*****************************************************\n"
			"*        YOU ENTERED VALID ID AND PASSWORD          *\n"
			"ID: " << tempID << "\n"
			"Password: " << tempPW << "\n"
			"* Choose an action:                                 *\n"
			"* 1: Confirm your change                            *\n"
			"* 2: Cancel the process                             *\n"
			"*****************************************************\n";
		bool good;
		while (true) {
			cout << "Your option: ";
			cin >> option;
			cin.clear();
			while (cin.get() != '\n');
			if (option == 1) {
				good = true;
				break;
			}
			else if (option == 2) {
				good = false;
				break;
			}
			else {
				cout << "Invalid Input. Retry!" << endl;
				continue;
			}
		}
		if (good == true) {
			break;
		}
		else {
			cout << "Process was cancelled!" << endl;
			return;
		}
	}
	admin.ID = tempID;
	admin.password = tempPW;
	cout << "\n\n*****************************************************\n"
		"*    SUCCESSFULLY CHANGED ADMIN ID AND PASSWORD.    *\n"
		"*****************************************************" << endl;
}

void AccountList::accessAccount() {
	string temp;
	bool found = false;
	cout << "\n\n*****************************************************\n"
		"*               ACCESSING USER ACCOUNT              *\n"
		"*****************************************************" << endl;
	cout << "Account ID: ";
	getline(cin, temp);
	size_t i;
	for (i = 0; i < list.size(); i++) {
		if (temp == list[i]->getID()) {
			found = true;
			break;
		}
	}
	if (found) {
		int option;
		cout << "\n\n\n\n\n\n***************************************************\n"
			"*               SUCCESSFULLY SIGNED IN            *\n"
			"*  What would you like to do with this account?   *\n"
			"* 1: Modify account                               *\n"
			"* 2: Delete this account                          *\n"
			"***************************************************\n";
		while (true) {
			cout << "Your option: ";
			cin >> option;
			cin.clear();
			while (cin.get() != '\n');
			if (option == 1) {
				adminAccountMenu(list[i]);
				break;
			}
			else if (option == 2) {
				int confirm;
				cout << "Are you sure you want to delete the account " << list[i]->getID() << "?\n"
						"1            : Yes\n"
						"Anything else: No\n"
						"\nYour option: ";
				cin >> confirm;
				cin.clear();
				while (cin.get() != '\n');
				if (confirm == 1) {
					adminDeleteAccount(i);
					cout << "\n\n*****************************************************\n"
						"*         ACCOUNT SUCCESSFULLY DELETED              *\n"
						"*****************************************************" << endl;
				}
				else
				cout << "\n\n******************************************************\n "
					"*Account Deletion Cancelled! Back to PREVIOUS MENU...*\n"
					"******************************************************" << endl;
				break;
			}
			else {
				cout << "Invalid Input. Retry!" << endl;
				continue;
			}
		}
	}
	else {
		cout << "Account does not exist! Back to MAIN MENU..." << endl;
	}
}

void AccountList::adminAccountMenu(Account * account) {
	int option;
	double amt;
	string temp;
	do {
		bool used = false;
		cout << "\n\n\n\n\n*************************************\n"
				"*  CHOOSE YOUR MODIFICATION OPTION  *\n"
				"*                                   *\n"
				"*  1: View Account Information      *\n"
				"*  2: Change ID                     *\n"
				"*  3: Change Password               *\n"
				"*  4: Change Name                   *\n"
				"*  5: Deposit                       *\n"
				"*  6: Withdraw                      *\n"
				"*  7: Back to PREVIOUS MENU         *\n"
				"*                                   *\n"
				"*************************************\n\n"
				"Enter your option: ";
		cin >> option;
		cin.clear();
		while (cin.get() != '\n');
		switch (option) {
		case 1:
			account->display();
			break;
		case 2:
			while (true) {
				cout << "Enter New ID: ";
				getline(cin, temp);
				if (temp.size() < 5 || temp.find(" ") != string::npos) {
					cout << "ID is too short or contain SPACE! Retry" << endl;
					continue;
				}
				break;
			}
			//Check if ID already existed
			for (size_t i = 0; i < list.size(); i++) {
				if (temp == list[i]->getID()) {
					used = true;
					break;
				}
			}
			if (used)
				cout << "\n\n*******************************************************\n"
				"*ERROR: THIS ID IS ALREADY USED! PROCESS WAS CANCELLED*\n"
				"*******************************************************" << endl;
			else
				account->changeID(temp);
			break;

		case 3:
			while (true) {
				cout << "Enter New Password: ";
				getline(cin, temp);
				if (temp.size() < 5 || temp.find(" ") != string::npos) {
					cout << "Password is too short or contain SPACE! Retry" << endl;
					continue;
				}
				break;
			}
			account->changePassword(temp);
			break;

		case 4:
			while (true) {
				cout << "Enter New Name: ";
				getline(cin, temp);
				if (temp.size() < 5) {
					cout << "Name is too short! Retry" << endl;
					continue;
				}
				break;
			}
			account->changeName(temp);
			break;

		case 5:
			cout << " DEPOSIT:" << endl;
			amt = getAmount();
			if (account->deposit(amt))
				cout << "Transaction Was Successful!" << endl;
			else
				cout << "Invalid Input. Transaction Was Cancelled!" << endl;
			break;
		case 6:
			cout << " WITHDRAW:" << endl;
			amt = getAmount();
			if (account->withdraw(amt))
				cout << "Transaction Was Successful!" << endl;
			else
				cout << "Insufficient Funds. Transaction Was Cancelled!" << endl;
			break;
		case 7:
			break;
		default:
			cout << "Invalid option! Try Again\n" << endl;
			break;
		}
	} while (option != 7);
}

void AccountList::adminDeleteAccount(int i) {
	//swap
	int last = list.size() - 1;
	Account* temp;
	if (i != last) {
		temp = list[i];
		list[i] = list[last];
		list[last] = temp;
	}
	//Clean up last
	temp = list[last];
	list.pop_back();
	delete temp;
}

bool AccountList::saveToFile() {

		ofstream outfile("accountlist.txt", ofstream::binary | ios::out);
		if (!outfile.fail()) {
			size_t size;
			//Save the size of the account list
			size = list.size();
			outfile.write((char*)&size, sizeof(size));
			//Loop to save each account
			for (size_t i = 0; i < list.size(); i++) {
				//Save account ID
				string temp = list[i]->getID();
				size = temp.size();
				outfile.write((char*)&size, sizeof(size));
				outfile.write(temp.c_str(), size);
				//Save account password
				temp = list[i]->getPassWord();
				size = temp.size();
				outfile.write((char*)&size, sizeof(size));
				outfile.write(temp.c_str(), size);
				//Save full name
				temp = list[i]->getName();
				size = temp.size();
				outfile.write((char*)&size, sizeof(size));
				outfile.write(temp.c_str(), size);
				//Save account balance
				double balance = list[i]->getBalance();
				outfile.write((char*)&balance, sizeof(balance));

			}
			//Save admin ID
			string temp = admin.ID;
			size = temp.size();
			outfile.write((char*)&size, sizeof(size));
			outfile.write(temp.c_str(), size);
			//Save admin password
			temp = admin.password;
			size = temp.size();
			outfile.write((char*)&size, sizeof(size));
			outfile.write(temp.c_str(), size);



			outfile.close();
			return true;
		}
	return false;
}
bool AccountList::loadFromFile() {
	ifstream infile("accountlist.txt", ifstream::binary | ios::in);
	if (!infile.fail()) {
		size_t listSize;
		//Load the size of the account list
		infile.read((char*)&listSize, sizeof(listSize));
		list.resize(listSize);
		//Loop through each account in the list to load its content
		size_t size;
		for (size_t i = 0; i < listSize; i++) {
			string ID;
			string password;
			string name;
			double balance;
			//Load user ID from file
			infile.read((char*)&size, sizeof(size));
			ID.resize(size);
			infile.read(&ID[0], size);
			//Load user password from file
			infile.read((char*)&size, sizeof(size));
			password.resize(size);
			infile.read(&password[0], size);
			//Load full name
			infile.read((char*)&size, sizeof(size));
			name.resize(size);
			infile.read(&name[0], size);
			//load balance
			infile.read((char*)&balance, sizeof(balance));
			//Create account based on loaded content and append to the list
			Account * account = new Account(ID, password, name, balance);
			list[i] = account;
		}
		//Load admin ID
		infile.read((char*)&size, sizeof(size));
		admin.ID.resize(size);
		infile.read(&(admin.ID)[0], size);
		//Load admin password
		infile.read((char*)&size, sizeof(size));
		admin.password.resize(size);
		infile.read(&(admin.password)[0], size);
		infile.close();
		return true;
	}
	return false;
}

void AccountList::clear() {
	saveToFile();
	for (size_t i = 0; i < list.size(); i++) {
		delete list[i];
	}
	list.clear();
}