// src/VeganRecipe.h
#pragma once // Prevent multiple inclusions

#include "Recipe.h"

class VeganRecipe : public Recipe {
public:
    VeganRecipe(const std::string& title = "", 
       int prepTime = 0, 
       MealType mealType = MealType::Other);

    void display() const override;
    std::string getTypeString() const override { return "Vegan"; }
    bool isValidForDiet(const Ingredient& ingredient) const override;
    virtual ~VeganRecipe() = default;
};
