// src/main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
// TODO: Remove vector include when ingredient serialization is implemented
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
void addIngredientsToRecipe(LinkedList<std::unique_ptr<Recipe>>& recipes);
void saveRecipes(const LinkedList<std::unique_ptr<Recipe>>& recipes);
void loadRecipes(LinkedList<std::unique_ptr<Recipe>>& recipes);
MealType getMealTypeInput();
DietType getDietTypeInput();
std::unique_ptr<Recipe> createRecipeFromData(const std::string& title, int prepTime, MealType mealType, DietType dietType);

int main() {
    LinkedList<std::unique_ptr<Recipe>> recipeList;
    loadRecipes(recipeList);

    int choice = 0;
    while (choice != 4) {
        displayMenu();
        std::cout << "Enter your choice: ";
        
        // Improved input handling
        if (!(std::cin >> choice)) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            choice = 0;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addRecipe(recipeList);
                break;
            case 2:
                listRecipes(recipeList);
                break;
            case 3:
                addIngredientsToRecipe(recipeList);
                break;
            case 4:
                std::cout << "Saving recipes and exiting." << std::endl;
                saveRecipes(recipeList);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        std::cout << std::endl;
    }

    return 0;
}

void displayMenu() {
    std::cout << "=== Recipe Manager Menu ===" << std::endl;
    std::cout << "1. Add Recipe" << std::endl;
    std::cout << "2. List Recipes" << std::endl;
    std::cout << "3. Add Ingredients to Recipe" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << "=========================" << std::endl;
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

    MealType mealType = getMealTypeInput();
    DietType dietType = getDietTypeInput();

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
    
    // TODO: Add ingredient input functionality
    // TODO: Add ingredient blacklist validation
    // TODO: Add recipe sorting options
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
             // TODO: Add ingredient serialization
             // TODO: Add recipe categories and tags serialization
        }
    }
    outFile.close();
}


// Basic loading: Title,PrepTime,MealTypeStr,DietTypeStr
void addIngredientsToRecipe(LinkedList<std::unique_ptr<Recipe>>& recipes) {
    if (recipes.isEmpty()) {
        std::cout << "No recipes available. Please add a recipe first." << std::endl;
        return;
    }

    std::cout << "Available Recipes:" << std::endl;
    int index = 1;
    for (const auto& recipe : recipes) {
        std::cout << index++ << ". " << recipe->getTitle() << std::endl;
    }

    std::cout << "Enter recipe number: ";
    int choice;
    if (!(std::cin >> choice) || choice < 1 || choice > static_cast<int>(recipes.size())) {
        std::cout << "Invalid recipe number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get iterator to the selected recipe
    auto it = recipes.begin();
    for (int i = 1; i < choice; ++i) {
        ++it;
    }

    std::cout << "\nAdding ingredients to: " << (*it)->getTitle() << std::endl;
    std::cout << "Enter ingredients (empty line to finish):\n";
    std::cout << "Format: ingredient_name,quantity (e.g., 'flour,2 cups')" << std::endl;

    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) break;

        size_t comma = line.find(',');
        std::string name = (comma != std::string::npos) ? line.substr(0, comma) : line;
        std::string quantity = (comma != std::string::npos) ? line.substr(comma + 1) : "";

        // Trim whitespace
        name = name.substr(name.find_first_not_of(" \t"));
        name = name.substr(0, name.find_last_not_of(" \t") + 1);
        quantity = quantity.substr(quantity.find_first_not_of(" \t"));
        quantity = quantity.substr(0, quantity.find_last_not_of(" \t") + 1);

        if (!name.empty()) {
            (*it)->addIngredient(Ingredient(name, quantity));
            std::cout << "Added: " << name;
            if (!quantity.empty()) std::cout << " (" << quantity << ")";
            std::cout << std::endl;
        }
    }
}

MealType getMealTypeInput() {
    std::cout << "Enter meal type:\n";
    std::cout << "1. Breakfast (or 'b')\n";
    std::cout << "2. Lunch (or 'l')\n";
    std::cout << "3. Dinner (or 'd')\n";
    std::cout << "4. Snack (or 's')\n";
    std::cout << "Choice: ";
    
    std::string input;
    std::getline(std::cin, input);
    
    // Convert to lowercase for letter input
    if (!input.empty()) {
        input[0] = std::tolower(input[0]);
    }
    
    if (input == "1" || input == "b") return MealType::Breakfast;
    if (input == "2" || input == "l") return MealType::Lunch;
    if (input == "3" || input == "d") return MealType::Dinner;
    if (input == "4" || input == "s") return MealType::Snack;
    
    std::cout << "Invalid meal type. Defaulting to Dinner." << std::endl;
    return MealType::Dinner;
}

DietType getDietTypeInput() {
    std::cout << "Enter diet type:\n";
    std::cout << "1. Vegan (or 'v')\n";
    std::cout << "2. Vegetarian (or 'g')\n";
    std::cout << "3. Pescatarian (or 'p')\n";
    std::cout << "4. Omnivore (or 'o')\n";
    std::cout << "Choice: ";
    
    std::string input;
    std::getline(std::cin, input);
    
    // Convert to lowercase for letter input
    if (!input.empty()) {
        input[0] = std::tolower(input[0]);
    }
    
    if (input == "1" || input == "v") return DietType::Vegan;
    if (input == "2" || input == "g") return DietType::Vegetarian;
    if (input == "3" || input == "p") return DietType::Pescatarian;
    if (input == "4" || input == "o") return DietType::Omnivore;
    
    std::cout << "Invalid diet type. Defaulting to Omnivore." << std::endl;
    return DietType::Omnivore;
}

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
                   // TODO: Add ingredient deserialization
                   // TODO: Add recipe categories and tags deserialization
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
        case DietType::Vegan:
            return std::unique_ptr<Recipe>(new VeganRecipe(title, prepTime, mealType));
        case DietType::Vegetarian:
            return std::unique_ptr<Recipe>(new VegetarianRecipe(title, prepTime, mealType));
        case DietType::Pescatarian:
            return std::unique_ptr<Recipe>(new PescatarianRecipe(title, prepTime, mealType));
        case DietType::Omnivore:
            return std::unique_ptr<Recipe>(new OmnivoreRecipe(title, prepTime, mealType));
        default:
            throw std::invalid_argument("Invalid diet type");
    }
}
