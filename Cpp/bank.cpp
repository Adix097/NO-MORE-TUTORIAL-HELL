#include <iostream>
using namespace std;

class Bank {
    private:
        double balance;
        int id;
        static int nextID;
        
    public:
        Bank (int initialBalance = 0) {
            this->balance = initialBalance;
            this->id = nextID++;
        };
        void deposit (double amount) {
            balance += amount;
            cout << "Successfully deposited " << amount << endl;
        };
        void withdraw (double amount) {
            if (balance > amount) {
                balance -= amount;
                cout << "Successfully withdrew " << amount << endl;
            } else {
                cout << "Insufficient Balance!\n";
            }
        };

        void getBalance () {
            cout << "Balance: " << balance << endl;
        };
        void getId () {
            cout << "ID: #" << id << endl;
        };
        void getDetails () {
            cout << "ID: #" << id << "\n" << "Balance: " << balance << "\n" << endl;
        }

};
int Bank::nextID = 1;


int main () {
    Bank person1(10000);
    Bank person2(5000);

    person1.deposit(1000);
    person2.withdraw(1000);

    person1.getDetails();
    person2.getDetails();
    return 0;
}

