#include<iostream>
using namespace std;

class BankAccount {
public:
    long long int accountNumber;
    string holderName;
    string accountType;
    double balance;

    void setDetails() {
        cout << "=============================================================" << endl;
        cout << "                    Bank Account Registration                " << endl;
        cout << "=============================================================" << endl;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        while (accountNumber <= 0) {
            cout << "Account Number must be a positive number. Please re-enter: ";
            cin >> accountNumber;
        }

        cin.ignore();
        cout << "Enter Account Holder's Full Name: ";
        getline(cin, holderName);

        cout << "Select Account Type:" << endl;
        cout << "   S - Savings Account" << endl;
        cout << "   C - Current Account" << endl;
        cout << "   F - Fixed Deposit Account" << endl;
        cout << "Enter your choice (S/C/F): ";
        cin >> accountType;

        while (accountType != "S" && accountType != "C" && accountType != "F") {
            cout << "Invalid input. Please enter a valid account type (S/C/F): ";
            cin >> accountType;
        }

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;

        while (balance <= 0) {
            cout << "Initial deposit must be positive. Please re-enter: ";
            cin >> balance;
        }

        cout << endl << "-------------------------------------------------------------" << endl;
        if (accountType == "S") {
            cout << "Savings Account has been successfully created." << endl;
        } else if (accountType == "C") {
            cout << "Current Account has been successfully created." << endl;
        } else if (accountType == "F") {
            cout << "Fixed Deposit Account has been successfully created." << endl;
        }
        cout << "-------------------------------------------------------------" << endl << endl;
    }

    void deposit() {
        double amount;
        cout << "Enter Amount to Deposit: ";
        cin >> amount;

        while (amount <= 0) {
            cout << "Deposit amount must be greater than 0. Please re-enter: ";
            cin >> amount;
        }

        balance += amount;
        cout << "Deposit successful. Updated Balance: " << balance << endl;
    }

    void withdraw() {
        double amount;
        cout << "Enter Amount to Withdraw: ";
        cin >> amount;

        while (amount <= 0) {
            cout << "Withdrawal amount must be greater than 0. Please re-enter: ";
            cin >> amount;
        }

        if (amount > balance) {
            cout << "Insufficient balance. Withdrawal denied." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful. Remaining Balance: " << balance << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    void showAccountInfo() {
        cout << endl << "------------------ Account Information ----------------------" << endl;
        cout << "Account Number     : " << accountNumber << endl;
        cout << "Account Holder Name: " << holderName << endl;
        cout << "Account Type       : " << (accountType == "S" ? "Savings" : accountType == "C" ? "Current" : "Fixed Deposit") << endl;
        cout << "Current Balance    : " << balance << endl;
        cout << "-------------------------------------------------------------" << endl;
    }
};

class SavingAccount : public BankAccount {
public:
    void calculateInterest() {
        double interest = balance * 0.05;
        cout << "Your annual interest at 5% is: " << interest << " Rupees" << endl;
    }
};

class CurrentAccount : public BankAccount {
public:
    const double overdraftLimit = 50000;

    void checkOverdraft() {
        if (balance > overdraftLimit) {
            cout << "You have exceeded the overdraft limit of Rs. 50,000." << endl;
        } else {
            cout << "You are within the overdraft limit. Your balance is: " << balance << endl;
        }
    }
};

class FixedDeposit : public BankAccount {
public:
    int years;
    float interestRate = 0.15; // 15% per year
    float interest;

    void calculateInterest() {
        cout << "Enter Time Duration (In Years): ";
        cin >> years;

        interest = (balance * interestRate) * years;

        cout << endl;
        cout << "Your bank will provide Rs. " << interest << " interest in " << years << " years." << endl << endl;
    }

  void withdraw() {
    cout << "Enter the number of years you have completed with the Fixed Deposit: ";
    cin >> years;

    if (years >= 1) {
        float withdrawalAmount;
        cout << "You are eligible to withdraw your balance." << endl;
        cout << "Enter the amount you want to withdraw: ";
        cin >> withdrawalAmount;

        if (withdrawalAmount > 0 && withdrawalAmount <= balance) {
            balance -= withdrawalAmount;
            cout << "Withdrawal successful." << endl;
            cout << "Remaining Balance: Rs. " << balance << endl;
        } else {
            cout << "Invalid amount. Please enter a value less than or equal to your balance." << endl;
        }
    } else {
        cout << "You cannot withdraw your Fixed Deposit before completing at least 1 year." << endl;
    }
}
};



int main() {
    BankAccount baseAccount;
    SavingAccount sa;
    CurrentAccount ca;
    FixedDeposit fd;

   

    // Step 1: Register a bank account
    baseAccount.setDetails();

    // Step 2: Choose functionalities based on account type
    string accType = baseAccount.accountType;
    int choice;

    if (accType == "S") {
        do {
            cout << endl << "================ SAVINGS ACCOUNT MENU =================" << endl;
            cout << "1. Deposit Money" << endl;
            cout << "2. Withdraw Money" << endl;
            cout << "3. Calculate Interest (5% Annual)" << endl;
            cout << "4. Check Balance" << endl;
            cout << "5. View Account Information" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    baseAccount.deposit();
                    break;
                case 2:
                    baseAccount.withdraw();
                    break;
                case 3:
                    sa.balance = baseAccount.getBalance();
                    sa.calculateInterest();
                    break;
                case 4:
                    cout << "Your Current Balance is: Rs. " << baseAccount.getBalance() << endl;
                    break;
                case 5:
                    baseAccount.showAccountInfo();
                    break;
                case 0:
                    cout << "Exiting Savings Account services..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }

    else if (accType == "C") {
        do {
            cout << endl << "================ CURRENT ACCOUNT MENU =================" << endl;
            cout << "1. Deposit Money" << endl;
            cout << "2. Withdraw Money" << endl;
            cout << "3. Check Overdraft Limit (Max Rs. 50,000)" << endl;
            cout << "4. Check Balance" << endl;
            cout << "5. View Account Information" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    baseAccount.deposit();
                    break;
                case 2:
                    baseAccount.withdraw();
                    break;
                case 3:
                    ca.balance = baseAccount.getBalance();
                    ca.checkOverdraft();
                    break;
                case 4:
                    cout << "Your Current Balance is: Rs. " << baseAccount.getBalance() << endl;
                    break;
                case 5:
                    baseAccount.showAccountInfo();
                    break;
                case 0:
                    cout << "Exiting Current Account services..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }

    else if (accType == "F") {
        do {
            cout << endl << "============= FIXED DEPOSIT ACCOUNT MENU =============" << endl;
            cout << "1. Deposit Money" << endl;
            cout << "2. Withdraw Money (Only after 12 months)" << endl;
            cout << "3. Calculate Interest (15% per month)" << endl;
            cout << "4. Check Balance" << endl;
            cout << "5. View Account Information" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    baseAccount.deposit();
                    break;
                case 2:
    fd.balance = baseAccount.getBalance();
    fd.withdraw();
    break;
case 3:
    fd.balance = baseAccount.getBalance();
    fd.calculateInterest();
    fd.withdraw();
    break;

                case 4:
                    cout << "Your Current Balance is: Rs. " << baseAccount.getBalance() << endl;
                    break;
                case 5:
                    baseAccount.showAccountInfo();
                    
                    break;
                case 0:
                    cout << "Exiting Fixed Deposit services..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }


    cout <<endl<< "====================================== Thankyou for visiting ????======================================"<< endl;
   

    return 0;
}
