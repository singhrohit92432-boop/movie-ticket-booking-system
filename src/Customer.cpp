#pragma once
#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;
    string email;

public:
    Customer(int id, string n, string p, string e)
        : customerId(id), name(n), phone(p), email(e) {}

    void createBooking() const {
        cout << "Booking created for customer: " << name << "\n";
    }

    void cancelBooking() const {
        cout << "Booking cancelled for customer: " << name << "\n";
    }

    void viewHistory() const {
        cout << "Viewing booking history for: " << name << "\n";
    }

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
};