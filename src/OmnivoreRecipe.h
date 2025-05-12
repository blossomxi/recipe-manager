// src/OmnivoreRecipe.h
#pragma once

#include "Recipe.h"

class OmnivoreRecipe : public Recipe {
public:
    OmnivoreRecipe(const std::string& title = "", 
                   int prepTime = 0, 
                   MealType mealType = MealType::Other);

    void display() const override;
    std::string getTypeString() const override { return "Omnivore"; }
    bool isValidForDiet(const Ingredient& ingredient) const override;
    virtual ~OmnivoreRecipe() = default;
};
