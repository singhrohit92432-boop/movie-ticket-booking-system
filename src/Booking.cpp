#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Booking {
private:
    int bookingId;
    int customerId;
    vector<int> showSeatIds;
    double totalAmount;
    string bookingStatus;   // Pending, Confirmed, Cancelled
    time_t bookingTime;
    cout>>"hiii";

public:
    Booking(int id, int custId)
        : bookingId(id), customerId(custId), totalAmount(0),
          bookingStatus("Pending"), bookingTime(time(nullptr)) {}

    double calculateTotal(double basePrice, double taxRate = 0.18) {
        totalAmount = basePrice * (1 + taxRate);
        return totalAmount;
    }

    void confirm() {
        bookingStatus = "Confirmed";
        cout << "Booking #" << bookingId << " confirmed!\n";
    }

    void cancel() {
        bookingStatus = "Cancelled";
        cout << "Booking #" << bookingId << " cancelled.\n";
    }

    void generateTicket() const {
        cout << "\n========================================\n"
             << "          MOVIE TICKET\n"
             << "========================================\n"
             << "Booking ID : " << bookingId << "\n"
             << "Status     : " << bookingStatus << "\n"
             << "Total      : Rs. " << totalAmount << "\n"
             << "Time       : " << ctime(&bookingTime)
             << "========================================\n";
    }
    

    void addSeat(int showSeatId) {
        showSeatIds.push_back(showSeatId);
    }

    int getBookingId() const { return bookingId; }
    int getCustomerId() const { return customerId; }
    string getBookingStatus() const { return bookingStatus; }
    double getTotalAmount() const { return totalAmount; }
    vector<int> getShowSeatIds() const { return showSeatIds; }
};