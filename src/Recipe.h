// src/Recipe.h
#pragma once

#include <string>
#include "Ingredient.h"
#include "LinkedList.h"
#include "MealType.h"
#include "DietType.h"
#include <unordered_set>

// Helper functions
std::string mealTypeToString(MealType type);
MealType stringToMealType(const std::string& str);

std::string dietTypeToString(DietType type);
DietType stringToDietType(const std::string& str);

// Recipe class
class Recipe {
protected:
    std::string title;
    int prepTime; // Preparation time in minutes
    LinkedList<Ingredient> ingredients;
    MealType mealType;
    DietType dietType;
    static std::unordered_set<std::string> blacklistedIngredients; // Static blacklist shared across all recipes

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
    virtual void display() const = 0;

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

    // Ingredient validation methods
    static void addToBlacklist(const std::string& ingredient);
    static void removeFromBlacklist(const std::string& ingredient);
    static bool isBlacklisted(const std::string& ingredient);
    bool validateIngredient(const Ingredient& ingredient) const;
    virtual bool isValidForDiet(const Ingredient& ingredient) const = 0; // Pure virtual method for diet-specific validation

    // Serialization methods
    virtual std::string serialize() const;
    static Recipe* deserialize(const std::string& data);
    virtual std::string getTypeString() const = 0; // Pure virtual method to get recipe type string

    // Search and Sort methods
    static bool compareByTitle(const Recipe* a, const Recipe* b) {
        return a->getTitle() < b->getTitle();
    }

    static bool compareByPrepTime(const Recipe* a, const Recipe* b) {
        return a->getPrepTime() < b->getPrepTime();
    }

    static bool compareByMealType(const Recipe* a, const Recipe* b) {
        return static_cast<int>(a->getMealType()) < static_cast<int>(b->getMealType());
    }

    // TODO: Add ingredient blacklist filtering
    // TODO: Add file I/O for recipe persistence
    // TODO: Add recipe categories and tags
};
