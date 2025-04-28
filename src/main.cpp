// src/main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <memory> // For unique_ptr
#include <vector>
#include <stdexcept> // For exception handling during parsing

#include "LinkedList.h"
#include "Recipe.h"
#include "VegetarianRecipe.h"
#include "VeganRecipe.h"
#include "PescatarianRecipe.h"
#include "OmnivoreRecipe.h"

const std::string RECIPE_FILE = "recipes.txt";

// Function Prototypes
void displayMenu();
void addRecipe(LinkedList<std::unique_ptr<Recipe>>& recipes);
void listRecipes(const LinkedList<std::unique_ptr<Recipe>>& recipes);
void saveRecipes(const LinkedList<std::unique_ptr<Recipe>>& recipes);
void loadRecipes(LinkedList<std::unique_ptr<Recipe>>& recipes);
std::unique_ptr<Recipe> createRecipeFromData(const std::string& title, int prepTime, MealType mealType, DietType dietType);

int main() {
    LinkedList<std::unique_ptr<Recipe>> recipeList;
    loadRecipes(recipeList);

    int choice = 0;
    while (choice != 3) {
        displayMenu();
        std::cout << "Enter your choice: ";
        
        // Improved input handling
        if (!(std::cin >> choice)) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            std::cout << "Invalid input. Please enter a number." << std::endl;
            choice = 0; // Reset choice
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the rest of the line (including newline)

        switch (choice) {
            case 1:
                addRecipe(recipeList);
                break;
            case 2:
                listRecipes(recipeList);
                break;
            case 3:
                std::cout << "Saving recipes and exiting." << std::endl;
                saveRecipes(recipeList);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        std::cout << std::endl; // Add a newline for spacing
    }

    return 0;
}

void displayMenu() {
    std::cout << "--- Recipe Manager Menu ---" << std::endl;
    std::cout << "1. Add Recipe" << std::endl;
    std::cout << "2. List Recipes" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "-------------------------" << std::endl;
}

void addRecipe(LinkedList<std::unique_ptr<Recipe>>& recipes) {
    std::string title, mealStr, dietStr;
    int prepTime;

    std::cout << "Enter recipe title: ";
    std::getline(std::cin, title); // Use getline after cin >> choice

    std::cout << "Enter prep time (minutes): ";
    while (!(std::cin >> prepTime) || prepTime < 0) { 
        std::cout << "Invalid input. Please enter a non-negative number for prep time: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline left by cin >> prepTime

    std::cout << "Enter meal type (Breakfast, Lunch, Dinner, Snack, Dessert, Other): ";
    std::getline(std::cin, mealStr);
    MealType mealType = stringToMealType(mealStr);

    std::cout << "Enter diet type (Vegetarian, Vegan, Pescatarian, Omnivore, Other): ";
    std::getline(std::cin, dietStr);
    DietType dietType = stringToDietType(dietStr);

    // Create the appropriate recipe type based on DietType
    try {
         std::unique_ptr<Recipe> newRecipe = createRecipeFromData(title, prepTime, mealType, dietType);
         if(newRecipe) {
            recipes.push_back(std::move(newRecipe)); // Move ownership into the list
            std::cout << "Recipe '" << title << "' added successfully!" << std::endl;
         } else {
             std::cout << "Failed to create recipe (unknown diet type?)." << std::endl;
         }
    } catch (const std::exception& e) {
        std::cerr << "Error adding recipe: " << e.what() << std::endl;
    }
    
    // TODO: Add functionality to input ingredients
}

void listRecipes(const LinkedList<std::unique_ptr<Recipe>>& recipes) {
    std::cout << "\n--- Listing All Recipes ---" << std::endl;
    if (recipes.isEmpty()) {
        std::cout << "No recipes available." << std::endl;
    } else {
        int i = 1;
        for (const auto& recipePtr : recipes) {
            std::cout << "\nRecipe #" << i++ << ":\n";
            if (recipePtr) { // Check if pointer is valid
                 recipePtr->display(); // Polymorphic call
            } else {
                 std::cerr << "Warning: Encountered a null recipe pointer in the list." << std::endl;
            }
        }
    }
    std::cout << "---------------------------" << std::endl;
}

// Basic saving: Title,PrepTime,MealTypeStr,DietTypeStr
void saveRecipes(const LinkedList<std::unique_ptr<Recipe>>& recipes) {
    std::ofstream outFile(RECIPE_FILE);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << RECIPE_FILE << " for writing." << std::endl;
        return;
    }

    for (const auto& recipePtr : recipes) {
        if (recipePtr) { // Check if pointer is valid before accessing
             outFile << recipePtr->getTitle() << ","
                     << recipePtr->getPrepTime() << ","
                     << mealTypeToString(recipePtr->getMealType()) << ","
                     << dietTypeToString(recipePtr->getDietType()) << std::endl;
             // TODO: Add ingredient serialization later
        }
    }
    outFile.close();
}


// Basic loading: Title,PrepTime,MealTypeStr,DietTypeStr
void loadRecipes(LinkedList<std::unique_ptr<Recipe>>& recipes) {
    std::ifstream inFile(RECIPE_FILE);
    if (!inFile) {
        // File not existing is not an error on first run
        return;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(inFile, line)) {
        lineNumber++;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, ',')) {
            parts.push_back(segment);
        }

        if (parts.size() >= 4) { // Expecting at least Title, PrepTime, Meal, Diet
            try {
                std::string title = parts[0];
                int prepTime = std::stoi(parts[1]);
                MealType mealType = stringToMealType(parts[2]);
                DietType dietType = stringToDietType(parts[3]);
                
                std::unique_ptr<Recipe> recipe = createRecipeFromData(title, prepTime, mealType, dietType);
                if (recipe) {
                   // TODO: Add ingredient deserialization later
                   recipes.push_back(std::move(recipe));
                } else {
                    std::cerr << "Warning [Line " << lineNumber << "]: Could not create recipe (unknown diet type?): " << line << std::endl;
                }

            } catch (const std::invalid_argument& e) {
                std::cerr << "Warning [Line " << lineNumber << "]: Skipping line due to invalid number format (prepTime): " << line << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Warning [Line " << lineNumber << "]: Skipping line due to number out of range (prepTime): " << line << std::endl;
            } catch (...) {
                std::cerr << "Warning [Line " << lineNumber << "]: Skipping line due to unknown error during parsing: " << line << std::endl;
            }
        } else {
             if (!line.empty()) { // Don't warn about empty lines
                 std::cerr << "Warning [Line " << lineNumber << "]: Skipping malformed line (expected at least 4 comma-separated values): " << line << std::endl;
             }
        }
    }
    inFile.close();
}

// Factory function to create the correct recipe type
std::unique_ptr<Recipe> createRecipeFromData(const std::string& title, int prepTime, MealType mealType, DietType dietType) {
    switch (dietType) {
        case DietType::Vegetarian:
            return std::make_unique<VegetarianRecipe>(title, prepTime, mealType);
        case DietType::Vegan:
            return std::make_unique<VeganRecipe>(title, prepTime, mealType);
        case DietType::Pescatarian:
            return std::make_unique<PescatarianRecipe>(title, prepTime, mealType);
        case DietType::Omnivore:
            return std::make_unique<OmnivoreRecipe>(title, prepTime, mealType);
        case DietType::Other:
             // For 'Other', we might default to Omnivore or a generic base, let's use Omnivore for now
             // Or potentially have a GenericRecipe class later.
             // Alternatively, could return nullptr or throw an exception if 'Other' isn't directly supported
             std::cerr << "Warning: Creating 'Omnivore' recipe for 'Other' diet type." << std::endl;
             return std::make_unique<OmnivoreRecipe>(title, prepTime, mealType); // Example: Defaulting 'Other' to Omnivore
        default:
            return nullptr; // Or throw an exception for unknown types
    }
}
