#pragma once

#include "Recipe.h"
#include <memory>
#include <string>

class RecipeManager {
public:
    // Interactive version
    static std::unique_ptr<Recipe> addRecipe();
    // UML-compliant static factory
    static std::unique_ptr<Recipe> addRecipe(const std::string& title, int prepTime, MealType mealType, DietType dietType);
    // Static file I/O methods
    static LinkedList<std::unique_ptr<Recipe>> loadFromFile(const std::string& filename);
    static void saveToFile(const std::string& filename, const LinkedList<std::unique_ptr<Recipe>>& recipes);
};
