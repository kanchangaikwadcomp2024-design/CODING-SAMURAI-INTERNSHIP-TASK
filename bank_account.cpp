#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    void createAccount();
    void showAccount() const;
    void deposit(double amount);
    bool withdraw(double amount);
    int getAccountNumber() const;
};

/* -------- Class Functions -------- */

void BankAccount::createAccount() {
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    cout << "Enter Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Enter Initial Balance: ";
    cin >> balance;
}

void BankAccount::showAccount() const {
    cout << "\nAccount Number: " << accountNumber;
    cout << "\nAccount Holder Name: " << name;
    cout << "\nBalance: Rs. " << balance << endl;
}

void BankAccount::deposit(double amount) {
    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

/* -------- File Functions -------- */

void writeAccount() {
    BankAccount acc;
    ofstream outFile("accounts.dat", ios::binary | ios::app);

    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));
    outFile.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAll() {
    BankAccount acc;
    ifstream inFile("accounts.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        acc.showAccount();
        cout << "\n------------------------";
    }

    inFile.close();
}

void modifyAccount(int accNo, int type) {
    BankAccount acc;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccountNumber() == accNo) {

            double amount;
            cout << "Enter Amount: ";
            cin >> amount;

            if (type == 1) {
                acc.deposit(amount);
                cout << "\nDeposit Successful!\n";
            }
            else {
                if (acc.withdraw(amount))
                    cout << "\nWithdrawal Successful!\n";
                else {
                    cout << "\nInsufficient Balance!\n";
                    file.close();
                    return;
                }
            }

            file.seekp(file.tellg() - streampos(sizeof(acc)));
            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

void transferFunds(int fromAcc, int toAcc, double amount) {
    BankAccount acc;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);

    bool fromFound = false, toFound = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {

        if (acc.getAccountNumber() == fromAcc) {
            if (!acc.withdraw(amount)) {
                cout << "\nInsufficient Balance!\n";
                file.close();
                return;
            }

            file.seekp(file.tellg() - streampos(sizeof(acc)));
            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));
            fromFound = true;
        }

        if (acc.getAccountNumber() == toAcc) {
            acc.deposit(amount);

            file.seekp(file.tellg() - streampos(sizeof(acc)));
            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));
            toFound = true;
        }
    }

    if (fromFound && toFound)
        cout << "\nTransfer Successful!\n";
    else
        cout << "\nTransfer Failed!\n";

    file.close();
}

/* -------- Main Function -------- */

int main() {
    int choice;

    do {
        cout << "\n\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Transfer Money";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;

        case 2:
            displayAll();
            break;

        case 3: {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 1);
            break;
        }

        case 4: {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 2);
            break;
        }

        case 5: {
            int fromAcc, toAcc;
            double amount;
            cout << "From Account: ";
            cin >> fromAcc;
            cout << "To Account: ";
            cin >> toAcc;
            cout << "Amount: ";
            cin >> amount;
            transferFunds(fromAcc, toAcc, amount);
            break;
        }

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}


