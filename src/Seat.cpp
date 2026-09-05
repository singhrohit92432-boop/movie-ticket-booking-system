#pragma once
#include <iostream>
#include <string>
using namespace std;

class Seat {
private:
    int seatId;
    char rowNumber;
    int seatNumber;
    string type;   // "Silver", "Gold", "Platinum"
    bool isBooked;

public:
    Seat(int id, char row, int num, string t)
        : seatId(id), rowNumber(row), seatNumber(num), type(t), isBooked(false) {}

    void book() {
        isBooked = true;
        cout << "Seat " << rowNumber << seatNumber << " booked.\n";
    }

    void unbook() {
        isBooked = false;
        cout << "Seat " << rowNumber << seatNumber << " unbooked.\n";
    }

    bool isAvailable() const { return !isBooked; }

    string getSeatInfo() const {
        return string(1, rowNumber) + to_string(seatNumber) + " (" + type + ")";
    }

    int getSeatId() const { return seatId; }
    string getType() const { return type; }
};