#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

// Include all class definitions (NO HEADERS)
#include "Movie.cpp"
#include "Screen.cpp"
#include "Seat.cpp"
#include "Show.cpp"
#include "ShowSeat.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "UPIPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

// -------------------- Global Data --------------------------
vector<Movie> movies;
vector<Screen> screens;
vector<Show> shows;
vector<ShowSeat> showSeats;
vector<Customer> customers;
BookingService bookingService;   // contains bookings

// Price constants
const double SILVER_PRICE = 150.0;
const double GOLD_PRICE   = 250.0;
const double PLATINUM_PRICE = 400.0;

// Helper to get seat type from row letter
string getSeatTypeFromRow(char row) {
    if (row == 'A') return "Platinum";
    if (row == 'B') return "Gold";
    return "Silver";
}

double getPriceForSeatType(const string& type) {
    if (type == "Platinum") return PLATINUM_PRICE;
    if (type == "Gold") return GOLD_PRICE;
    return SILVER_PRICE;
}

// -------------------- Feature Functions --------------------

void listMovies() {
    cout << "\n===== CURRENT MOVIES =====\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << "[" << (i+1) << "] " << movies[i].getTitle()
             << " (" << movies[i].getLanguage() << ") "
             << movies[i].getDuration() << " min\n";
    }
}

void listShowsForMovie(int movieIndex) {
    if (movieIndex < 0 || movieIndex >= (int)movies.size()) {
        cout << "Invalid movie selection.\n";
        return;
    }
    int movieId = movies[movieIndex].getMovieId();
    cout << "\n===== SHOWS FOR " << movies[movieIndex].getTitle() << " =====\n";
    int count = 0;
    for (const Show& s : shows) {
        if (s.getMovieId() == movieId) {
            ++count;
            cout << "[" << count << "] Screen-" << s.getScreenId()
                 << " at " << s.getShowTime() << " (Date: " << s.getDate() << ")\n";
        }
    }
    if (count == 0) cout << "No shows available for this movie.\n";
}

void displaySeatLayout(int showId) {
    Show* selectedShow = nullptr;
    for (auto& s : shows) {
        if (s.getShowId() == showId) { selectedShow = &s; break; }
    }
    if (!selectedShow) {
        cout << "Show not found.\n";
        return;
    }

    // Get all ShowSeats for this show
    vector<ShowSeat> showSeatsForShow;
    for (auto& ss : showSeats) {
        if (ss.getShowId() == showId)
            showSeatsForShow.push_back(ss);
    }

    cout << "\n===== SEAT LAYOUT ( [ ] = AVAILABLE, [X] = BOOKED ) =====\n";
    cout << "      1    2    3    4\n";
    char rows[] = {'A', 'B', 'C'};
    for (int r = 0; r < 3; ++r) {
        cout << rows[r] << "  ";
        for (int c = 0; c < 4; ++c) {
            int seatNumber = r * 4 + c + 1;
            string status = "AVAILABLE";
            for (const auto& ss : showSeatsForShow) {
                if (ss.getSeatId() == seatNumber) {
                    status = ss.getStatus();
                    break;
                }
            }
            if (status == "BOOKED") cout << " [X] ";
            else cout << " [ ] ";
        }
        cout << "\n";
    }
    cout << "Legend: Platinum (Row A), Gold (Row B), Silver (Row C)\n";
}

void bookTicket() {
    cout << "\n===== BOOK A TICKET =====\n";

    // 1. List movies
    listMovies();
    int movieChoice;
    cout << "Choose movie number: ";
    cin >> movieChoice;
    if (movieChoice < 1 || movieChoice > (int)movies.size()) {
        cout << "Invalid movie number.\n";
        return;
    }
    int movieId = movies[movieChoice-1].getMovieId();

    // 2. List shows for that movie
    listShowsForMovie(movieChoice-1);
    vector<Show> availableShows;
    for (const Show& s : shows) {
        if (s.getMovieId() == movieId) availableShows.push_back(s);
    }
    if (availableShows.empty()) {
        cout << "No shows available.\n";
        return;
    }
    int showChoice;
    cout << "Choose show number: ";
    cin >> showChoice;
    if (showChoice < 1 || showChoice > (int)availableShows.size()) {
        cout << "Invalid show number.\n";
        return;
    }
    Show selectedShow = availableShows[showChoice-1];
    int showId = selectedShow.getShowId();

    // 3. Display seat layout
    displaySeatLayout(showId);

    // 4. Ask for seats
    cout << "Enter seat numbers (e.g., A1,B2,C3): ";
    string input;
    cin.ignore();
    getline(cin, input);

    vector<string> seatTokens;
    string token;
    for (char ch : input) {
        if (ch == ',') {
            if (!token.empty()) { seatTokens.push_back(token); token.clear(); }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) seatTokens.push_back(token);

    vector<int> seatIds;
    bool invalid = false;
    for (const string& s : seatTokens) {
        if (s.length() < 2) { cout << "Invalid seat format: " << s << "\n"; invalid = true; break; }
        char row = toupper(s[0]);
        int number = stoi(s.substr(1));
        int rowOffset = (row == 'A') ? 0 : (row == 'B') ? 4 : (row == 'C') ? 8 : -1;
        if (rowOffset == -1) { cout << "Invalid row: " << row << "\n"; invalid = true; break; }
        int seatNum = rowOffset + number;
        if (seatNum < 1 || seatNum > 12) { cout << "Seat out of range: " << s << "\n"; invalid = true; break; }
        seatIds.push_back(seatNum);
    }
    if (invalid || seatIds.empty()) { cout << "Booking cancelled.\n"; return; }

    // 5. Check availability
    vector<int> showSeatIds;
    bool allAvailable = true;
    for (int seatId : seatIds) {
        bool found = false;
        for (auto& ss : showSeats) {
            if (ss.getShowId() == showId && ss.getSeatId() == seatId) {
                found = true;
                if (ss.getStatus() == "AVAILABLE") {
                    showSeatIds.push_back(ss.getShowSeatId());
                } else {
                    cout << "Seat " << seatId << " is already BOOKED.\n";
                    allAvailable = false;
                }
                break;
            }
        }
        if (!found) {
            cout << "Seat " << seatId << " not found in this show.\n";
            allAvailable = false;
        }
    }
    if (!allAvailable) { cout << "Booking rejected: one or more seats unavailable.\n"; return; }

    // 6. Calculate price
    double total = 0.0;
    for (int seatId : seatIds) {
        char row = 'A' + (seatId-1)/4;
        string type = getSeatTypeFromRow(row);
        total += getPriceForSeatType(type);
    }
    cout << "Total amount: Rs. " << total << "\n";

    // 7. Payment
    cout << "Pay by: 1. UPI  2. Card  3. Cash\n";
    int payOption;
    cin >> payOption;
    bool paymentSuccess = false;
    switch (payOption) {
        case 1: {
            string upiId;
            cout << "Enter UPI ID (e.g., user@paytm): ";
            cin >> upiId;
            UPIPayment upi(5000, 0, total, upiId, "Paytm");
            paymentSuccess = upi.processPayment();
            break;
        }
        case 2: {
            string cardNo, holder, expiry, cvv;
            cout << "Enter card number: ";
            cin >> cardNo;
            cout << "Enter card holder name: ";
            cin.ignore();
            getline(cin, holder);
            cout << "Enter expiry (MM/YY): ";
            cin >> expiry;
            cout << "Enter CVV: ";
            cin >> cvv;
            CardPayment card(5001, 0, total, cardNo, holder, expiry, cvv);
            paymentSuccess = card.processPayment();
            break;
        }
        case 3: {
            double cash;
            cout << "Enter cash tendered: ";
            cin >> cash;
            CashPayment cashPay(5002, 0, total, cash);
            paymentSuccess = cashPay.processPayment();
            break;
        }
        default:
            cout << "Invalid payment option.\n";
            return;
    }

    if (!paymentSuccess) {
        cout << "Payment failed. Booking not confirmed. Seats remain available.\n";
        return;
    }

    // 8. Confirm booking
    string custName, custPhone;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, custName);
    cout << "Enter phone number: ";
    cin >> custPhone;
    int customerId = customers.size() + 1000;
    Customer newCust(customerId, custName, custPhone, "");
    customers.push_back(newCust);

    int bookingId = bookingService.createBooking(customerId, showSeatIds, total);
    bookingService.confirmBooking(bookingId);

    // Update ShowSeat status
    for (int ssId : showSeatIds) {
        for (auto& ss : showSeats) {
            if (ss.getShowSeatId() == ssId) {
                ss.book();
                break;
            }
        }
    }

    // Print ticket
    TicketPrinter printer;
    string seatInfo = "";
    for (int seatId : seatIds) {
        char row = 'A' + (seatId-1)/4;
        int num = (seatId-1) % 4 + 1;
        if (!seatInfo.empty()) seatInfo += ", ";
        seatInfo += row + to_string(num);
    }
    string movieTitle = movies[movieChoice-1].getTitle();
    string showTime = selectedShow.getShowTime();
    printer.printTicket(bookingId, custName, movieTitle, showTime, seatInfo, total);

    cout << "\nBooking completed successfully!\n";
}

void cancelBooking() {
    cout << "\n===== CANCEL BOOKING =====\n";
    int bookingId;
    cout << "Enter Booking ID: ";
    cin >> bookingId;
    bool cancelled = bookingService.cancelBooking(bookingId);
    if (cancelled) {
        // Release seats – we need to find which ShowSeat IDs were used.
        // Since we don't store that in BookingService easily, we'll loop over bookings.
        // We'll retrieve the booking's showSeatIds and set them to AVAILABLE.
        const vector<Booking>& allBookings = bookingService.getBookings();
        for (const Booking& b : allBookings) {
            if (b.getBookingId() == bookingId) {
                for (int ssId : b.getShowSeatIds()) {
                    for (auto& ss : showSeats) {
                        if (ss.getShowSeatId() == ssId) {
                            ss.cancel(); // sets to AVAILABLE
                            break;
                        }
                    }
                }
                cout << "Seats released.\n";
                break;
            }
        }
    } else {
        cout << "Cancellation failed. Check booking ID or status.\n";
    }
}

void viewTickets() {
    cout << "\n===== YOUR TICKETS =====\n";
    string phone;
    cout << "Enter your phone number: ";
    cin >> phone;
    int custId = -1;
    for (const Customer& c : customers) {
        if (c.getPhone() == phone) { custId = c.getCustomerId(); break; }
    }
    if (custId == -1) { cout << "Customer not found.\n"; return; }

    const vector<Booking>& allBookings = bookingService.getBookings();
    bool found = false;
    for (const Booking& b : allBookings) {
        if (b.getCustomerId() == custId) {
            b.generateTicket();
            found = true;
        }
    }
    if (!found) cout << "No bookings found for this customer.\n";
}

// -------------------- Main Menu ------------------------------

int main() {
    // -------- Initialize Sample Data --------
    // Movies
    movies.emplace_back(101, "3 Idiots", "Comedy", 170, "Hindi", 8.5);
    movies.emplace_back(102, "Interstellar", "Sci-Fi", 169, "English", 8.6);

    // Screens (12 seats each)
    screens.emplace_back(1, 1, 1, 12);
    screens.emplace_back(2, 2, 1, 12);

    // Shows
    shows.emplace_back(1, 101, 1, "06:00 PM", "2026-09-10");
    shows.emplace_back(2, 101, 2, "09:00 PM", "2026-09-10");
    shows.emplace_back(3, 102, 1, "07:00 PM", "2026-09-10");

    // ShowSeats – 12 per show (total 36)
    for (int showId = 1; showId <= 3; ++showId) {
        for (int seatId = 1; seatId <= 12; ++seatId) {
            int ssId = (showId-1)*12 + seatId;
            showSeats.emplace_back(ssId, showId, seatId);
        }
    }

    // Pre-book one seat for demo (show 1, seat 3)
    for (auto& ss : showSeats) {
        if (ss.getShowId() == 1 && ss.getSeatId() == 3) {
            ss.book();
            break;
        }
    }

    // -------- Menu Loop --------
    int choice;
    do {
        cout << "\n========================================\n"
             << "  MOVIE TICKET BOOKING SYSTEM\n"
             << "========================================\n"
             << "1. List Movies   " 
             << "2. Book Ticket   "
             << "3. Cancel Booking   "
             << "4. View My Tickets   " 
             <<"0. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: listMovies(); break;
            case 2: bookTicket(); break;
            case 3: cancelBooking(); break;
            case 4: viewTickets(); break;
            case 0: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}