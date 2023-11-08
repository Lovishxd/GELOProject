#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;
void main_menu();
int second_menu(int);
int main() {
	int choice, choice2;
	do {
		
		cout << "\n";
		main_menu();
		cout << "\tPlease enter any of the above option for Example Enter 1 to order Coffee:- ";
		cin >> choice;
		switch (choice) {
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: cout << "You Chose Option 4. \n" << "What can I help you with the following options Or you can call an associate by entering 3\n"; cin >> choice2; second_menu(choice2);  break;
		case 5: cout << "\tThank you for shopping with us your order should be ready within 20 minutes \n"; exit(0); break;
		default: cout << "Invalid Choice. Please Retry";
		}
		
	} while (choice != 5 && choice !=4);
	return 0;
}

void main_menu() {
	
	cout << "\t\t\t\t\t--------------------------------------------\n";
	cout << "\t\t\t\t\t\tWelcome to Jason's Coffee Shop\t\n";
	cout << "\t\t\t\t\t--------------------------------------------\n";
	cout << "\tWhat would you like to buy today?\n";
	cout << "\tOur Menu options are: \n";
	cout << "\t\t\t1. Coffee \n";
	cout << "\t\t\t2. Cheesecake \n";
	cout << "\t\t\t3. Coffee Beans \n";
	cout << "\t\t\t4. Help \n";
	cout << "\t\t\t5. Complete \n";
	cout << "\tPlease enter any of the above option for Example Enter 1 to order Coffee \n\n";
	cout << "\tEnter 5 when you are done ordering\n\n\n";
	
	

}
int second_menu(int choice2) {
	
	cout << "\t\t\t1. Manager Login.\n";
	cout << "\t\t\t2. Employee Clock-in/out\n";
	cout << "\t\t\t3. Call Assistance \a\n";
	cout << "\t\t\t4. EXIT \a\n";
	
	if (choice2 == 1) {
		int pass1 = 1111, pass2;
		cout << "Please Enter the manager password to view sales and data : ";
		cin >> pass2;
		string check = (pass1 == pass2) ? "sales" : "Incorrect Password\n";
		if (check == "sales") { return 0; }
		else { cout << "Incorrect Password\n"; }
		

	}
	else if (choice2 == 2) { int id1; cout << "Enter your clockin ID please : "; cin >> id1; }
	else if (choice2 == 3) { cout << "An associate is headed your way. Thank you.";  }
	else { return 0; }
}