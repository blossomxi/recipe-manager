// src/Recipe.cpp
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

std::string mealTypeToString(MealType type) {
    switch (type) {
        case MealType::Breakfast: return "Breakfast";
        case MealType::Lunch:     return "Lunch";
        case MealType::Dinner:    return "Dinner";
        case MealType::Snack:     return "Snack";
        case MealType::Dessert:   return "Dessert";
        case MealType::Other:     return "Other";
        default:                  return "Unknown";
    }
}

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

std::string dietTypeToString(DietType type) {
    switch (type) {
        case DietType::Vegetarian:  return "Vegetarian";
        case DietType::Vegan:       return "Vegan";
        case DietType::Omnivore:    return "Omnivore";
        case DietType::Other:       return "Other";
        default:                    return "Unknown";
    }
}

DietType stringToDietType(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    if (lowerStr == "vegetarian") return DietType::Vegetarian;
    if (lowerStr == "vegan") return DietType::Vegan;
    if (lowerStr == "omnivore") return DietType::Omnivore;
    return DietType::Other;
}


// --- Recipe Class Implementation ---

// Initialize static member
std::unordered_set<std::string> Recipe::blacklistedIngredients;

Recipe::Recipe(const std::string& title, int prepTime, MealType mealType, DietType dietType)
    : title(title), prepTime(prepTime), mealType(mealType), dietType(dietType) {}

Recipe::Recipe(const Recipe& copy) {
    this->title = copy.title;
    this->prepTime = copy.prepTime;
    this->mealType = copy.mealType;
    this->dietType = copy.dietType;
    this->ingredients = copy.ingredients;
}

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

// Getters
std::string Recipe::getTitle() const {
    return title;
}

int Recipe::getPrepTime() const {
    return prepTime;
}

const LinkedList<Ingredient>& Recipe::getIngredients() const {
    return ingredients;
}

MealType Recipe::getMealType() const {
    return mealType;
}

DietType Recipe::getDietType() const {
    return dietType;
}

// Setters
void Recipe::setTitle(const std::string& title) {
    this->title = title;
}

void Recipe::setPrepTime(int prepTime) {
    if (prepTime >= 0) { // Basic validation
        this->prepTime = prepTime;
    }
}

void Recipe::setMealType(MealType type) {
    this->mealType = type;
}

void Recipe::setDietType(DietType type) {
    this->dietType = type;
}

bool Recipe::matchesTitle(std::string title) const {
    return this->title == title;
}

bool Recipe::matchesIngredient(std::string ingredient) const {
    for (auto it = ingredients.cbegin(); it != ingredients.cend(); ++it) {
        if (it->getName() == ingredient) {
            return true;
        }
    }
    return false;
}
// Ingredient management methods
void Recipe::addIngredient(const Ingredient& ingredient) {
    for (const auto& ing : ingredients) {
        if (ing.getName() == ingredient.getName()) {
            throw std::invalid_argument("Ingredient already exists: " + ingredient.getName());
        }
    }
    if (validateIngredient(ingredient)) {
        ingredients.push_back(Ingredient(ingredient));
    } else {
        throw std::invalid_argument("Invalid ingredient for this recipe type: " + ingredient.getName());
    }
}

void Recipe::removeIngredient(const std::string& ingredientName) {
    for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
        if (it->getName() == ingredientName) {
            ingredients.remove(*it);
            break;
        }
    }
}

void Recipe::editIngredient(const std::string& oldName, const Ingredient& newIngredient) {
    for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
        if (it->getName() == oldName) {
            *it = newIngredient;
            break;
        }
    }
}

void Recipe::addToBlacklist(const std::string& ingredient) {
    std::string lowerIngredient = ingredient;
    std::transform(lowerIngredient.begin(), lowerIngredient.end(), lowerIngredient.begin(), ::tolower);
    blacklistedIngredients.insert(lowerIngredient);
}

void Recipe::removeFromBlacklist(const std::string& ingredient) {
    std::string lowerIngredient = ingredient;
    std::transform(lowerIngredient.begin(), lowerIngredient.end(), lowerIngredient.begin(), ::tolower);
    blacklistedIngredients.erase(lowerIngredient);
}

bool Recipe::isBlacklisted(const std::string& ingredient) {
    std::string lowerIngredient = ingredient;
    std::transform(lowerIngredient.begin(), lowerIngredient.end(), lowerIngredient.begin(), ::tolower);
    return blacklistedIngredients.find(lowerIngredient) != blacklistedIngredients.end();
}

bool Recipe::validateIngredient(const Ingredient& ingredient) const {
    // Check if ingredient is blacklisted
    if (isBlacklisted(ingredient.getName())) {
        return false;
    }
    
    // Check if ingredient is valid for the specific diet type
    return isValidForDiet(ingredient);
}

std::string Recipe::serialize() const {
    std::ostringstream oss;
    oss << getTypeString() << "|"  // Recipe type
        << title << "|"
        << prepTime << "|"
        << mealTypeToString(mealType) << "|"
        << dietTypeToString(dietType) << "|";
    
    // Serialize ingredients
    bool first = true;
    for (const auto& ingredient : ingredients) {
        if (!first) oss << ";";
        oss << ingredient.getName() << ":" << ingredient.getQuantity();
        first = false;
    }
    
    return oss.str();
}

std::unique_ptr<Recipe> Recipe::deserialize(const std::string& data) {
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
    std::unique_ptr<Recipe> recipe;
    if (type == "Vegan") {
        recipe = std::make_unique<VeganRecipe>(title, prepTime, stringToMealType(mealTypeStr));
    } else if (type == "Vegetarian") {
        recipe = std::make_unique<VegetarianRecipe>(title, prepTime, stringToMealType(mealTypeStr));
    } else if (type == "Omnivore") {
        recipe = std::make_unique<OmnivoreRecipe>(title, prepTime, stringToMealType(mealTypeStr));
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
