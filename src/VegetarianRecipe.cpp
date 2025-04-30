// src/VegetarianRecipe.cpp
#include "VegetarianRecipe.h"
#include <iostream>

// Constructor definition
VegetarianRecipe::VegetarianRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Vegetarian) // Call base constructor, set DietType
{}

// Override display method
void VegetarianRecipe::display() const {
    std::cout << "=== Vegetarian Recipe ===" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    std::cout << "Diet Type: " << dietTypeToString(dietType) << std::endl;
    std::cout << "Ingredients:" << std::endl;
    if (ingredients.isEmpty()) {
        std::cout << "  (No ingredients added yet)" << std::endl;
    } else {
        for (const auto& ingredient : ingredients) {
            std::cout << "  - " << ingredient.toString() << std::endl;
        }
    }
    std::cout << "======================" << std::endl;
    // TODO: Add instructions display later
    std::cout << "-------------------------" << std::endl;
}
