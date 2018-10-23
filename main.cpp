/**
* BANK ACCOUNT MANAGER
* Writer: Thong Nguyen
* Date  : 08/08/2018
*/


#include"AccountList.h"

int main() {
	int option;
	AccountList list;
	list.init(); //Load existing accounts from file
	do {
		cout << "\n\n\n\n**********************************\n"
				"*         **MAIN MENU**          *\n"
				"* 1: Sign in                     *\n"
				"* 2: Sign up                     *\n"
				"* 3: Sign in as Admin            *\n"
				"* 4: Quit                        *\n"
				"*                                *\n"
				"**********************************\n"
				"Enter an option (1-4): ";
		cin >> option;
		cin.clear();
		while (cin.get() != '\n');
		switch (option) {
		case 1:
			list.signIn();
			break;
		case 2:
			list.signUp();
			break;
		case 3:
			list.adminSignIn();
			break;
		case 4:
			list.clear();
			break;
		default:
			cout << "Invalid option! Try Again\n" << endl;
			break;
		}
	} while (option != 4);
	return 0;
}
