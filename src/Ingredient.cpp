// src/Ingredient.cpp
#include "Ingredient.h"
#include <sstream>

Ingredient::Ingredient(const std::string& name, const std::string& quantity) {
    this->name = name;
    this->quantity = quantity;
}

std::string Ingredient::getName() const {
    return name;
}

std::string Ingredient::getQuantity() const {
    return quantity;
}

void Ingredient::setName(const std::string& name) {
    this->name = name;
}

void Ingredient::setQuantity(const std::string& quantity) {
    this->quantity = quantity;
}

std::string Ingredient::toString() const {
    std::ostringstream oss;
    oss << quantity << " " << name;
    return oss.str();
}
