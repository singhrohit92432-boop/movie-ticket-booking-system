#pragma once
#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    int movieId;
    string title;
    string genre;
    int duration;     // minutes
    string language;
    float rating;

public:
    Movie(int id, string t, string g, int d, string lang, float r)
        : movieId(id), title(t), genre(g), duration(d), language(lang), rating(r) {}

    void getDetails() const {
        cout << "Movie ID: " << movieId << "\n"
             << "Title: " << title << "\n"
             << "Genre: " << genre << "\n"
             << "Duration: " << duration << " min\n"
             << "Language: " << language << "\n"
             << "Rating: " << rating << "/10\n";
    }

    // Getters
    int getMovieId() const { return movieId; }
    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    int getDuration() const { return duration; }
    string getLanguage() const { return language; }
    float getRating() const { return rating; }
};