#include "RecipeManager.h"
#include "VeganRecipe.h"
#include "VegetarianRecipe.h"
#include "OmnivoreRecipe.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <fstream>

Recipe* RecipeManager::addRecipe() {
    std::string input;
    std::string title;
    int prepTime = 0;
    
    // Get title and prep time in one prompt
    while (true) {
        std::cout << "Enter title and prep time (minutes), separated by a comma:\n";
        std::getline(std::cin, input);
        
        size_t commaPos = input.find(',');
        if (commaPos == std::string::npos) {
            std::cout << "Error: Please include both title and prep time, separated by a comma.\n";
            continue;
        }
        
        title = input.substr(0, commaPos);
        std::string prepTimeStr = input.substr(commaPos + 1);
        
        // Trim whitespace
        title.erase(0, title.find_first_not_of(" \t"));
        title.erase(title.find_last_not_of(" \t") + 1);
        prepTimeStr.erase(0, prepTimeStr.find_first_not_of(" \t"));
        prepTimeStr.erase(prepTimeStr.find_last_not_of(" \t") + 1);
        
        if (title.empty()) {
            std::cout << "Error: Title cannot be empty.\n";
            continue;
        }
        
        try {
            prepTime = std::stoi(prepTimeStr);
            if (prepTime < 0) {
                std::cout << "Error: Prep time cannot be negative.\n";
                continue;
            }
            break;
        } catch (const std::exception&) {
            std::cout << "Error: Prep time must be a valid number.\n";
            continue;
        }
    }
    
    // Get meal type and diet type in one prompt
    MealType mealType = MealType::Other;
    DietType dietType = DietType::Omnivore;  // Default to Omnivore
    
    std::cout << "Select meal & diet type by entering keywords (e.g. breakfast/vegan) or leave blank for defaults:\n";
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        std::istringstream iss(input);
        std::string token;
        while (std::getline(iss, token, '/')) {
            // Trim whitespace
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            
            // Convert to lowercase for comparison
            std::transform(token.begin(), token.end(), token.begin(), ::tolower);
            
            // Try to match as meal type first
            MealType tempMealType = stringToMealType(token);
            if (tempMealType != MealType::Other) {
                mealType = tempMealType;
                continue;
            }
            
            // Try to match as diet type
            DietType tempDietType = stringToDietType(token);
            if (tempDietType != DietType::Other) {
                dietType = tempDietType;
            }
        }
    }
    
    // Create appropriate recipe subclass based on diet type
    Recipe* recipe = nullptr;
    switch (dietType) {
        case DietType::Vegan:
            recipe = new VeganRecipe(title, prepTime, mealType);
            break;
        case DietType::Vegetarian:
            recipe = new VegetarianRecipe(title, prepTime, mealType);
            break;
        default:
            recipe = new OmnivoreRecipe(title, prepTime, mealType);
    }
    
    // Get ingredients
    while (true) {
        std::cout << "Paste ingredients as comma-separated name:quantity pairs (e.g. flour:2cups,sugar:1cup):\n";
        std::getline(std::cin, input);
        
        if (input.empty()) {
            std::cout << "Error: At least one ingredient is required.\n";
            continue;
        }
        
        std::istringstream iss(input);
        std::string pair;
        bool validInput = true;
        
        while (std::getline(iss, pair, ',')) {
            size_t colonPos = pair.find(':');
            if (colonPos == std::string::npos) {
                std::cout << "Error: Each ingredient must be in name:quantity format.\n";
                validInput = false;
                break;
            }
            
            std::string name = pair.substr(0, colonPos);
            std::string quantity = pair.substr(colonPos + 1);
            
            // Trim whitespace
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
            quantity.erase(0, quantity.find_first_not_of(" \t"));
            quantity.erase(quantity.find_last_not_of(" \t") + 1);
            
            if (name.empty() || quantity.empty()) {
                std::cout << "Error: Ingredient name and quantity cannot be empty.\n";
                validInput = false;
                break;
            }
            
            bool duplicate = false;
            for (const auto& ing : recipe->getIngredients()) {
                if (ing.getName() == name) {
                    std::cout << "Warning: Duplicate ingredient '" << name << "' skipped.\n";
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                recipe->addIngredient(Ingredient(name, quantity));
            }
        }
        
        if (validInput) break;
    }
    
    return recipe;
}

// UML-compliant static factory
Recipe* RecipeManager::addRecipe(const std::string& title, int prepTime, MealType mealType, DietType dietType) {
    switch (dietType) {
        case DietType::Vegan:
            return new VeganRecipe(title, prepTime, mealType);
        case DietType::Vegetarian:
            return new VegetarianRecipe(title, prepTime, mealType);
        case DietType::Omnivore:
            return new OmnivoreRecipe(title, prepTime, mealType);
        default:
            throw std::invalid_argument("Invalid or unhandled diet type");
    }
}

LinkedList<Recipe*> RecipeManager::loadFromFile(const std::string& filename) {
    LinkedList<Recipe*> recipes;
    std::ifstream inFile(filename);
    if (!inFile) return recipes;
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        try {
            Recipe* recipe = Recipe::deserialize(line);
            if (recipe) recipes.push_back(recipe);
        } catch (const std::exception& e) {
            std::cerr << "Error loading recipe: " << e.what() << std::endl;
        }
    }
    return recipes;
}

void RecipeManager::saveToFile(const std::string& filename, const LinkedList<Recipe*>& recipes) {
    std::ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& recipePtr : recipes) {
        if (recipePtr) outFile << recipePtr->serialize() << std::endl;
    }
}
