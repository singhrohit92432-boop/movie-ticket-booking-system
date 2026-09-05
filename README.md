# 🎬 Movie Ticket Booking System

A **console-based Movie Ticket Booking System** developed in **C++** as part of the **TCS-504 System Design – Assignment 1**.

The system demonstrates object-oriented design principles by providing functionality for movie browsing, show selection, seat booking, multiple payment methods, ticket generation, and booking cancellation.

---

## 📌 Project Overview

The Movie Ticket Booking System is designed to simulate a real-world cinema booking workflow through a simple command-line interface.

Users can:

* Browse available movies and shows
* View available seats
* Select and book seats
* Make payments using multiple payment methods
* Generate and print tickets
* Cancel existing bookings

---

## ✨ Features

* 🎥 **Movie & Show Management** – View available movies and scheduled shows
* 💺 **Seat Management** – Display and select available seats
* 🎟️ **Ticket Booking** – Book seats for selected shows
* 💳 **Multiple Payment Methods** – UPI, Card, and Cash payments
* 🧾 **Ticket Generation** – Generate and display booking tickets
* ❌ **Booking Cancellation** – Cancel existing bookings
* 💰 **Price Calculation** – Calculate ticket prices based on the booking
* 🖥️ **Console-Based Interface** – Simple and easy-to-use command-line interface

---

## 🛠️ Technologies Used

* **Programming Language:** C++
* **Concepts:** Object-Oriented Programming (OOP)
* **Development Environment:** Visual Studio Code
* **Compiler:** GCC / G++
* **Version Control:** Git & GitHub

---

## 📂 Project Structure

```text
movie-ticket-booking-system/
│
├── diagrams/
│   ├── class-diagram.png
│   └── sequence-diagram.png
│
├── docs/
│   └── Assignment-1.pdf
│
├── screenshots/
│   ├── 1.png
│   ├── 2.jpeg
│   └── 3.png
│
├── src/
│   ├── Booking.cpp
│   ├── BookingService.cpp
│   ├── CardPayment.cpp
│   ├── CashPayment.cpp
│   ├── Customer.cpp
│   ├── Movie.cpp
│   ├── Payment.cpp
│   ├── PriceCalculator.cpp
│   ├── Screen.cpp
│   ├── Seat.cpp
│   ├── Show.cpp
│   ├── ShowSeat.cpp
│   ├── TicketPrinter.cpp
│   ├── UPIPayment.cpp
│   └── main.cpp
│
├── .gitignore
└── README.md
```

---

## 🧩 UML Diagrams

### Class Diagram

[![Class Diagram](diagrams/class-diagram.png)](diagrams/class-diagram.png)

### Sequence Diagram

[![Sequence Diagram](diagrams/sequence-diagram.png)](diagrams/sequence-diagram.png)

---

## 🖥️ Demo

### 1. Main Menu & Movie Listing

[![Main Menu and Movie List](screenshots/1.png)](screenshots/1.png)

### 2. Show & Seat Selection

[![Booking Flow](screenshots/2.png)](screenshots/2.png)

### 3. Payment & Ticket Confirmation

[![Payment and Ticket](screenshots/3.png)](screenshots/3.png)

---

## 🚀 How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/singhrohit92432-boop/movie-ticket-booking-system.git
cd movie-ticket-booking-system
```

### 2. Compile the Project

```bash
g++ src/main.cpp -o ticket-system
```

### 3. Run the Application

**Windows:**

```bash
.\ticket-system.exe
```

**Linux / macOS:**

```bash
./ticket-system
```

> **Note:** If the project contains multiple `.cpp` source files that are required for compilation, compile all required source files together.

---

## 💳 Payment Options

The system supports multiple payment methods:

| Payment Method | Supported |
| -------------- | --------- |
| UPI            | ✅         |
| Card           | ✅         |
| Cash           | ✅         |

---

## 🎯 System Workflow

```text
Start
  │
  ▼
View Movies
  │
  ▼
Select Show
  │
  ▼
View Available Seats
  │
  ▼
Select Seats
  │
  ▼
Calculate Price
  │
  ▼
Choose Payment Method
  │
  ▼
Confirm Booking
  │
  ▼
Generate Ticket
  │
  ▼
End
```

---

## 📚 Academic Information

**Course:** TCS-504 System Design
**Assignment:** Assignment 1
**Project:** Movie Ticket Booking System
**Language:** C++

---

## 👤 Author

**Rohit Singh**

---

## 📄 License

This project was developed for **academic and educational purposes**.
