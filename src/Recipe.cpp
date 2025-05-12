// src/Recipe.cpp
// Implementation of the Recipe class and related helper functions for a recipe management system.
// This file demonstrates OOP principles, custom data structures, and serialization logic.
#include "Recipe.h"
#include "VeganRecipe.h"
#include "VegetarianRecipe.h"
#include "OmnivoreRecipe.h"
#include <stdexcept> // For invalid_argument
#include <algorithm> // For std::transform
#include <cctype>    // For ::tolower
#include <unordered_set>
#include <sstream>

// --- Helper Enum Functions --- 

// Converts a MealType enum to its string representation.
std::string mealTypeToString(MealType type) {
    switch (static_cast<int>(type)) {
        case static_cast<int>(MealType::Breakfast): return "Breakfast";
        case static_cast<int>(MealType::Lunch):     return "Lunch";
        case static_cast<int>(MealType::Dinner):    return "Dinner";
        case static_cast<int>(MealType::Snack):     return "Snack";
        case static_cast<int>(MealType::Dessert):   return "Dessert";
        case static_cast<int>(MealType::Other):     return "Other";
        default:                                    return "Unknown";
    }
}

// Converts a string to the corresponding MealType enum value (case-insensitive).
MealType stringToMealType(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    if (lowerStr == "breakfast") return MealType::Breakfast;
    if (lowerStr == "lunch") return MealType::Lunch;
    if (lowerStr == "dinner") return MealType::Dinner;
    if (lowerStr == "snack") return MealType::Snack;
    if (lowerStr == "dessert") return MealType::Dessert;
    return MealType::Other;
}

// Converts a DietType enum to its string representation.
std::string dietTypeToString(DietType type) {
    switch (static_cast<int>(type)) {
        case static_cast<int>(DietType::Vegetarian):  return "Vegetarian";
        case static_cast<int>(DietType::Vegan):       return "Vegan";
        case static_cast<int>(DietType::Omnivore):    return "Omnivore";
        case static_cast<int>(DietType::Other):       return "Other";
        default:                                      return "Unknown";
    }
}

// Converts a string to the corresponding DietType enum value (case-insensitive).
DietType stringToDietType(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    if (lowerStr == "vegetarian") return DietType::Vegetarian;
    if (lowerStr == "vegan") return DietType::Vegan;
    if (lowerStr == "omnivore") return DietType::Omnivore;
    return DietType::Other;
}


// --- Recipe Class Implementation ---

// Static member for global ingredient blacklist shared by all Recipe instances.
std::unordered_set<std::string> Recipe::blacklistedIngredients;

// Constructor: Initializes a Recipe with title, prep time, meal type, and diet type.
Recipe::Recipe(const std::string& title, int prepTime, MealType mealType, DietType dietType)
    : title(title), prepTime(prepTime), mealType(mealType), dietType(dietType) {}

// Copy constructor: Deep copies all fields, including the linked list of ingredients.
Recipe::Recipe(const Recipe& copy) {
    this->title = copy.title;
    this->prepTime = copy.prepTime;
    this->mealType = copy.mealType;
    this->dietType = copy.dietType;
    this->ingredients = copy.ingredients;
}

// Copy assignment operator: Ensures deep copy and self-assignment safety.
Recipe& Recipe::operator=(const Recipe& copy) {
    if (this != &copy) {
        this->title = copy.title;
        this->prepTime = copy.prepTime;
        this->mealType = copy.mealType;
        this->dietType = copy.dietType;
        this->ingredients = copy.ingredients;
    }
    return *this;
}

// --- Getters ---
// Returns the recipe title.
std::string Recipe::getTitle() const {
    return title;
}
// Returns the preparation time in minutes.
int Recipe::getPrepTime() const {
    return prepTime;
}
// Returns a const reference to the linked list of ingredients.
const LinkedList<Ingredient>& Recipe::getIngredients() const {
    return ingredients;
}
// Returns the meal type.
MealType Recipe::getMealType() const {
    return mealType;
}
// Returns the diet type.
DietType Recipe::getDietType() const {
    return dietType;
}

// --- Setters ---
// Sets the recipe title.
void Recipe::setTitle(const std::string& title) {
    this->title = title;
}
// Sets the preparation time (must be non-negative).
void Recipe::setPrepTime(int prepTime) {
    if (prepTime >= 0) { // Basic validation
        this->prepTime = prepTime;
    }
}
// Sets the meal type.
void Recipe::setMealType(MealType type) {
    this->mealType = type;
}
// Sets the diet type.
void Recipe::setDietType(DietType type) {
    this->dietType = type;
}

// Checks if the recipe title matches the given string (exact match).
bool Recipe::matchesTitle(std::string title) const {
    return this->title == title;
}

// Checks if the recipe contains an ingredient with the given name.
bool Recipe::matchesIngredient(std::string ingredient) const {
    for (LinkedList<Ingredient>::const_iterator it = this->ingredients.begin(); it != this->ingredients.end(); ++it) {
        const Ingredient& ing = *it;
        if (ing.getName() == ingredient) {
            return true;
        }
    }
    return false;
}

// --- Ingredient Management Methods ---
// Adds an ingredient to the recipe after validation (OOP: uses polymorphic validateIngredient).
void Recipe::addIngredient(const Ingredient& ingredient) {
    for (LinkedList<Ingredient>::iterator it = this->ingredients.begin(); it != this->ingredients.end(); ++it) {
        const Ingredient& ing = *it;
        if (ing.getName() == ingredient.getName()) {
            throw std::invalid_argument("Ingredient already exists: " + ingredient.getName());
        }
    }
    if (validateIngredient(ingredient)) {
        this->ingredients.push_back(Ingredient(ingredient));
    } else {
        throw std::invalid_argument("Invalid ingredient for this recipe type: " + ingredient.getName());
    }
}

// Removes an ingredient by name (linear search and remove using custom linked list).
void Recipe::removeIngredient(const std::string& ingredientName) {
    for (LinkedList<Ingredient>::iterator it = this->ingredients.begin(); it != this->ingredients.end(); ++it) {
        if (it->getName() == ingredientName) {
            this->ingredients.remove(*it);
            break;
        }
    }
}

// Edits an existing ingredient by replacing it with a new one (by name).
void Recipe::editIngredient(const std::string& oldName, const Ingredient& newIngredient) {
    for (LinkedList<Ingredient>::iterator it = this->ingredients.begin(); it != this->ingredients.end(); ++it) {
        if (it->getName() == oldName) {
            *it = newIngredient;
            break;
        }
    }
}

// --- Blacklist Management (Static) ---
// Adds an ingredient to the global blacklist (case-insensitive).
void Recipe::addToBlacklist(const std::string& ingredient) {
    std::string lowerIngredient = ingredient;
    std::transform(lowerIngredient.begin(), lowerIngredient.end(), lowerIngredient.begin(), ::tolower);
    blacklistedIngredients.insert(lowerIngredient);
}
// Removes an ingredient from the global blacklist (case-insensitive).
void Recipe::removeFromBlacklist(const std::string& ingredient) {
    std::string lowerIngredient = ingredient;
    std::transform(lowerIngredient.begin(), lowerIngredient.end(), lowerIngredient.begin(), ::tolower);
    blacklistedIngredients.erase(lowerIngredient);
}
// Checks if an ingredient is blacklisted (case-insensitive).
bool Recipe::isBlacklisted(const std::string& ingredient) {
    std::string lowerIngredient = ingredient;
    std::transform(lowerIngredient.begin(), lowerIngredient.end(), lowerIngredient.begin(), ::tolower);
    return blacklistedIngredients.find(lowerIngredient) != blacklistedIngredients.end();
}

// --- Ingredient Validation ---
// Validates an ingredient for this recipe (checks blacklist and diet rules).
bool Recipe::validateIngredient(const Ingredient& ingredient) const {
    // Check if ingredient is blacklisted
    if (isBlacklisted(ingredient.getName())) {
        return false;
    }
    
    // Check if ingredient is valid for the specific diet type
    return isValidForDiet(ingredient);
}

// --- Serialization/Deserialization ---
// Serializes the recipe to a string for file storage (format: type|title|prepTime|mealType|dietType|ingredient1:qty1;ingredient2:qty2;...)
std::string Recipe::serialize() const {
    std::ostringstream oss;
    oss << getTypeString() << "|"  // Recipe type
        << title << "|"
        << prepTime << "|"
        << mealTypeToString(mealType) << "|"
        << dietTypeToString(dietType) << "|";
    
    // Serialize ingredients
    bool first = true;
    for (LinkedList<Ingredient>::const_iterator it = this->ingredients.begin(); it != this->ingredients.end(); ++it) {
        const Ingredient& ing = *it;
        if (!first) oss << ";";
        oss << ing.getName() << ":" << ing.getQuantity();
        first = false;
    }
    
    return oss.str();
}

// Deserializes a recipe from a string, reconstructing the correct derived type and all ingredients.
Recipe* Recipe::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string type, title, mealTypeStr, dietTypeStr, ingredientsStr;
    int prepTime;
    
    // Parse the main recipe data
    std::getline(iss, type, '|');
    std::getline(iss, title, '|');
    iss >> prepTime;
    iss.ignore(); // Skip the '|'
    std::getline(iss, mealTypeStr, '|');
    std::getline(iss, dietTypeStr, '|');
    std::getline(iss, ingredientsStr);
    
    // Create the appropriate recipe type
    Recipe* recipe = nullptr;
    if (type == "Vegan") {
        recipe = new VeganRecipe(title, prepTime, stringToMealType(mealTypeStr));
    } else if (type == "Vegetarian") {
        recipe = new VegetarianRecipe(title, prepTime, stringToMealType(mealTypeStr));
    } else if (type == "Omnivore") {
        recipe = new OmnivoreRecipe(title, prepTime, stringToMealType(mealTypeStr));
    } else {
        throw std::runtime_error("Unknown recipe type: " + type);
    }
    
    // Parse and add ingredients
    std::istringstream ingredientsStream(ingredientsStr);
    std::string ingredientPair;
    while (std::getline(ingredientsStream, ingredientPair, ';')) {
        size_t colonPos = ingredientPair.find(':');
        if (colonPos != std::string::npos) {
            std::string name = ingredientPair.substr(0, colonPos);
            std::string quantity = ingredientPair.substr(colonPos + 1);
            recipe->addIngredient(Ingredient(name, quantity));
        }
    }
    
    return recipe;
}
