// src/PescatarianRecipe.cpp
#include "PescatarianRecipe.h"
#include <iostream>

PescatarianRecipe::PescatarianRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Pescatarian) {}

void PescatarianRecipe::display() const {
    std::cout << "=== Pescatarian Recipe ===" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    
    std::cout << "Ingredients:" << std::endl;
    if (ingredients.isEmpty()) {
        std::cout << "  (No ingredients added yet)" << std::endl;
    } else {
        for (const auto& ingredient : ingredients) {
            std::cout << "  - " << ingredient.toString() << std::endl;
        }
    }
    std::cout << "========================" << std::endl;
}
