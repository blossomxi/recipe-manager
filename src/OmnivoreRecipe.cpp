// src/OmnivoreRecipe.cpp
#include "OmnivoreRecipe.h"
#include <iostream>

OmnivoreRecipe::OmnivoreRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Omnivore) {}

void OmnivoreRecipe::display() const {
    std::cout << "=== Omnivore Recipe ===" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    
    std::cout << "Ingredients:" << std::endl;
    if (ingredients.isEmpty()) {
        std::cout << "  (No ingredients added yet)" << std::endl;
    } else {
        for (LinkedList<Ingredient>::const_iterator it = ingredients.begin(); it != ingredients.end(); ++it) {
            std::cout << "  - " << it->toString() << std::endl;
        }
    }
    std::cout << "=====================" << std::endl;
}

bool OmnivoreRecipe::isValidForDiet(const Ingredient& ingredient) const {
    // Omnivore recipes can have any ingredient except blacklisted ones
    return true;
}
