#include<iostream>
#include"Account.h"
using namespace std;

Account::Account(const string& pID, const string& pPassword, const string& pName, const double pBalance) {
	ID = pID;
	password = pPassword;
	balance = pBalance;
	name = pName;
}

Account::~Account()
{
}

bool Account::deposit(double amt) {
	if (amt > 0) {
		balance += amt;
		return true;
	}
	return false;
}
bool Account::withdraw(double amt) {
	if ((amt > 0) && ((balance - amt) >= 0)) {
		balance -= amt;
		return true;
	}
	return false;
}

void Account::display() {
	cout << "\n\n\n********************************\n"
		"ACCOUNT INFORMATION\n"
		"ID      : " << ID << "\n"
		"Password: " << password << "\n"
		"Name    : " << name << "\n"
		"Balance : $" << balance << "\n"
		"********************************\n\n\n" << endl;
}

void Account::changeID(string pID) {
	if (pID != ID) {
		ID = pID;
		cout << "ID was successfully changed! Back to PREVIOUS MENU" << endl;
	}
	else
		cout << "New ID is the same as previous ID. Process was Cancelled!" << endl;
}
void Account::changePassword(string pPassword) {
	if (pPassword != password) {
		password = pPassword;
		cout << "Password was successfully changed! Back to PREVIOUS MENU" << endl;
	}
	else
		cout << "New password is the same as previous password. Process was Cancelled!" << endl;
}
void Account::changeName(string pName) {
	if (pName != name) {
		name = pName;
		cout << "Name was successfully changed! Back to PREVIOUS MENU" << endl;
	}
	else
		cout << "New name is the same as previous name. Process was Cancelled!" << endl;
}