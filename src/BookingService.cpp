#pragma once
#include "Booking.cpp"
#include <iostream>
#include <vector>
using namespace std;

class BookingService {
private:
    
    vector<Booking> bookings;
    int bookingCounter;

public:
    BookingService() : bookingCounter(1000) {}

    int createBooking(int customerId, const vector<int>& showSeatIds, double amount) {
        ++bookingCounter;
        Booking newBooking(bookingCounter, customerId);
        for (int ssId : showSeatIds) {
            newBooking.addSeat(ssId);
        }
        newBooking.calculateTotal(amount);
        bookings.push_back(newBooking);
        cout << "Booking created with ID: " << bookingCounter << "\n";
        return bookingCounter;
    }

    bool cancelBooking(int bookingId) {
        for (Booking& b : bookings) {
            if (b.getBookingId() == bookingId) {
                if (b.getBookingStatus() == "Confirmed") {
                    b.cancel();
                    // Release seats – we'll let the caller handle it, but we return true.
                    return true;
                } else {
                    cout << "Booking cannot be cancelled. Current status: " << b.getBookingStatus() << "\n";
                    return false;
                }
            }
        }
        cout << "Booking ID not found.\n";
        return false;
    }

    bool confirmBooking(int bookingId) {
        for (Booking& b : bookings) {
            if (b.getBookingId() == bookingId && b.getBookingStatus() == "Pending") {
                b.confirm();
                return true;
            }
        }
        return false;
    }

    void viewBooking(int bookingId) const {
        for (const Booking& b : bookings) {
            if (b.getBookingId() == bookingId) {
                b.generateTicket();
                return;
            }
        }
        cout << "Booking not found.\n";
    }

    // For external retrieval of bookings (used in viewTickets)
    const vector<Booking>& getBookings() const { return bookings; }
};