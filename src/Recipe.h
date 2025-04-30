// src/Recipe.h
#pragma once

#include <string>
#include "Ingredient.h"
#include "LinkedList.h"

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
    LinkedList<Ingredient> ingredients;
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

    // Copy constructors for Rule of Three
    Recipe(const Recipe& copy);
    Recipe& operator=(const Recipe& copy);

    // Abstract display method
    virtual void display() const = 0; // TODO: Implement display() in each derived class

    // Getters
    std::string getTitle() const;
    int getPrepTime() const;
    const LinkedList<Ingredient>& getIngredients() const; // Return const ref
    MealType getMealType() const;
    DietType getDietType() const;

    // Setters (basic ones)
    void setTitle(const std::string& title);
    void setPrepTime(int prepTime);
    // Ingredient management methods
    void addIngredient(const Ingredient& ingredient);
    void removeIngredient(const std::string& ingredientName);
    void editIngredient(const std::string& oldName, const Ingredient& newIngredient);
    
    void setMealType(MealType type);
    void setDietType(DietType type);
    
    // Search methods
    bool matchesTitle(std::string title) const;
    bool matchesIngredient(std::string ingredient) const;

    // TODO: Add ingredient blacklist filtering
    // TODO: Add file I/O for recipe persistence
    // TODO: Add recipe categories and tags
};
