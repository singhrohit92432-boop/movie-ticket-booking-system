#pragma once
#include <iostream>
#include <string>
using namespace std;

class Payment {
protected:
    int paymentId;
    int bookingId;
    double amount;
    string method;
    string status;
    string transactionId;

public:
    Payment(int pId, int bId, double amt, string m)
        : paymentId(pId), bookingId(bId), amount(amt), method(m),
          status("Pending"), transactionId("") {}

    virtual bool processPayment() = 0;

    bool refund() {
        if (status == "Completed") {
            status = "Refunded";
            cout << "Refund processed successfully.\n";
            return true;
        }
        cout << "Refund failed: Payment not completed.\n";
        return false;
    }

    void verifyStatus() const {
        cout << "Payment Status: " << status << "\n";
    }

    int getPaymentId() const { return paymentId; }
    string getStatus() const { return status; }
    string getTransactionId() const { return transactionId; }
};