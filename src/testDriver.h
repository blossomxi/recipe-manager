// Recipe Manager - Test Driver Program
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <stdexcept>

#include "LinkedList.h"
#include "Recipe.h"
#include "VegetarianRecipe.h"
#include "VeganRecipe.h"
#include "OmnivoreRecipe.h"


// Function prototypes for test cases
void testAddRecipe();
void testAddIngredientsToRecipe();
void testListRecipes();
void testSaveAndLoadRecipes();
void testRemoveRecipe();
void testEditRecipe();
void testSearchRecipes();
void testSortRecipes();


int testDriver() {
  std::cout << "Running tests...\n";

  testAddRecipe();
  testAddIngredientsToRecipe();
  testListRecipes();
  testSaveAndLoadRecipes();
  testRemoveRecipe();
  testEditRecipe();
  testSearchRecipes();
  testSortRecipes();

  std::cout << "All tests passed!\n";

  return 0;
}

void testAddRecipe() {
  std::cout << "Testing addRecipe...\n";

  LinkedList<Recipe*> recipes;
  std::string title = "Test Recipe";
  int prepTime = 30;
  MealType mealType = MealType::Dinner;
  DietType dietType = DietType::Vegan;

  try {
    Recipe* newRecipe = createRecipeFromData(title, prepTime, mealType, dietType);
      if(newRecipe) {
        recipes.push_back(newRecipe); // Just push pointer
        // Check if the recipe was added correctly
        if (!recipes.isEmpty()) {
          LinkedList<Recipe*>::iterator it = recipes.begin();
          
          if (it != recipes.end()) {
            Recipe* recipePtr = *it;

            assert(recipes.size() == 1);
            assert(recipePtr->getTitle() == title);
            assert(recipePtr->getPrepTime() == prepTime);
          }
        } else {
          std::cerr << "Error: Recipe list is empty after adding a recipe.\n";
        }
      } else {
        std::cout << "\nFailed to create recipe (unknown diet type?).\n";
      }
  } catch (const std::exception& e) {
    std::cerr << "\nError adding recipe: " << e.what() << "\n";
  }

  // Cleanup
  recipes.clear();
}

void testAddIngredientsToRecipe(){
  std::cout << "Testing addIngredientsToRecipe...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe = createRecipeFromData("Test Recipe", 15, MealType::Breakfast, DietType::Vegan);
  recipes.push_back(recipe);

  // Simulate adding ingredients
  recipe->addIngredient(Ingredient("Flour", "2 cups"));
  recipe->addIngredient(Ingredient("Sugar", "1 cup"));

  assert(recipe->getIngredients().size() == 2);

  LinkedList<Ingredient>::const_iterator it = recipe->getIngredients().begin();
  assert(it != recipe->getIngredients().end() && it->getName() == "Flour");
  assert(it != recipe->getIngredients().end() && it->getQuantity() == "2 cups");
  ++it;
  assert(it != recipe->getIngredients().end() && it->getName() == "Sugar");
  assert(it != recipe->getIngredients().end() && it->getQuantity() == "1 cup");

  // Cleanup
  recipes.clear();
}

void testListRecipes() {
  std::cout << "Testing listRecipes...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe1 = createRecipeFromData("Recipe 1", 20, MealType::Lunch, DietType::Vegetarian);
  Recipe* recipe2 = createRecipeFromData("Recipe 2", 40, MealType::Dinner, DietType::Omnivore);

  recipes.push_back(recipe1);
  recipes.push_back(recipe2);

  std::ostringstream output;
  std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

  listRecipes(recipes);

  std::cout.rdbuf(oldCout);
  std::string result = output.str();

  assert(result.find("Recipe 1") != std::string::npos);
  assert(result.find("Recipe 2") != std::string::npos);

  // Cleanup
  recipes.clear();
}

void testSaveAndLoadRecipes() {
  std::cout << "Testing save and load recipes...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe = createRecipeFromData("Saved Recipe", 15, MealType::Breakfast, DietType::Vegan);
  recipes.push_back(recipe);

  saveRecipes(recipes);

  LinkedList<Recipe*> loadedRecipes;
  loadRecipes(loadedRecipes);


  LinkedList<Recipe*>::iterator it = loadedRecipes.begin();
  Recipe* recipePtr = *it;

  assert(!loadedRecipes.isEmpty());
  assert(loadedRecipes.size() == 1);
  assert(recipePtr->getTitle() == "Saved Recipe");

  // Cleanup
  recipes.clear();
  loadedRecipes.clear();
}

void testRemoveRecipe() {
  std::cout << "Testing removeRecipe...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe = createRecipeFromData("Recipe to Remove", 25, MealType::Lunch, DietType::Omnivore);
  recipes.push_back(recipe);

  assert(!recipes.isEmpty());
  assert(recipes.size() == 1);

  recipes.removeIf([](Recipe* r) {
    if (r->getTitle() == "Recipe to Remove") {
      delete r;
      return true;
    }
    return false;
  });

  assert(recipes.isEmpty());
}

void testEditRecipe() {
  std::cout << "Testing editRecipe...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe = createRecipeFromData("Editable Recipe", 10, MealType::Breakfast, DietType::Vegetarian);
  recipes.push_back(recipe);

  recipe->setTitle("Edited Recipe");
  recipe->setPrepTime(20);
  recipe->setMealType(MealType::Dinner);

  assert(recipe->getTitle() == "Edited Recipe");
  assert(recipe->getPrepTime() == 20);
  assert(recipe->getMealType() == MealType::Dinner);

  // Cleanup
  recipes.clear();
}

void testSearchRecipes() {
  std::cout << "Testing searchRecipes...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe1 = createRecipeFromData("Searchable Recipe", 15, MealType::Lunch, DietType::Vegan);
  Recipe* recipe2 = createRecipeFromData("Another Recipe", 30, MealType::Dinner, DietType::Omnivore);

  recipes.push_back(recipe1);
  recipes.push_back(recipe2);

  Recipe* foundRecipe = findRecipeByTitle(recipes, "Searchable Recipe");
  assert(foundRecipe != nullptr);
  assert(foundRecipe->getTitle() == "Searchable Recipe");

  // Cleanup
  recipes.clear();
}

void testSortRecipes() {
  std::cout << "Testing sortRecipes...\n";
  LinkedList<Recipe*> recipes;
  Recipe* recipe1 = createRecipeFromData("B Recipe", 20, MealType::Lunch, DietType::Vegetarian);
  Recipe* recipe2 = createRecipeFromData("A Recipe", 10, MealType::Breakfast, DietType::Vegan);

  recipes.push_back(recipe1);
  recipes.push_back(recipe2);

  recipes.sort(Recipe::compareByTitle);

  if (!recipes.isEmpty()) {
    LinkedList<Recipe*>::iterator it1 = recipes.begin();
    LinkedList<Recipe*>::iterator it2 = recipes.begin();
    ++it2;

    if (it1 != recipes.end() && it2 != recipes.end()) {
      Recipe* recipePtr1 = *it1;
      Recipe* recipePtr2 = *it2;

      assert(recipePtr1->getTitle() == "A Recipe");
      assert(recipePtr2->getTitle() == "B Recipe");
    } else {
      std::cerr << "Error: Invalid iterators after sorting.\n";
    }
  } else {
    std::cerr << "Error: Recipe list is empty after sorting.\n";
  }

  // Cleanup
  recipes.clear();
}


