#pragma once
#include <iostream>
#include <string>
using namespace std;

class ShowSeat {
private:
    int showSeatId;
    int showId;
    int seatId;
    string status;   // "AVAILABLE", "BOOKED", "RESERVED"

public:
    ShowSeat(int id, int sId, int seId)
        : showSeatId(id), showId(sId), seatId(seId), status("AVAILABLE") {}

    bool book() {
        if (status == "AVAILABLE") {
            status = "BOOKED";
            return true;
        }
        return false;
    }

    bool cancel() {
        if (status == "BOOKED") {
            status = "AVAILABLE";
            return true;
        }
        return false;
    }

    string getStatus() const { return status; }
    int getShowSeatId() const { return showSeatId; }
    int getShowId() const { return showId; }
    int getSeatId() const { return seatId; }
};