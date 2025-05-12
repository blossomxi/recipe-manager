#pragma once

#include "Recipe.h"
#include <string>

class RecipeManager {
public:
    // Interactive version
    static Recipe* addRecipe();
    // UML-compliant static factory
    static Recipe* addRecipe(const std::string& title, int prepTime, MealType mealType, DietType dietType);
    // Static file I/O methods
    static LinkedList<Recipe*> loadFromFile(const std::string& filename);
    static void saveToFile(const std::string& filename, const LinkedList<Recipe*>& recipes);
};
