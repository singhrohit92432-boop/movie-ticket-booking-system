#pragma once
#include <iostream>
using namespace std;

class PriceCalculator {
private:
    double basePrice;
    double taxRate;
    double discount;

public:
    PriceCalculator(double base = 200.0, double tax = 0.18, double disc = 0.0)
        : basePrice(base), taxRate(tax), discount(disc) {}

    double calculatePrice(int seatType, bool isWeekend) const {
        double price = basePrice;
        if (seatType == 1) price *= 1.8;      // Platinum
        else if (seatType == 2) price *= 1.4; // Gold
        // Silver stays base
        if (isWeekend) price *= 1.2;
        return price;
    }

    double applyDiscount(double price, double discPercent) const {
        return price * (1 - discPercent / 100);
    }

    double calculateTax(double price) const {
        return price * taxRate;
    }

    double getFinalPrice(double price) const {
        double total = price + calculateTax(price);
        total -= total * discount / 100;
        return total;
    }

    void setBasePrice(double price) { basePrice = price; }
    void setTaxRate(double rate) { taxRate = rate; }
    void setDiscount(double disc) { discount = disc; }
};