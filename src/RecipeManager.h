#pragma once

#include "Recipe.h"
#include <memory>

class RecipeManager {
public:
    // Creates a new recipe by guiding the user through a streamlined input process
    // Returns a unique_ptr to the created Recipe object
    // Throws std::invalid_argument if input validation fails
    static std::unique_ptr<Recipe> addRecipe();
    
    // TODO: Add saveRecipe method for file I/O
    // static void saveRecipe(const Recipe& recipe);
};
