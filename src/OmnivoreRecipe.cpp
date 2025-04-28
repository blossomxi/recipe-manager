// src/OmnivoreRecipe.cpp
#include "OmnivoreRecipe.h"
#include <iostream>

OmnivoreRecipe::OmnivoreRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Omnivore) {}

void OmnivoreRecipe::display() const {
    // TODO: Implement display for OmnivoreRecipe
    std::cout << "--- Omnivore Recipe ---" << std::endl;
    std::cout << "Title: " << title << " (Display TODO)" << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    std::cout << "Diet Type: " << dietTypeToString(dietType) << std::endl;
    std::cout << "-----------------------" << std::endl;
}
