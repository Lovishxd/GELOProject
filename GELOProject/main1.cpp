#include <iostream> //including to use input and output stream
#include <iomanip> //including to use precisions in decimal places
#include <string>      // to use strings inputs and outputs
#include <fstream>  // to store data in a file
#include <chrono>   //To use time library 
#include <ctime>  
#include <random> //random number generation 

//////////////////////////////////////
/////// All Constants Defined  //////
////////////////////////////////////
const double COFFEE_PRICE = 1.50;
const double LARGE_COFFEE_PRICE = 1.90;
const double CHEESECAKE_PRICE = 3.00;
const double COFFEE_BEANS_PRICE = 0.60;
const int MANAGER_PASSWORD = 1234;
/*static identifier to use one variable per one transaction*/
static int transactionIDCounter;

using namespace std;

//////////////////////////////////
////////Prototypes Declared//////
/////////////////////////////////
void main_menu();        //Main Menu prompt
int second_menu(int);    //Manager Menu prompt
double sellCoffee(int&); // Coffee selling function
double sellCheesecake(int&); //Cheesecake selling function
double sellCoffeeBeans(double&); //Coffee Beans Selling function
void managerActions(double, double, double, int, int, double); //Manager actions to access sales 
void orderReview(double, double, double);                     //To callback order details
void displayItemQuantities(int, int, double);                 //To store different datas and sale
void displayTotalCoffeeSold(double);
void displayTotalMoneyMade(double);
void recordTransaction(const string& items, int quantity, double total);          //To store different datas and sale
void displaySalesData(); 
int generateRandomID();

// Function for printing ASCII art pattern
void printPattern() { //Raw string defined for spacing 
    cout <<R"(                                  

                                                           ___                       _       _____        __  __            _____ _                  
                                                          |_  |                     ( )     /  __ \      / _|/ _|          /  ___| |                 
                                                            | | __ _ ___  ___  _ __ |/ ___  | /  \/ ___ | |_| |_ ___  ___  \ `--.| |__   ___  _ __   
                                                            | |/ _` / __|/ _ \| '_ \  / __| | |    / _ \|  _|  _/ _ \/ _ \  `--. | '_ \ / _ \| '_ \  
                                                        /\__/ | (_| \__ | (_) | | | | \__ \ | \__/| (_) | | | ||  __|  __/ /\__/ | | | | (_) | |_) | 
                                                        \____/ \__,_|___/\___/|_| |_| |___/  \____/\___/|_| |_| \___|\___| \____/|_| |_|\___/| .__/  
                                                                                                                                             | |     
                                                                                                                                             |_|     

)" << endl;
}

int main() {
    int choice, choice2;       //variables for choice for menu one and menu two
    double total1 = 0, total2 = 0, total3 = 0, totalCoffeeSold = 0, totalMoneyMade = 0; //All other variables defined to store items sold
    int coffeeCups = 0, cheesecakeSlices = 0;
    double coffeeBeansAmount = 0;

    do {
        // Display ASCII art pattern and main menu
        cout << "\n\t\t\t";
        printPattern();                               
        main_menu();
        // User input for main menu choice
        cout << "\tPlease enter the number corresponding to your choice: ";
        cin >> choice;
        cout <<endl;
        switch (choice) {
            case 1:
            // Sell coffee and update total
                total1 += sellCoffee(coffeeCups);
                break;
            case 2:
            // Sell cheesecake and update total
                total2 += sellCheesecake(cheesecakeSlices);
                break;
            case 3:
            // Sell coffee beans and update total
                total3 += sellCoffeeBeans(coffeeBeansAmount);
                break;
            case 4:
            // Review order and display total cost
                orderReview(total1, total2, total3);
                cout << "Your total including tax is: $" << fixed << setprecision(2) << (total1 + total2 + total3) + ((total1 + total2 + total3) * 0.07) << endl;
                break;
            case 5:
             // Display help options
                cout << "You chose Option 5. What can I help you with?\n\n";
                cout << "\t1. Manager Login.\n\n";
                cout << "\t2. Employee Clock-in/out\n\n";
                cout << "\t3. Call Assistance\n\n";
                cout << "\t4. EXIT\n\n";
                cout << "Enter the number corresponding to your choice: ";
                cin >> choice2;
                cout << endl;
                if (choice2 == 1) {
                     // Handle manager actions
                    second_menu(choice2);
                    managerActions(total1, total2, total3, coffeeCups, cheesecakeSlices, coffeeBeansAmount);
                } else if (choice2 == 4) {
                    // Exit the program
                    cout << "Exiting program. Thank you for using Jason's Coffee Shop.\n";
                    exit(0);
                } else {
                    // Display secondary menu
                    second_menu(choice2);
                }
                break;
            case 6:
            // Record transaction and exit
                recordTransaction("Coffee, Cheesecake, Coffee Beans", coffeeCups + cheesecakeSlices + coffeeBeansAmount, totalMoneyMade);
                cout << "\tThank you for shopping with us. Your order should be ready within 20 minutes.\n";
                exit(0);
                break;
            default:// Invalid choice
                cout << "Invalid Choice. Please retry.\n";
        }

        totalCoffeeSold = total1 + total2 + total3;
        // Update total coffee sold and total money made
        totalMoneyMade = (total1 + total2 + total3) + ((total1 + total2 + total3) * 0.07);

    } while (choice != 5 && choice != 6);

    return 0;
}
// Function to display the main menu
void main_menu() {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());         // Get current time
    string currentTime = ctime(&now);

    // Display main menu
    cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\tWelcome to Jason's Coffee Shop\t" << "\t\t\t\t\t\t\t\t" << currentTime;
    cout << "\t\t\t\t\t\t\t\t\t\t--------------------------------------------\n";
    cout << "\tWhat would you like to buy today?\n\n";
    cout << "\tOur Menu options are: \n\n";
    cout << "\t1. Coffee\n\n";
    cout << "\t2. Cheesecake\n\n";
    cout << "\t3. Coffee Beans\n\n";
    cout << "\t4. Review Order\n\n";
    cout << "\t5. Help\n\n";
    cout << "\t6. Complete\n\n";
    cout << "Enter the number corresponding to your choice.\n\n";
} 
//Manager actios to put data from other functions      //Nested Functions
void managerActions(double total1, double total2, double total3, int coffeeCups, int cheesecakeSlices, double coffeeBeansAmount) {
    double totalCoffeeSold = total1 + total2 + total3;
    double totalMoneyMade = (total1 + total2 + total3) + ((total1 + total2 + total3) * 0.07);
    displayItemQuantities(coffeeCups, cheesecakeSlices, coffeeBeansAmount);
    displayTotalCoffeeSold(totalCoffeeSold);
    displayTotalMoneyMade(totalMoneyMade);
    displaySalesData();
}
//Display Sales
void displayItemQuantities(int coffeeCups, int cheesecakeSlices, double coffeeBeansAmount) {
    cout << "Quantities Sold:\n";
    cout << "Coffee Cups: " << coffeeCups << " cups\n";
    cout << "Cheesecake Slices: " << cheesecakeSlices << " slices\n";
    cout << "Coffee Beans: " << coffeeBeansAmount << " ounces\n";
    cout << "-------------------------\n";
}
//Display Sales
void displayTotalCoffeeSold(double totalCoffee) {
    cout << "Total Coffee Sold: " << totalCoffee << " cups\n";
    cout << "-------------------------\n";
}
//Display Total Money
void displayTotalMoneyMade(double totalMoney) {
    cout << "Total Money Made: $" << fixed << setprecision(2) << totalMoney << "\n";
    cout << "-------------------------\n";
}
// Function to handle manager-specific actions
int second_menu(int choice2) {
    if (choice2 == 1) {
        int correctPassword = MANAGER_PASSWORD;           //password checker
        int userPassword;              //to input user a password
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
        cout << "Enter your clock-in ID: ";               //clockin Id
        cin >> id1;
        cout << "Successfully clocked in ID number: " << id1 << endl;
    } else if (choice2 == 3) {
        cout << "An associate is headed your way. Thank you.\n";         
    } else {
        return 0;
    }
    return 0;
}
// Function for selling coffee
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
    int transactionID = generateRandomID();

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
        cerr << "Error opening transaction file.\n";        //cerr to print error lines used in C++
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
//This function generates random number in as a unique transaction Id for every purchase,.
int generateRandomID(){
    random_device rd;     //generates a seed
    mt19937 gen(rd());         //generates a random number using Mersenne Twister
    uniform_int_distribution<> dis(10000, 999999); //giving the range to generate a random number
    return dis(gen);
}