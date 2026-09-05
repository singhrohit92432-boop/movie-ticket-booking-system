#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class CashPayment : public Payment {
private:
    double cashTendered;
    double changeAmount;

public:
    CashPayment(int pId, int bId, double amt, double cash)
        : Payment(pId, bId, amt, "Cash"), cashTendered(cash), changeAmount(0) {}

    bool processPayment() override {
        cout << "Processing Cash payment...\n"
             << "Amount Due: Rs. " << amount << "\n"
             << "Cash Tendered: Rs. " << cashTendered << "\n";

        if (cashTendered >= amount) {
            changeAmount = cashTendered - amount;
            status = "Completed";
            transactionId = "CASH-" + to_string(paymentId) + "-" + to_string(time(nullptr));
            cout << "Cash payment successful!\nChange: Rs. " << changeAmount << "\n"
                 << "Transaction ID: " << transactionId << "\n";
            return true;
        } else {
            status = "Failed";
            cout << "Cash payment failed: Insufficient cash.\n"
                 << "Please provide Rs. " << (amount - cashTendered) << " more.\n";
            return false;
        }
    }

    double calculateChange() const {
        if (cashTendered >= amount) return cashTendered - amount;
        return 0;
    }
};