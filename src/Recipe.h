// src/Recipe.h
#pragma once

#include <string>
#include <vector>
#include <memory> // For potential future use with smart pointers if needed
#include "Ingredient.h"

// Enumerations
enum class MealType {
    Breakfast,
    Lunch,
    Dinner,
    Snack, // Added Snack for more variety
    Dessert,
    Other
};

enum class DietType {
    Vegetarian,
    Vegan,
    Pescatarian,
    Omnivore,
    Other
};

// Helper function to convert MealType to string (optional but useful)
std::string mealTypeToString(MealType type);
MealType stringToMealType(const std::string& str);

// Helper function to convert DietType to string (optional but useful)
std::string dietTypeToString(DietType type);
DietType stringToDietType(const std::string& str);

class Recipe {
protected:
    std::string title;
    int prepTime; // Preparation time in minutes
    std::vector<Ingredient> ingredients;
    MealType mealType;
    DietType dietType;

public:
    // Constructor
    Recipe(const std::string& title = "", 
           int prepTime = 0, 
           MealType mealType = MealType::Other, 
           DietType dietType = DietType::Other);

    // Virtual destructor is crucial for base classes with virtual functions
    virtual ~Recipe() = default;

    // Abstract display method
    virtual void display() const = 0;

    // Getters
    std::string getTitle() const;
    int getPrepTime() const;
    const std::vector<Ingredient>& getIngredients() const; // Return const ref
    MealType getMealType() const;
    DietType getDietType() const;

    // Setters (basic ones)
    void setTitle(const std::string& title);
    void setPrepTime(int prepTime);
    // TODO: Add/Remove/Edit ingredients methods
    void setMealType(MealType type);
    void setDietType(DietType type);
    
    // TODO: Methods for filtering, searching (can be external functions too)
};
