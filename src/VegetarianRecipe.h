// src/VegetarianRecipe.h
#pragma once // Prevent multiple inclusions

#include "Recipe.h"

class VegetarianRecipe : public Recipe {
public:
    // Constructor - forwards to base and sets specific DietType
    VegetarianRecipe(const std::string& title = "", 
       int prepTime = 0, 
       MealType mealType = MealType::Other);

    // Override the display method
    void display() const override;

    // Virtual destructor
    virtual ~VegetarianRecipe() = default;

    // Added getTypeString method
    std::string getTypeString() const override { return "Vegetarian"; }

    // Added isValidForDiet method
    bool isValidForDiet(const Ingredient& ingredient) const override;
};
