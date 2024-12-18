#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Account
{
public:
    string accountNumber;
    string accountHolder;
    double balance;

    Account(string accNum, string holder) : accountNumber(accNum), accountHolder(holder), balance(0.0) {}

    void deposit(double amount)
    {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited " << amount << " TL. New balance: " << balance << " TL." << endl;
        }
        else
        {
            cout << "Invalid amount! Please enter a positive value." << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Successfully withdrew " << amount << " TL. Remaining balance: " << balance << " TL." << endl;
        }
        else
        {
            cout << "Insufficient balance or invalid amount! Current balance: " << balance << " TL." << endl;
        }
    }

    void displayBalance() const
    {
        cout << "Account Holder: " << accountHolder << ", Account Number: " << accountNumber
            << ", Balance: " << balance << " TL." << endl;
    }
};


class Bank
{
private:
    vector<Account> accounts;

public:
    void createAccount(const string& accountNumber, const string& accountHolder)
    {
        accounts.push_back(Account(accountNumber, accountHolder));
        cout << "Account successfully created. Account Number: " << accountNumber << endl;
    }

    Account* findAccount(const string& accountNumber)
    {
        for (auto& account : accounts) {
            if (account.accountNumber == accountNumber)
            {
                return &account;
            }
        }
        return nullptr;
    }

    void listAccounts() const
    {
        cout << "\n--- All Accounts ---\n";
        for (const auto& account : accounts) {
            account.displayBalance();
        }
    }

    void closeAccount(const string& accountNumber)
    {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) {
                accounts.erase(it);
                cout << "Account successfully closed: " << accountNumber << endl;
                return;
            }
        }
        cout << "Account not found!" << endl;
    }
};


int main()
{
    Bank bank;
    int choice;
    string accountNumber, accountHolder;
    double amount;

    while (true)
    {
        cout << endl;
        cout << "--- BANK AUTOMATION SYSTEM ---" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. View Balance" << endl;
        cout << "5. List All Accounts" << endl;
        cout << "6. Close Account" << endl;
        cout << "7. Exit" << endl;
        cout << endl;
        cout << "Make your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Account Holder Name: ";
            cin >> accountHolder;
            bank.createAccount(accountNumber, accountHolder);
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            if (Account* depositAccount = bank.findAccount(accountNumber)) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                depositAccount->deposit(amount);
            }
            else
            {
                cout << "Account not found!" << endl;
            }
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            if (Account* withdrawAccount = bank.findAccount(accountNumber)) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                withdrawAccount->withdraw(amount);
            }
            else
            {
                cout << "Account not found!" << endl;
            }
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            if (Account* balanceAccount = bank.findAccount(accountNumber)) {
                balanceAccount->displayBalance();
            }
            else
            {
                cout << "Account not found!" << endl;
            }
            break;

        case 5:
            bank.listAccounts();
            break;

        case 6:
            cout << "Enter Account Number to close: ";
            cin >> accountNumber;
            bank.closeAccount(accountNumber);
            break;

        case 7:
            cout << "Exiting the system. Have a nice day!" << endl;
            return 0;

        default:
            cout << "Invalid choice! Please enter a number between 1-7." << endl;
            break;
        }
    }

    return 0;
}
