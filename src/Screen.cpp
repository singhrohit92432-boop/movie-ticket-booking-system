#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Screen {
private:
    int screenId;
    int screenNumber;
    int cinemaId;
    int capacity;
    vector<bool> seatAvailability;

public:
    Screen(int id, int num, int cineId, int cap)
        : screenId(id), screenNumber(num), cinemaId(cineId), capacity(cap) {
        seatAvailability.resize(cap, true);
    }

    void getSeatMap() const {
        cout << "Screen " << screenNumber << " - Seat Map\n"
             << "Total Capacity: " << capacity << "\n";
        int available = 0;
        for (bool s : seatAvailability) if (s) ++available;
        cout << "Available Seats: " << available << "\n"
             << "Booked Seats: " << (capacity - available) << "\n";
    }

    bool checkAvailability(int seatNumber) const {
        if (seatNumber < 0 || seatNumber >= capacity) return false;
        return seatAvailability[seatNumber];
    }

    bool bookSeat(int seatNumber) {
        if (seatNumber < 0 || seatNumber >= capacity || !seatAvailability[seatNumber])
            return false;
        seatAvailability[seatNumber] = false;
        return true;
    }

    void unbookSeat(int seatNumber) {
        if (seatNumber >= 0 && seatNumber < capacity)
            seatAvailability[seatNumber] = true;
    }

    int getScreenId() const { return screenId; }
    int getCapacity() const { return capacity; }
    int getScreenNumber() const { return screenNumber; }
};