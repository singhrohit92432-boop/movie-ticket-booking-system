#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class UPIPayment : public Payment {
private:
    string upiId;
    string provider;

public:
    UPIPayment(int pId, int bId, double amt, string uId, string prov)
        : Payment(pId, bId, amt, "UPI"), upiId(uId), provider(prov) {}

    bool processPayment() override {
        cout << "Processing UPI payment...\n"
             << "UPI ID: " << upiId << "\n"
             << "Provider: " << provider << "\n"
             << "Amount: Rs. " << amount << "\n";

        if (upiId.find('@') != string::npos && upiId.length() > 5) {
            status = "Completed";
            transactionId = "UPI-" + to_string(paymentId) + "-" + to_string(time(nullptr));
            cout << "UPI payment successful!\nTransaction ID: " << transactionId << "\n";
            return true;
        } else {
            status = "Failed";
            cout << "UPI payment failed: Invalid UPI ID.\n";
            return false;
        }
    }

    bool validateUPIId() const {
        return upiId.find('@') != string::npos && upiId.length() > 5;
    }
};