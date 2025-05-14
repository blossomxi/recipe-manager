// Recipe Manager - Main Driver Program

//#include "driver.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <stdexcept> // For exception handling during parsing

#include "LinkedList.h"
#include "Recipe.h"
#include "VegetarianRecipe.h"
#include "VeganRecipe.h"
#include "OmnivoreRecipe.h"



const std::string RECIPE_FILE = "recipes.txt";

//Function Prototypes
int driver();
void displayMenu();
void addRecipe(LinkedList<Recipe*>& recipes);
void listRecipes(const LinkedList<Recipe*>& recipes);
void addIngredientsToRecipe(LinkedList<Recipe*>& recipes);
void saveRecipes(const LinkedList<Recipe*>& recipes);
void loadRecipes(LinkedList<Recipe*>& recipes);
MealType getMealTypeInput();
DietType getDietTypeInput();
Recipe* createRecipeFromData(const std::string& title, int prepTime, MealType mealType, DietType dietType);
Recipe* findRecipeByTitle(LinkedList<Recipe*>& recipes, const std::string& title); // Helper Prototype
void removeRecipe(LinkedList<Recipe*>& recipes); // Prototype
void editRecipe(LinkedList<Recipe*>& recipes); // Prototype
void searchRecipes(const LinkedList<Recipe*>& recipes);
void sortRecipes(LinkedList<Recipe*>& recipes);

int driver() {
    LinkedList<Recipe*> recipeList;
    loadRecipes(recipeList);

    int choice = 0;
    while (choice != 8) {
        std::cout << "\n-------------------------\n"; 
        displayMenu();
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
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
                editRecipe(recipeList); 
                break;
            case 5: 
                removeRecipe(recipeList); 
                break;
            case 6:
                searchRecipes(recipeList);
                break;
            case 7:
                sortRecipes(recipeList);
                break;
            case 8: 
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
    std::cout << "\n\n";
    std::cout << "      🍴  Fork & Function: Recipe Manager  🍴\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "  1. Add Recipe\n";
    std::cout << "  2. List Recipes\n";
    std::cout << "  3. Add Ingredients to Recipe\n";
    std::cout << "  4. Edit Recipe\n";
    std::cout << "  5. Remove Recipe\n";
    std::cout << "  6. Search Recipes\n";
    std::cout << "  7. Sort Recipes\n";
    std::cout << "  8. Quit\n";
    std::cout << "--------------------------------------------------\n\n";
}

void addRecipe(LinkedList<Recipe*>& recipes) {
    std::string title, mealStr, dietStr;
    int prepTime;

    std::cout << "\nEnter recipe title: ";
    std::getline(std::cin, title); 

    std::cout << "\nEnter prep time (minutes): ";
    while (!(std::cin >> prepTime) || prepTime <= 0) { 
        std::cout << "\nInvalid input. Please enter a positive number for prep time: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline left by cin >> prepTime

    MealType mealType = getMealTypeInput();
    DietType dietType = getDietTypeInput();

    // Create the appropriate recipe type based on DietType
    try {
         Recipe* newRecipe = createRecipeFromData(title, prepTime, mealType, dietType);
         if(newRecipe) {
            recipes.push_back(newRecipe); // Just push pointer
            std::cout << "\nRecipe '" << title << "' added successfully!\n";
         } else {
             std::cout << "\nFailed to create recipe (unknown diet type?).\n";
         }
    } catch (const std::exception& e) {
        std::cerr << "\nError adding recipe: " << e.what() << "\n";
    }
    
    // TODO: Add ingredient input functionality
    // TODO: Add ingredient blacklist validation
    // TODO: Add recipe sorting options
}

void listRecipes(const LinkedList<Recipe*>& recipes) {
    std::cout << "\n--- Listing All Recipes ---" << std::endl;
    if (recipes.isEmpty()) {
        std::cout << "No recipes available." << std::endl;
    } else {
        int i = 1;
        for (LinkedList<Recipe*>::const_iterator it = recipes.begin(); it != recipes.end(); ++it) {
            Recipe* recipePtr = *it;
            std::cout << "\nRecipe #" << i++ << ":\n";
            if (recipePtr) { // Check if pointer is valid
                 recipePtr->display(); 
            } else {
                 std::cerr << "Warning: Encountered a null recipe pointer in the list." << std::endl;
            }
        }
    }
    std::cout << "---------------------------" << std::endl;
}

void saveRecipes(const LinkedList<Recipe*>& recipes) {
    std::ofstream outFile(RECIPE_FILE);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << RECIPE_FILE << " for writing." << std::endl;
        return;
    }

    for (LinkedList<Recipe*>::const_iterator it = recipes.begin(); it != recipes.end(); ++it) {
        Recipe* recipePtr = *it;
        if (recipePtr) {
            outFile << recipePtr->serialize() << std::endl;
        }
    }
    outFile.close();
}

void loadRecipes(LinkedList<Recipe*>& recipes) {
    std::ifstream inFile(RECIPE_FILE);
    if (!inFile) {
        // File not existing is not an error on first run
        return;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(inFile, line)) {
        lineNumber++;
        if (line.empty()) continue;

        try {
            Recipe* recipe = Recipe::deserialize(line);
            if (recipe) {
                recipes.push_back(recipe);
            }
        } catch (const std::exception& e) {
            std::cerr << "Warning [Line " << lineNumber << "]: Error deserializing recipe: " << e.what() << std::endl;
        }
    }
    inFile.close();
}

// Basic saving: Title,PrepTime,MealTypeStr,DietTypeStr
void addIngredientsToRecipe(LinkedList<Recipe*>& recipes) {
    if (recipes.isEmpty()) {
        std::cout << "No recipes available. Please add a recipe first." << std::endl;
        return;
    }

    std::cout << "Available Recipes:" << std::endl;
    int index = 1;
    for (LinkedList<Recipe*>::iterator it = recipes.begin(); it != recipes.end(); ++it) {
        Recipe* recipePtr = *it;
        std::cout << index++ << ". " << recipePtr->getTitle() << std::endl;
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
    LinkedList<Recipe*>::iterator it = recipes.begin();
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
    std::string input;
    while (true) {
        std::cout << "\nEnter meal type:\n";
        std::cout << "1. Breakfast (or 'b')\n";
        std::cout << "2. Lunch (or 'l')\n";
        std::cout << "3. Dinner (or 'd')\n";
        std::cout << "4. Other (or 't')\n";   
        std::cout << "Choice: ";
        
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "\nInput cannot be empty. Please try again.\n";
            continue;
        }
        
        // Convert to lowercase for letter input
        char firstChar = std::tolower(input[0]);
        
        if (input == "1" || firstChar == 'b') return MealType::Breakfast;
        if (input == "2" || firstChar == 'l') return MealType::Lunch;
        if (input == "3" || firstChar == 'd') return MealType::Dinner;
        if (input == "4" || firstChar == 't') return MealType::Other;   
        
        std::cout << "\nInvalid meal type. Please enter a valid number or letter.\n";
    }
}

DietType getDietTypeInput() {
    std::string input;
    while (true) {
        std::cout << "\nEnter diet type:\n";
        std::cout << "1. Vegan (or 'v')\n";
        std::cout << "2. Vegetarian (or 'g')\n";
        std::cout << "3. Omnivore (or 'o')\n";
        std::cout << "Choice: ";
        
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "\nInput cannot be empty. Please try again.\n";
            continue;
        }
        
        // Convert to lowercase for letter input
        char firstChar = std::tolower(input[0]);
        
        if (input == "1" || firstChar == 'v') return DietType::Vegan;
        if (input == "2" || firstChar == 'g') return DietType::Vegetarian;
        if (input == "3" || firstChar == 'o') return DietType::Omnivore;
        
        std::cout << "\nInvalid diet type. Please enter a valid number or letter.\n";
    }
}

// Factory function to create the correct recipe type
Recipe* createRecipeFromData(const std::string& title, int prepTime, MealType mealType, DietType dietType) {
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

// Helper function to find a recipe by title (returns non-owning pointer)
Recipe* findRecipeByTitle(LinkedList<Recipe*>& recipes, const std::string& title) {
    for (LinkedList<Recipe*>::iterator it = recipes.begin(); it != recipes.end(); ++it) {
        if ((*it) && (*it)->getTitle() == title) {
            return *it; // Return raw pointer
        }
    }
    return nullptr; // Not found
}

void removeRecipe(LinkedList<Recipe*>& recipes) {
    std::cout << "Enter the exact title of the recipe to remove: ";
    std::string titleToRemove;
    std::getline(std::cin, titleToRemove);

    if (titleToRemove.empty()) {
        std::cout << "Recipe title cannot be empty." << std::endl;
        return;
    }

    // Use the find helper first to confirm existence
    Recipe* foundRecipe = findRecipeByTitle(recipes, titleToRemove);

    if (!foundRecipe) {
        std::cout << "Recipe '" << titleToRemove << "' not found." << std::endl;
        return;
    }

    std::cout << "Found recipe: " << foundRecipe->getTitle() << std::endl;
    std::cout << "Are you sure you want to remove it? (y/n): ";
    std::string confirmation;
    std::getline(std::cin, confirmation);

    if (confirmation == "y" || confirmation == "Y") {
        bool removed = recipes.removeIf([&titleToRemove](Recipe* recipe_ptr) {
            if (recipe_ptr && recipe_ptr->getTitle() == titleToRemove) {
                delete recipe_ptr; // Free memory
                return true;
            }
            return false;
        });

        if (removed) {
            std::cout << "Recipe '" << titleToRemove << "' removed successfully." << std::endl;
        } else {
            std::cout << "Error: Recipe '" << titleToRemove << "' could not be removed (already removed or error?)." << std::endl;
        }
    } else {
        std::cout << "Removal cancelled." << std::endl;
    }
}

void editRecipe(LinkedList<Recipe*>& recipes) {
    std::cout << "Enter the exact title of the recipe to edit: ";
    std::string titleToEdit;
    std::getline(std::cin, titleToEdit);

    if (titleToEdit.empty()) {
        std::cout << "Recipe title cannot be empty." << std::endl;
        return;
    }

    Recipe* recipeToEdit = findRecipeByTitle(recipes, titleToEdit);

    if (!recipeToEdit) {
        std::cout << "Recipe '" << titleToEdit << "' not found." << std::endl;
        return;
    }

    int editChoice = 0;
    while (editChoice != 4) {
        std::cout << "\n--- Editing Recipe: " << recipeToEdit->getTitle() << " ---" << std::endl;
        std::cout << "Current Prep Time: " << recipeToEdit->getPrepTime() << " minutes" << std::endl;
        std::cout << "Current Meal Type: " << mealTypeToString(recipeToEdit->getMealType()) << std::endl;
        std::cout << "Current Diet Type: " << dietTypeToString(recipeToEdit->getDietType()) << " (Cannot be changed)" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "1. Edit Title" << std::endl;
        std::cout << "2. Edit Prep Time" << std::endl;
        std::cout << "3. Edit Meal Type" << std::endl;
        std::cout << "4. Done Editing" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> editChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            editChoice = 0;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

        switch (editChoice) {
            case 1: { // Edit Title
                std::string newTitle;
                std::cout << "Enter new title: ";
                std::getline(std::cin, newTitle);
                if (!newTitle.empty()) {
                    recipeToEdit->setTitle(newTitle);
                    std::cout << "Title updated." << std::endl;
                    titleToEdit = newTitle; 
                } else {
                    std::cout << "Title cannot be empty. Not updated." << std::endl;
                }
                break;
            }
            case 2: { // Edit Prep Time
                int newPrepTime;
                std::cout << "Enter new prep time (minutes, must be > 0): ";
                while (!(std::cin >> newPrepTime) || newPrepTime <= 0) {
                    std::cout << "Invalid input. Please enter a positive number for prep time: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                recipeToEdit->setPrepTime(newPrepTime);
                std::cout << "Prep time updated." << std::endl;
                break;
            }
            case 3: { // Edit Meal Type
                 std::cout << "Select new meal type:" << std::endl;
                 MealType newMealType = getMealTypeInput(); // Reuse existing input function
                 recipeToEdit->setMealType(newMealType);
                 std::cout << "Meal type updated." << std::endl;
                break;
            }
            case 4: // Done Editing
                std::cout << "Finished editing '" << recipeToEdit->getTitle() << "'." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void searchRecipes(const LinkedList<Recipe*>& recipes) {
    std::cout << "\n========================================\n";
    std::cout << "           Search Recipes               \n";
    std::cout << "========================================\n";
    std::cout << "| 1. Search by title                   |\n";
    std::cout << "| 2. Search by ingredient              |\n";
    std::cout << "| 3. Search by meal type               |\n";
    std::cout << "| 4. Search by diet type               |\n";
    std::cout << "========================================\n";
    std::cout << "Choice: ";

    int choice;
    if (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cout << "Invalid choice." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string searchTerm;
    bool found = false;

    switch (choice) {
        case 1: {
            std::cout << "Enter title to search: ";
            std::getline(std::cin, searchTerm);
            for (LinkedList<Recipe*>::const_iterator it = recipes.begin(); it != recipes.end(); ++it) {
                Recipe* recipePtr = *it;
                if (recipePtr->matchesTitle(searchTerm)) {
                    recipePtr->display();
                    found = true;
                }
            }
            break;
        }
        case 2: {
            std::cout << "Enter ingredient to search: ";
            std::getline(std::cin, searchTerm);
            for (LinkedList<Recipe*>::const_iterator it = recipes.begin(); it != recipes.end(); ++it) {
                Recipe* recipePtr = *it;
                if (recipePtr->matchesIngredient(searchTerm)) {
                    recipePtr->display();
                    found = true;
                }
            }
            break;
        }
        case 3: {
            std::cout << "Enter meal type to search: ";
            std::getline(std::cin, searchTerm);
            MealType searchMealType = stringToMealType(searchTerm);
            for (LinkedList<Recipe*>::const_iterator it = recipes.begin(); it != recipes.end(); ++it) {
                Recipe* recipePtr = *it;
                if (recipePtr->getMealType() == searchMealType) {
                    recipePtr->display();
                    found = true;
                }
            }
            break;
        }
        case 4: {
            std::cout << "Enter diet type to search: ";
            std::getline(std::cin, searchTerm);
            DietType searchDietType = stringToDietType(searchTerm);
            for (LinkedList<Recipe*>::const_iterator it = recipes.begin(); it != recipes.end(); ++it) {
                Recipe* recipePtr = *it;
                if (recipePtr->getDietType() == searchDietType) {
                    recipePtr->display();
                    found = true;
                }
            }
            break;
        }
    }

    if (!found) {
        std::cout << "No recipes found matching your search criteria." << std::endl;
    }
}

void sortRecipes(LinkedList<Recipe*>& recipes) {
    std::cout << "\n========================================\n";
    std::cout << "             Sort Recipes               \n";
    std::cout << "========================================\n";
    std::cout << "| 1. Sort by title                     |\n";
    std::cout << "| 2. Sort by prep time                 |\n";
    std::cout << "| 3. Sort by meal type                 |\n";
    std::cout << "========================================\n";
    std::cout << "Choice: ";

    int choice;
    if (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cout << "Invalid choice." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1:
            recipes.sort(Recipe::compareByTitle);
            std::cout << "Recipes sorted by title." << std::endl;
            break;
        case 2:
            recipes.sort(Recipe::compareByPrepTime);
            std::cout << "Recipes sorted by prep time." << std::endl;
            break;
        case 3:
            recipes.sort(Recipe::compareByMealType);
            std::cout << "Recipes sorted by meal type." << std::endl;
            break;
    }
}
