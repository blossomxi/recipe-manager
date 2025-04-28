// src/VeganRecipe.cpp
#include "VeganRecipe.h"
#include <iostream>

VeganRecipe::VeganRecipe(const std::string& title, int prepTime, MealType mealType)
    : Recipe(title, prepTime, mealType, DietType::Vegan) {}

void VeganRecipe::display() const {
    // TODO: Implement display for VeganRecipe
    std::cout << "--- Vegan Recipe ---" << std::endl;
    std::cout << "Title: " << title << " (Display TODO)" << std::endl;
    std::cout << "Prep Time: " << prepTime << " minutes" << std::endl;
    std::cout << "Meal Type: " << mealTypeToString(mealType) << std::endl;
    std::cout << "Diet Type: " << dietTypeToString(dietType) << std::endl;
    std::cout << "--------------------" << std::endl;
}
