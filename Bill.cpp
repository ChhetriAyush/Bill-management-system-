#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> // Include this header for setw and other manipulators
#include <windows.h>

using namespace std;

class Item {
public:
    string name;
    int quantity;
    float price;

    Item(string n, int q, float p) : name(n), quantity(q), price(p) {}
};

class Bill {
private:
    vector<Item> items;
    float totalAmount;

public:
    Bill() : totalAmount(0.0) {}

    void addItem(const string& name, int quantity, float price) {
        items.push_back(Item(name, quantity, price));
        totalAmount += quantity * price;
    }

    void displayBill() const {
        if (items.empty()) {
            cout << "No items in the bill.\n";
            return;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Set text color to yellow

        cout << "\n======= BILL =======\n";
        cout << left << setw(20) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << setw(10) << "Total" << endl;
        cout << "--------------------------------------------\n";

        for (const auto& item : items) {
            cout << left << setw(20) << item.name << setw(10) << item.quantity << setw(10) << item.price << setw(10) << item.quantity * item.price << endl;
        }

        cout << "--------------------------------------------\n";
        cout << left << setw(20) << "Total Amount:" << setw(10) << "" << setw(10) << "" << setw(10) << totalAmount << endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text color to white
    }

    float getTotalAmount() const {
        return totalAmount;
    }

    void saveBillToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }

        file << "======= BILL =======\n";
        file << left << setw(20) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << setw(10) << "Total" << endl;
        file << "--------------------------------------------\n";

        for (const auto& item : items) {
            file << left << setw(20) << item.name << setw(10) << item.quantity << setw(10) << item.price << setw(10) << item.quantity * item.price << endl;
        }

        file << "--------------------------------------------\n";
        file << left << setw(20) << "Total Amount:" << setw(10) << "" << setw(10) << "" << setw(10) << totalAmount << endl;
        file << "============================================\n\n";

        file.close();
    }

    static void searchBillInFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

int main() {
    Bill bill;

    int n;
    cout << "Billing System\n";
    cout << "1. Create Bill\n2. Display Bill\n3. Save Bill\n4. Search Bill\n5. Exit\n";

    do {
        cout << "Enter your choice: ";
        cin >> n;

        switch(n) {
            case 1: {
                char choice = 'y';
                while (choice != 'n' && choice != 'N') {
                    string name;
                    int quantity;
                    float price;

                    cout << "\nEnter item name: ";
                    cin >> name;

                    cout << "Enter quantity: ";
                    cin >> quantity;

                    cout << "Enter per price: ";
                    cin >> price;

                    bill.addItem(name, quantity, price);

                    cout << "\nDo you want to add more items? (y/n): ";
                    cin >> choice;
                }
                break;
            }
            case 2: {
                bill.displayBill();
                break;
            }
            case 3: {
                string filename;
                cout << "Enter filename to save the bill: ";
                cin >> filename;
                bill.saveBillToFile(filename);
                break;
            }
            case 4: {
                string filename;
                cout << "Enter filename to search the bill: ";
                cin >> filename;
                Bill::searchBillInFile(filename);
                break;
            }
            case 5:
                cout << "Thank you.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (n != 5);

    return 0;
}