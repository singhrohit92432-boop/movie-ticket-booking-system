#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class CardPayment : public Payment {
private:
    string cardNumber;
    string cardHolder;
    string expiry;
    string cvv;

public:
    CardPayment(int pId, int bId, double amt, string cardNo, string holder, string exp, string c)
        : Payment(pId, bId, amt, "Card"), cardNumber(cardNo), cardHolder(holder),
          expiry(exp), cvv(c) {}

    bool processPayment() override {
        cout << "Processing Card payment...\n"
             << "Card Type: " << (cardNumber[0] == '4' ? "Visa" : "MasterCard") << "\n"
             << "Card Holder: " << cardHolder << "\n"
             << "Amount: Rs. " << amount << "\n";

        if (cardNumber.length() >= 16 && cvv.length() == 3) {
            status = "Completed";
            transactionId = "CARD-" + to_string(paymentId) + "-" + to_string(time(nullptr));
            cout << "Card payment successful!\nTransaction ID: " << transactionId << "\n";
            return true;
        } else {
            status = "Failed";
            cout << "Card payment failed: Invalid card details.\n";
            return false;
        }
    }

    bool validateCard() const {
        return cardNumber.length() >= 16 && cvv.length() == 3;
    }
};