#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

const double COFFEE_PRICE = 1.50;
const double LARGE_COFFEE_PRICE = 1.90;
const double CHEESECAKE_PRICE = 3.00;
const double COFFEE_BEANS_PRICE = 0.60;
const int MANAGER_PASSWORD = 1234;

static int transactionIDCounter;

using namespace std;

// Function declarations
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
void recordTransaction(const string& items, int quantity, double total);
void displaySalesData();

int main() {
    int choice, choice2;
    double total1 = 0, total2 = 0, total3 = 0, totalCoffeeSold = 0, totalMoneyMade = 0;
    int coffeeCups = 0, cheesecakeSlices = 0;
    double coffeeBeansAmount = 0;

    do {
        cout << "\n";
        main_menu();
        cout << "\tPlease enter the number corresponding to your choice: ";
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
                cout << "Your total including tax is: $" << fixed << setprecision(2) << (total1 + total2 + total3) + ((total1 + total2 + total3) * 0.07) << endl;
                break;
            case 5:
                cout << "You chose Option 5. What can I help you with?\n";
                cout << "\t1. Manager Login.\n";
                cout << "\t2. Employee Clock-in/out\n";
                cout << "\t3. Call Assistance\n";
                cout << "\t4. EXIT\n";
                cout << "Enter the number corresponding to your choice: ";
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
                recordTransaction("Coffee, Cheesecake, Coffee Beans", coffeeCups + cheesecakeSlices + coffeeBeansAmount, totalMoneyMade);
                cout << "\tThank you for shopping with us. Your order should be ready within 20 minutes.\n";
                exit(0);
                break;
            default:
                cout << "Invalid Choice. Please retry.\n";
        }

        totalCoffeeSold = total1 + total2 + total3;
        totalMoneyMade = (total1 + total2 + total3) + ((total1 + total2 + total3) * 0.07);

    } while (choice != 5 && choice != 6);

    return 0;
}

void main_menu() {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string currentTime = ctime(&now);
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t\tWelcome to Jason's Coffee Shop\t" << "\t\t\t\t\t\t" << currentTime << "\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\tWhat would you like to buy today?\n";
    cout << "\tOur Menu options are: \n";
    cout << "\t1. Coffee\n";
    cout << "\t2. Cheesecake\n";
    cout << "\t3. Coffee Beans\n";
    cout << "\t4. Review Order\n";
    cout << "\t5. Help\n";
    cout << "\t6. Complete\n";
    cout << "Enter the number corresponding to your choice.\n\n";
}

void managerActions(double total1, double total2, double total3, int coffeeCups, int cheesecakeSlices, double coffeeBeansAmount) {
    double totalCoffeeSold = total1 + total2 + total3;
    double totalMoneyMade = (total1 + total2 + total3) + ((total1 + total2 + total3) * 0.07);
    displayItemQuantities(coffeeCups, cheesecakeSlices, coffeeBeansAmount);
    displayTotalCoffeeSold(totalCoffeeSold);
    displayTotalMoneyMade(totalMoneyMade);
    displaySalesData();
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
    }
    return 0;
}

double sellCoffee(int& coffeeCups) {
    int quantity;
    double total;
    string size;

    cout << "  You have selected to buy Coffee\n";
    cout << "What size of Coffee would you like to choose?\n";
    cout << "Please enter 'L' for Large (12oz) or 'S' for Small (9oz): ";
    cin >> size;

    do {
        if (size == "L" || size == "l") {
            cout << "Please enter the quantity you would like to buy: ";
            cin >> quantity;
            coffeeCups += quantity;
            total = quantity * LARGE_COFFEE_PRICE;
        } else if (size == "S" || size == "s") {
            cout << "Please enter the quantity you would like to buy: ";
            cin >> quantity;
            coffeeCups += quantity;
            total = quantity * COFFEE_PRICE;
        } else {
            cout << "Invalid size. Please try again!\n";
            continue;
        }

        cout << "You have purchased " << quantity << " cup(s) of coffee. Your total cost is $" << fixed << setprecision(2) << total << endl;

        char choice;
        cout << "Would you like to purchase more Coffee? (Enter 'Y' for yes or any other key for no): ";
        cin >> choice;

        if (tolower(choice) != 'y') {
            break;
        }

        cout << "\nWhat size of Coffee would you like to choose?\n";
        cout << "Please enter 'L' for Large (12oz) or 'S' for Small (9oz): ";
        cin >> size;

    } while (true);

    return total;
}

double sellCheesecake(int& cheesecakeSlices) {
    int quantity;
    double total;

    do {
        cout << "You have selected to buy Cheesecake\n";
        cout << "Cheesecake is $3.00 each\n";
        cout << "Please enter the quantity you would like to buy: ";
        cin >> quantity;
        cheesecakeSlices += quantity;
        total = quantity * CHEESECAKE_PRICE;

        cout << "You have purchased " << quantity << " Cheesecake(s). Your total cost is $" << fixed << setprecision(2) << total << endl;

        char choice;
        cout << "Would you like to purchase more Cheesecake? (Enter 'Y' for yes or any other key for no): ";
        cin >> choice;

        if (tolower(choice) != 'y') {
            break;
        }

    } while (true);

    return total;
}

double sellCoffeeBeans(double& coffeeBeansAmount) {
    int quantity;
    double total;

    do {
        cout << "You have selected to buy Coffee Beans\n";
        cout << "Coffee Beans are $0.60 per ounce\n";
        cout << "Please enter the quantity you would like to buy: ";
        cin >> quantity;
        coffeeBeansAmount += quantity;
        total = quantity * COFFEE_BEANS_PRICE;

        cout << "You have purchased " << quantity << " ounce(s) of Coffee Beans. Your total cost is $" << fixed << setprecision(2) << total << endl;

        char choice;
        cout << "Would you like to purchase more Coffee Beans? (Enter 'Y' for yes or any other key for no): ";
        cin >> choice;

        if (tolower(choice) != 'y') {
            break;
        }

    } while (true);

    return total;
}

void orderReview(double total1, double total2, double total3) {
    cout << "*****************************************\n";
    cout << "* Order Review: \n";
    cout << "* Coffee: $" << fixed << setprecision(2) << total1 << "\n";
    cout << "* Cheesecake: $" << fixed << setprecision(2) << total2 << "\n";
    cout << "* Coffee Beans: $" << fixed << setprecision(2) << total3 << "\n";
    cout << "*****************************************\n";
}

void recordTransaction(const string& items, int quantity, double total) {
    // Increment the transaction ID counter
    int transactionID = ++transactionIDCounter;

    time_t now = time(0);
    tm* localTime = localtime(&now);
    char dateTime[80];
    strftime(dateTime, 80, "%Y-%m-%d %H:%M:%S", localTime);

    // Open the file in append mode
    ofstream transactionFile("transaction_history.txt", ios::app);
    if (transactionFile.is_open()) {
        // Record transaction details in the file
        transactionFile << "Transaction ID: " << transactionID << endl;
        transactionFile << "Items Bought: " << items << endl;
        transactionFile << "Quantity: " << quantity << endl;
        transactionFile << "Transaction Total: $" << fixed << setprecision(2) << total << endl;
        transactionFile << "Date and Time: " << dateTime << endl;
        transactionFile << "--------------------------------------------\n";

        cout << "Transaction recorded successfully.\n";
        transactionFile.close();
    } else {
        cerr << "Error opening transaction file.\n";
    }
}

void displaySalesData() {
    cout << "\nSales Data from Transaction History:\n";

    // Open the transaction details file
    ifstream transactionFile("transaction_history.txt");
    if (transactionFile.is_open()) {
        string line;
        while (getline(transactionFile, line)) {
            cout << line << endl;
        }
        transactionFile.close();
    } else {
        cerr << "Error opening transaction file.\n";
    }
}
