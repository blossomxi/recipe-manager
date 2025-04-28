// src/PescatarianRecipe.h
#pragma once

#include "Recipe.h"

class PescatarianRecipe : public Recipe {
public:
    PescatarianRecipe(const std::string& title = "", 
                      int prepTime = 0, 
                      MealType mealType = MealType::Other);

    void display() const override;
};
