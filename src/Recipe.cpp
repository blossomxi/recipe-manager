// src/Recipe.cpp
#include "Recipe.h"
#include <stdexcept> // For invalid_argument
#include <algorithm> // For std::transform
#include <cctype>    // For ::tolower

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
        case DietType::Pescatarian: return "Pescatarian";
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
    if (lowerStr == "pescatarian") return DietType::Pescatarian;
    if (lowerStr == "omnivore") return DietType::Omnivore;
    return DietType::Other;
}


// --- Recipe Class Implementation ---

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

const std::vector<Ingredient>& Recipe::getIngredients() const {
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

// TODO: Implement ingredient management methods (missing editRecipe)
bool Recipe::matchesTitle(string title) const {
    return this->title == title;
}

bool Recipe::matchesIngredient(string ingredient) const {
    vector<Ingredient>::iterator it = (this->ingredients).begin();
    while(it != (this->ingredients).end()) {
        if(it->getName() == ingredient) {
            return true;
        }
        it++;
    }
    return false;
}
// TODO: Implement shared helper functions if needed
