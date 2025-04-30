// src/Ingredient.h
#pragma once

#include <string>

class Ingredient {
private:
    std::string name;
    std::string quantity; // Using string for flexibility (e.g., "2 cups", "1 pinch")

public:
    Ingredient(const std::string& name = "", const std::string& quantity = "");

    // Getters
    std::string getName() const;
    std::string getQuantity() const;

    // Setters
    void setName(const std::string& name);
    void setQuantity(const std::string& quantity);

    // Utility
    std::string toString() const;

    // Operators
    bool operator==(const Ingredient& other) const {
        return name == other.name && quantity == other.quantity;
    }
};
