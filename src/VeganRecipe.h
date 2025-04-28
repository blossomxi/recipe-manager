// src/VeganRecipe.h
#pragma once // Prevent multiple inclusions

#include "Recipe.h"

class VeganRecipe : public Recipe {
public:
    VeganRecipe(const std::string& title = "", 
       int prepTime = 0, 
       MealType mealType = MealType::Other);

    void display() const override;
};
