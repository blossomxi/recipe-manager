// src/VeganRecipe.cpp
#include "VeganRecipe.h"
#include <iostream>

VeganRecipe::VeganRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Vegan) {}

void VeganRecipe::display() const {
    std::cout << "=== Vegan Recipe ===" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    
    std::cout << "Ingredients:" << std::endl;
    if (ingredients.isEmpty()) {
        std::cout << "  (No ingredients added yet)" << std::endl;
    } else {
        for (const auto& ingredient : ingredients) {
            std::cout << "  - " << ingredient.getName() << std::endl;
        }
    }
    std::cout << "==================" << std::endl;
}
