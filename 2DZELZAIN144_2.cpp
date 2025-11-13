#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BankAccount {
protected:
    string ownerName;
    int accountNumber;
    double balance;

private:
    bool isValidAmount(double amount) const {
        return amount > 0.0;
    }

public:
    BankAccount(const string& owner, int number, double startBalance)
        : ownerName(owner), accountNumber(number), balance(startBalance) {
    }

    virtual ~BankAccount() {}

    virtual void deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
        }
        else {
            cout << "Invalid deposit amount.\n";
        }
    }

    virtual bool withdraw(double amount) {
        if (!isValidAmount(amount)) {
            cout << "Invalid withdraw amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Not enough funds.\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    virtual void displayInfo() const {
        cout << "Owner: " << ownerName
            << ", Account number: " << accountNumber
            << ", Balance: " << fixed << setprecision(2) << balance << '\n';
    }

    BankAccount& operator+=(double amount) {
        deposit(amount);
        return *this;
    }

    BankAccount& operator-=(double amount) {
        withdraw(amount);
        return *this;
    }

    bool operator>(const BankAccount& other) const {
        return balance > other.balance;
    }
};

class SavingsAccount : public BankAccount {
    double interestRate; // 0.05 = 5%
public:
    SavingsAccount(const string& owner, int number, double startBalance,
        double rate)
        : BankAccount(owner, number, startBalance), interestRate(rate) {
    }

    void deposit(double amount) override {
        if (!amount) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        double withInterest = amount + amount * interestRate;
        balance += withInterest;
    }

    void displayInfo() const override {
        cout << "Owner: " << ownerName
            << ", Account number: " << accountNumber
            << ", Balance: " << fixed << setprecision(2) << balance
            << ", Interest rate: " << interestRate * 100 << "%\n";
    }

    SavingsAccount operator+(const SavingsAccount& other) const {
        double newBalance = balance + other.balance;
        double newRate = (interestRate + other.interestRate) / 2.0;
        return SavingsAccount("Merged account", 0, newBalance, newRate);
    }
};

void processTransaction(BankAccount& account, double amount) {
    account.deposit(amount);
}

bool processTransaction(BankAccount& from, BankAccount& to, double amount) {
    if (from.withdraw(amount)) {
        to.deposit(amount);
        return true;
    }
    return false;
}

int main() {
    BankAccount    acc1("Alice", 1001, 500.0);
    SavingsAccount sav1("Bob", 2001, 1000.0, 0.05);
    SavingsAccount sav2("Charlie", 2002, 300.0, 0.03);

    BankAccount* accounts[3] = { &acc1, &sav1, &sav2 };

    cout << "Initial accounts:\n";
    for (int i = 0; i < 3; ++i)
        accounts[i]->displayInfo();
    cout << '\n';

    processTransaction(acc1, 200.0);
    processTransaction(sav1, sav2, 150.0);

    sav1 += 50.0;
    acc1 -= 100.0;

    SavingsAccount merged = sav1 + sav2;

    cout << "After operations:\n";
    for (int i = 0; i < 3; ++i)
        accounts[i]->displayInfo();
    cout << '\n';

    cout << "Merged savings account:\n";
    merged.displayInfo();
    cout << '\n';

    cout << "Compare balances (Alice vs Bob):\n";
    if (acc1 > sav1)
        cout << "Alice has more money than Bob.\n";
    else
        cout << "Bob has more or equal money than Alice.\n";
    cout << '\n';

    cout << "Final state (polymorphic displayInfo):\n";
    for (int i = 0; i < 3; ++i)
        accounts[i]->displayInfo();

    return 0;
}
