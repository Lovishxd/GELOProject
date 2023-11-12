#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <fstream>

const double COFFEE_PRICE = 1.20;
const double CHEESECAKE_PRICE = 2.00;
const double COFFEE_BEANS_PRICE = 5.00;
const int MANAGER_PASSWORD = 1234;

using namespace std;
void main_menu();
int second_menu(int);
double sellCoffee(int&);
double sellCheesecake(int&);
double sellCoffeeBeans(double&);
void managerActions(double, double, double, int, int, double);
void orderReview(double, double, double);
void displayItemQuantities(int, int, double);
void displayTotalCoffeeSold(double);
void displayTotalMoneyMade(double);

int main() {
    int choice, choice2;
    double total1 = 0, total2 = 0, total3 = 0, totalCoffeeSold = 0, totalMoneyMade = 0;
    int coffeeCups = 0, cheesecakeSlices = 0;
    double coffeeBeansAmount = 0;

    do {
        cout << "\n";
        main_menu();
        cout << "\tPlease enter any of the above options. For example, enter 1 to order Coffee: ";
        cin >> choice;

        switch (choice) {
            case 1:
                total1 += sellCoffee(coffeeCups);
                break;
            case 2:
                total2 += sellCheesecake(cheesecakeSlices);
                break;
            case 3:
                total3 += sellCoffeeBeans(coffeeBeansAmount);
                break;
            case 4:
                orderReview(total1, total2, total3);
                cout << "Your total including tax is: $" << fixed << setprecision(2) << (total1 + total2 + total3) * 1.7 << endl;
                break;
            case 5:
                cout << "You chose Option 5. \n";
                cout << "What can I help you with the following options? Or you can call an associate by entering 3\n";
                cout << "\t\t\t1. Manager Login.\n";
                cout << "\t\t\t2. Employee Clock-in/out\n";
                cout << "\t\t\t3. Call Assistance \a\n";
                cout << "\t\t\t4. EXIT \a\n";
                cin >> choice2;
                if (choice2 == 1) {
                    second_menu(choice2);
                    managerActions(total1, total2, total3, coffeeCups, cheesecakeSlices, coffeeBeansAmount);
                } else if (choice2 == 4) {
                    cout << "Exiting program. Thank you for using Jason's Coffee Shop.\n";
                    exit(0);
                } else {
                    second_menu(choice2);
                }
                break;
            case 6:
                cout << "\tThank you for shopping with us. Your order should be ready within 20 minutes \n";
                exit(0);
                break;
            default:
                cout << "Invalid Choice. Please Retry";
        }

        totalCoffeeSold = total1 + total2 + total3;
        totalMoneyMade = (total1 + total2 + total3) * 1.7;

    } while (choice != 5 && choice != 6);

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
	cout << "\t\t\t4. Review Order \n";
	cout << "\t\t\t5. Help \n";
	cout << "\t\t\t6. Complete \n";
	cout << "\tPlease enter any of the above option for Example Enter 1 to order Coffee \n\n";
	cout << "\tEnter 6 when you are done ordering\n\n\n";
	
	

}
void managerActions(double total1, double total2, double total3, int coffeeCups, int cheesecakeSlices, double coffeeBeansAmount) {
    double totalCoffeeSold = total1 + total2 + total3;
    double totalMoneyMade = (total1 + total2 + total3) * 1.7;
    displayItemQuantities(coffeeCups, cheesecakeSlices, coffeeBeansAmount);
    displayTotalCoffeeSold(totalCoffeeSold);
    displayTotalMoneyMade(totalMoneyMade);
}

void displayItemQuantities(int coffeeCups, int cheesecakeSlices, double coffeeBeansAmount) {
    cout << "Quantities Sold:\n";
    cout << "Coffee Cups: " << coffeeCups << " cups\n";
    cout << "Cheesecake Slices: " << cheesecakeSlices << " slices\n";
    cout << "Coffee Beans: " << coffeeBeansAmount << " ounces\n";
    cout << "-------------------------\n";
}

void displayTotalCoffeeSold(double totalCoffee) {
    cout << "Total Coffee Sold: " << totalCoffee << " cups\n";
    cout << "-------------------------\n";
}

void displayTotalMoneyMade(double totalMoney) {
    cout << "Total Money Made: $" << fixed << setprecision(2) << totalMoney << "\n";
    cout << "-------------------------\n";
}
int second_menu(int choice2) {
    if (choice2 == 1) {
        int correctPassword = MANAGER_PASSWORD;
        int userPassword;
        int attempts = 0;

        do {
            cout << "Please enter the manager password to view sales and data: ";
            cin >> userPassword;

            if (userPassword == correctPassword) {
                cout << "Login successful.\n";
                return 0;
            } else {
                cout << "Incorrect password. Please try again.\n";
                attempts++;

                if (attempts >= 3) {
                    cout << "Too many incorrect attempts. Exiting.\n";
                    exit(0);
                }
            }
        } while (true);
    } else if (choice2 == 2) {
        int id1;
        cout << "Enter your clock-in ID: ";
        cin >> id1;
        cout << "Successfully clocked in ID number: " << id1 << endl;
    } else if (choice2 == 3) {
        cout << "An associate is headed your way. Thank you.\n";
    } else {
        return 0;
}}


double sellCoffee(int& coffeeCups) {
    int cf;
    double total;
    string tempChoice;
    string size1;

    cout << "  You Have selected To buy Coffee  \n";
    cout << "\tWhat size of Coffee would you like to choose?\n";
    cout << "Please enter L/l (12oz) for Large or S/s(9oz) for small : ";
    cin >> size1;

    do {
        if (size1 == "L" || size1 == "l") {
            cout << "Please enter the quantity you would like to buy : ";
            cin >> cf;
            cout << endl;
            coffeeCups += cf; // Increment the quantity of coffee cups sold
            total = cf * COFFEE_PRICE;

            cout << "Would you like to purchase more Coffee? (Enter Y/y for y or enter any key for no) :";
            cin >> tempChoice;
            cout << endl;
        } else if (size1 == "S" || size1 == "s") {
            cout << "Please enter the quantity you would like to buy : ";
            cin >> cf;
            coffeeCups += cf; // Increment the quantity of coffee cups sold
            total = cf * COFFEE_PRICE;
            cout << "Would you like to purchase more Coffee? (Enter Y/y for y or enter any key for no) :";
            cin >> tempChoice;
            cout << endl;
        } else {
            cout << "Invalid Size Please Try Again!";
            cout << "Would you like to purchase more Coffee? (Enter Y/y for y or enter any key for no) :";
            cin >> tempChoice;
            cout << endl;
        }
    } while (tempChoice == "Y" || tempChoice == "y");

    cout << "You have purchased " << cf << " cup(s) of coffee. Your total cost is $" << total << endl;
    return total;
}

double sellCheesecake(int& cheesecakeSlices) {
    int qty1;
    double total;
    string tempChoice;

    do {
        cout << " You Have selected To buy Cheesecake \n";
        cout << "Cheesecake is $2.00 each \n";
        cout << "Please enter the quantity you would like to buy : ";
        cin >> qty1;
        cheesecakeSlices += qty1; // Increment the quantity of cheesecake slices sold
        total = qty1 * CHEESECAKE_PRICE;
        cout << "You have purchased " << qty1 << " Cheesecake(s). Your total cost is $" << total << endl;

        cout << "Would you like to purchase more Cheesecake? (Enter Y/y for y or enter any key for no) :";
        cin >> tempChoice;
        cout << endl;

    } while (tempChoice == "Y" || tempChoice == "y");

    return total;
}

double sellCoffeeBeans(double& coffeeBeansAmount) {
    int qty2;
    double total;
    string tempChoice;

    do {
        cout << " You Have selected To buy Coffee Beans \n";
        cout << "Coffee Beans are $5.00 per ounce \n";
        cout << "Please enter the quantity you would like to buy : ";
        cin >> qty2;
        coffeeBeansAmount += qty2; // Accumulate the amount of coffee beans sold
        total = qty2 * COFFEE_BEANS_PRICE;
        cout << "You have purchased " << qty2 << " pounds of Coffee Beans. Your total cost is $" << total << endl;

        cout << "Would you like to purchase more Coffee Beans? (Enter Y/y for y or enter any key for no) :";
        cin >> tempChoice;
        cout << endl;

    } while (tempChoice == "Y" || tempChoice == "y");

    return total;
}
void orderReview(double total1, double total2, double total3) {
    cout << "*****************************************\n";
    cout << "* Order Review: \n";
    cout << "* Coffee: $" << total1 << "\n";
    cout << "* Cheesecake: $" << total2 << "\n";
    cout << "* Coffee Beans: $" << total3 << "\n";
    cout << "*****************************************\n";
}