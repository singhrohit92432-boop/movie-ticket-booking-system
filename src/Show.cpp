#pragma once
#include <iostream>
#include <string>
using namespace std;

class Show {
private:
    int showId;
    int movieId;
    int screenId;
    string showTime;
    string date;

public:
    Show(int id, int mId, int sId, string time, string d)
        : showId(id), movieId(mId), screenId(sId), showTime(time), date(d) {}

    void getAvailableSeats() const {
        cout << "Show ID: " << showId << "\n"
             << "Date: " << date << "  Time: " << showTime << "\n"
             << "Checking seat availability...\n";
    }

    int getShowId() const { return showId; }
    int getMovieId() const { return movieId; }
    int getScreenId() const { return screenId; }
    string getShowTime() const { return showTime; }
    string getDate() const { return date; }
};