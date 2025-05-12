// src/VeganRecipe.cpp
#include "VeganRecipe.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

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
        for (LinkedList<Ingredient>::const_iterator it = ingredients.begin(); it != ingredients.end(); ++it) {
            std::cout << "  - " << it->getName() << std::endl;
        }
    }
    std::cout << "==================" << std::endl;
}

bool VeganRecipe::isValidForDiet(const Ingredient& ingredient) const {
    // List of non-vegan ingredients
    static const std::unordered_set<std::string> nonVeganIngredients = {
        "milk", "cheese", "butter", "cream", "yogurt", "honey", "eggs", "meat", "beef", "pork", "chicken", "fish",
        "seafood", "lard", "gelatin", "whey", "casein", "lactose", "shellfish", "poultry"
    };

    std::string lowerName = ingredient.getName();
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    return nonVeganIngredients.find(lowerName) == nonVeganIngredients.end();
}
