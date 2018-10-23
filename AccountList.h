#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include<iostream>
#include<fstream>
#include<vector>
#include"Account.h"
using namespace std;

class AccountList
{
private:
	struct Admin {
		string ID;
		string password;
	};

	vector<Account*> list;
	Admin admin;


	void accountMenu(Account * account); //Display a menu included what a user can do with the account
	double getAmount();

	//Admin section
	void adminMenu();
	void changeAdminInfo();
	void accessAccount();
	void adminAccountMenu(Account * account);
	void adminDeleteAccount(int i);

	//Load/save from file
	bool saveToFile();
	bool loadFromFile();

public:
	AccountList();
	~AccountList();
	
	void init();
	void signIn();
	void signUp();

	//Admin section
	void adminSignIn();

	void clear();
};


#endif // !ACCOUNTLIST_H
