// src/VegetarianRecipe.cpp
#include "VegetarianRecipe.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

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
    std::cout << "-------------------------" << std::endl;
}

bool VegetarianRecipe::isValidForDiet(const Ingredient& ingredient) const {
    // List of non-vegetarian ingredients
    static const std::unordered_set<std::string> nonVegetarianIngredients = {
        "meat", "beef", "pork", "chicken", "fish", "seafood", "lard", "gelatin", "shellfish", "poultry"
    };

    std::string lowerName = ingredient.getName();
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    return nonVegetarianIngredients.find(lowerName) == nonVegetarianIngredients.end();
}
