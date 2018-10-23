#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<string>
#include<cstdlib>
using std::string;

class Account
{
private:
	string ID;
	string password;
	string name;
	double balance;

public:
	Account(const string& pID, const string& pPassword, const string& pName, const double pBalance = 0); //Create a new account with the provided ID and Password
	~Account();
	string getID() const { return ID; }
	string getPassWord() const { return password; }
	double getBalance() const { return balance; }
	string getName() const { return name; }
	bool deposit(double amt);
	bool withdraw(double amt);
	void display();

	void changeID(string pID);
	void changePassword(string pPassword);
	void changeName(string pName);
};

#endif // !ACCOUNT_H

