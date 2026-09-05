#pragma once
#include <iostream>
#include <string>
using namespace std;

class TicketPrinter {
private:
    string ticketFormat;

public:
    TicketPrinter(string format = "PDF") : ticketFormat(format) {}

    void printTicket(int bookingId, const string& customerName, const string& movieTitle,
                     const string& showTime, const string& seatInfo, double amount) const {
        cout << "\n╔══════════════════════════════════════════════════════╗\n"
             << "║                  MOVIE TICKET                       ║\n"
             << "╠══════════════════════════════════════════════════════╣\n"
             << "║  Booking ID   : " << bookingId << "\n"
             << "║  Customer     : " << customerName << "\n"
             << "║  Movie        : " << movieTitle << "\n"
             << "║  Show Time    : " << showTime << "\n"
             << "║  Seats        : " << seatInfo << "\n"
             << "║  Total Amount : Rs. " << amount << "\n"
             << "║  Format       : " << ticketFormat << "\n"
             << "║  Status       : CONFIRMED\n"
             << "╚══════════════════════════════════════════════════════╝\n";
    }

    void generatePDF(int bookingId) const {
        cout << "Generating PDF ticket: Ticket_" << bookingId << ".pdf\n";
    }

    void setTicketFormat(const string& format) { ticketFormat = format; }
};