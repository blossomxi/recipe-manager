// src/OmnivoreRecipe.h
#pragma once

#include "Recipe.h"

class OmnivoreRecipe : public Recipe {
public:
    OmnivoreRecipe(const std::string& title = "", 
                   int prepTime = 0, 
                   MealType mealType = MealType::Other);

    void display() const override;
    virtual ~OmnivoreRecipe() = default;
};
