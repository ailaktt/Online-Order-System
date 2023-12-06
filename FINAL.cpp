#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MenuNumber = 12;
const string Menu[MenuNumber] = { "Hot Americano", "Hot Cafe Latte", "Hot Mocha Latte", "Hot Caramel Macchiato", "Hot French Vanilla Latte", "Hot Spanish Latte",
                                    "Iced Caramel Macchiato", "Iced French Vanilla Latte", "Iced Mocha Latte", "Iced Matcha Latte",  "Strawberry Frappe", "Chocolate Chip Frappe" };
const double Prices[MenuNumber] = { 85, 90, 105, 115, 115, 115, 115, 115, 115, 130, 145, 145 };

// Customer Detail
struct Customer {
    string Name;
    string Address;
    string ContactNumber;
};

// Menu Display
void displayMenu() {
    cout << setfill('-') << setw(45) << fixed << "" << endl;
    cout << setfill(' ') << setw(26) << "A Coffee Menu" << endl;
    cout << setfill('-') << setw(45) << "" << endl;

    for (int i = 0; i < MenuNumber; ++i) {
        cout << "[" << i + 1 << "] ";

        // To Align Menu Number 9 to 11     

        if (i == 9 || i == 10 || i == 11) {
            cout << setfill('.') << setw(30);
        }
        else {
            cout << setfill('.') << setw(31);
        }
        cout << left << Menu[i] << "  " << fixed << setprecision(2) << Prices[i] << endl;
    }
    cout << setfill('-') << setw(45) << "" << endl;
}

// Order Form
void displayOrderForm(const int order[], int count) {
    cout << "\nOrder Form:\n";
    cout << setfill('-') << setw(35) << "" << endl;
    for (int i = 0; i < count; ++i) {
        int itemIndex = order[i];
        cout << Menu[itemIndex] << " " << Prices[itemIndex] << endl;
    }
    cout << setfill('-') << setw(35) << "" << endl;
}

// Customer Information
void takeCustomerInfo(Customer& customer) {
    cout << "Enter Name: ";
    getline(cin >> ws, customer.Name);

    cout << "Enter Address: ";
    getline(cin >> ws, customer.Address);

    cout << "Enter Contact Number: ";
    getline(cin >> ws, customer.ContactNumber);

    cout << endl << setfill('-') << setw(45) << "" << endl << endl;
}

// Order Taking
void takeOrder(int order[], int& count) {
    int choice;
    do {
        displayMenu();
        displayOrderForm(order, count);

        cout << "ENTER PRODUCT CODE: (Enter 0 to Checkout): ";
        cin >> choice;

        if (choice >= 1 && choice <= MenuNumber) {

            order[count++] = choice - 1;
            cout << Menu[choice - 1] << " ADDED TO ORDER.\n";
        }
        else if (choice == 0) {
            if (count == 0) {
                cout << "NO ITEMS WERE ORDERED\n";
                continue;
            }
            cout << "PROCEEDING TO CHECKOUT.\n";
            break;
        }
        else {
            cout << "INVALID/ERROR PLEASE TRY AGAIN.\n";
        }
    } while (true);
}

// Receipt and Customer Info

void generateReceipt(int order[], int count, const Customer& customer) {
    double total = 0.0;
    int PaymentMethod = 0;

    cout << endl << setfill('-') << setw(45) << "" << endl;
    cout << "Order Receipt for " << customer.Name << ":\n";
    cout << "Address: " << customer.Address << "\n";
    cout << "Contact Number: " << customer.ContactNumber << "\n";
    cout << setfill('-') << setw(45) << "" << endl << endl;

    for (int i = 0; i < count; ++i) {
        int itemIndex = order[i];
        cout << Menu[itemIndex] << " " << Prices[itemIndex] << endl;
        total += Prices[itemIndex];
    }
    cout << setfill('-') << setw(45) << "" << endl;
    cout << "Total: " << total << endl << endl;

    // Order Confirmation

    char CheckoutChoice;
    cout << "Do you want to proceed to checkout? (Y/N)? ";
    cin >> CheckoutChoice;

    // Payment Method & Order Summary for proceeded checkout (Y)

    if (tolower(CheckoutChoice) == 'y') {

        cout << endl << setfill('-') << setw(45) << "" << endl;
        cout << "Payment Method: " << PaymentMethod << endl;
        cout << setfill('-') << setw(45) << "" << endl;
        cout << "Order Summary:\n";
        for (int i = 0; i < count; ++i) {
            int itemIndex = order[i];
            cout << Menu[itemIndex] << " " << Prices[itemIndex] << endl;
        }
        cout << setfill('-') << setw(45) << "" << endl;
        cout << "Total: " << total << endl << endl;
        cout << "Select payment method:\n";
        cout << "[1] Cash\n";
        cout << "[2] Card\n";
        cout << "[3] E-cash\n";
        cout << "Enter your payment method: ";
        cin >> PaymentMethod;
        cout << endl << setfill('-') << setw(45) << "" << endl;
        cout << "Payment Method: " << PaymentMethod << endl;
        cout << setfill('-') << setw(45) << "" << endl;
        cout << "Order Summary:\n";
        for (int i = 0; i < count; ++i) {
            int itemIndex = order[i];
            cout << Menu[itemIndex] << " " << Prices[itemIndex] << endl;
            break;
        }
        cout << setfill('-') << setw(45) << "" << endl;
        cout << "Total: " << total << endl << endl;
    }
 
    // Cash Payment Method: Amount to Be Received & Change To Be Given

    if (PaymentMethod == 1) {
        double amountPaid;
        bool CorrectAmount = false;

        do {
            cout << "Enter Cash(Enter exact amount if no change is needed): ";
            cin >> amountPaid;

            if (amountPaid >= total) {
                double change = amountPaid - total;
                cout << "Amount Paid: " << amountPaid << endl;
                cout << "Total: " << total << endl;
                cout << "Change: " << change << endl;
                cout << "Thank You for ordering!\n";
                return;
            }
            else {
                cout << "Insufficient amount. Try Again.\n";
            }
        } while (!CorrectAmount);   
    }
 

 // Payment Method & Order Summary for unproceeded checkout (N) + order limit feature
  
    else if (tolower(CheckoutChoice) == 'n') {
        int newItem;

        do {
            if (count >= 100) {
                cout << "Order limit reached. Maximum 100 only." << endl;
                    break;
            }
            displayMenu();
            displayOrderForm(order, count);

            cout << "Enter Product Code(Enter 0 to checkout): ";
            cin >> newItem;

            if (newItem != 0) {
                order[count++] = newItem - 1;
                cout << "Updated Order form.\n";
                displayOrderForm(order, count);
            }

            else {
                cout << "Returning to payment method selection...\n";
                cout << "Select payment method:\n";
                cout << "[1] Cash\n";
                cout << "[2] Card\n";
                cout << "[3] E-cash\n" << endl;
                cout << "Enter your payment method: ";

                cin >> PaymentMethod;

                cout << endl << setfill('-') << setw(45) << "" << endl;
                cout << "Payment Method: " << PaymentMethod << endl;
                cout << setfill('-') << setw(45) << "" << endl;
                cout << "Order Summary:\n";

                for (int i = 0; i < count; ++i) {
                    int itemIndex = order[i];
                    cout << Menu[itemIndex] << " " << Prices[itemIndex] << endl;
                }
                cout << setfill('-') << setw(45) << "" << endl;
                cout << "Total: " << total << endl << endl;
                
            }
        } while (newItem != 0);
    }
    else {
        cout << "Invalid Please Try Again.\n";
    }
}



int main() {
    int order[100]; // Maximum of 100 Orders
    int orderCount = 0;

    Customer customer;

    cout << setfill('-') << setw(45) << "" << endl;
    cout << "Welcome to A Coffee Online Order System!" << endl << endl;


    takeCustomerInfo(customer);
    takeOrder(order, orderCount);

    if (orderCount > 0) {
        generateReceipt(order, orderCount, customer);
    }
    else {
        cout << "No items were ordered.\n";
    }

    return 0;
}
