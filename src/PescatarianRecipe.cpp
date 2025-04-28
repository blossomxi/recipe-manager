// src/PescatarianRecipe.cpp
#include "PescatarianRecipe.h"
#include <iostream>

PescatarianRecipe::PescatarianRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Pescatarian) {}

void PescatarianRecipe::display() const {
    // TODO: Implement display for PescatarianRecipe
    std::cout << "--- Pescatarian Recipe ---" << std::endl;
    std::cout << "Title: " << title << " (Display TODO)" << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    std::cout << "Diet Type: " << dietTypeToString(dietType) << std::endl;
    std::cout << "--------------------------" << std::endl;
}
