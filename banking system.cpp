#include <iostream>
#include <map>
#include <vector>
#include <ctime>
using namespace std;


struct Transaction {
    string type;
    double amount;
    time_t date;
};


class Account {
public:
    int accountNumber;
    string accountHolderName;
    double balance;
    vector<Transaction> transactionHistory;

    
    Account() : accountNumber(0), accountHolderName(""), balance(0.0) {}

    
    Account(int accNo, string name, double initialDeposit) 
        : accountNumber(accNo), accountHolderName(name), balance(initialDeposit) {
        addTransaction("Initial Deposit", initialDeposit);
    }

    
    void deposit(double amount) {
        balance += amount;
        addTransaction("Deposit", amount);
        cout << "Deposited: $" << amount << ". New Balance: $" << balance << endl;
    }

    
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            addTransaction("Withdrawal", amount);
            cout << "Withdraw: $" << amount << ". New Balance: $" << balance << endl;
        }
    }

    
    void showTransactionHistory() {
        cout << "Transaction History for Account " << accountNumber << ":" << endl;
        for (const auto& transaction : transactionHistory) {
            cout << transaction.type << " of $" << transaction.amount 
                 << " on " << ctime(&transaction.date);
        }
    }

private:
    
    void addTransaction(const string& type, double amount) {
        transactionHistory.push_back({type, amount, time(nullptr)});
    }
};


class BankingSystem {
private:
    map<int, Account> accounts;

public:
    
    void createAccount(int accNo, string name, double initialDeposit) {
        if (accounts.find(accNo) == accounts.end()) {
            accounts[accNo] = Account(accNo, name, initialDeposit);
            cout << "Account created for " << name << " with Account No: " << accNo << endl;
        } else {
            cout << "Account already exists!" << endl;
        }
    }

    
    void deposit(int accNo, double amount) {
        if (accounts.find(accNo) != accounts.end()) {
            accounts[accNo].deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    
    void withdraw(int accNo, double amount) {
        if (accounts.find(accNo) != accounts.end()) {
            accounts[accNo].withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    
    void showTransactionHistory(int accNo) {
        if (accounts.find(accNo) != accounts.end()) {
            accounts[accNo].showTransactionHistory();
        } else {
            cout << "Account not found!" << endl;
        }
    }
};


int main() {
    BankingSystem bank;
    int choice, accNo;
    double amount;
    string name;

    while (true) {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Show Transaction History\n5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Deposit: $";
            cin >> amount;
            bank.createAccount(accNo, name, amount);
            break;
        case 2:
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Deposit Amount: $";
            cin >> amount;
            bank.deposit(accNo, amount);
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Withdrawal Amount: $";
            cin >> amount;
            bank.withdraw(accNo, amount);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            bank.showTransactionHistory(accNo);
            break;
        case 5:
            cout << "Exiting system. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
