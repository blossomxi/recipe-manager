# Fork & Function: Recipe Manager

## Project Overview
A C++ recipe management system that helps users organize and filter recipes based on dietary preferences and ingredients.

## Current Features
- **Comprehensive Recipe Management:**
  - Add new recipes specifying title, preparation time, meal type (`breakfast`, `lunch`, `dinner`, `snack`, `dessert`), and diet type (`vegan`, `vegetarian`, `omnivore`).
  - Add multiple ingredients with name and quantity to existing recipes using a bulk entry format.
  - List all stored recipes, displaying their details.
  - Search recipes by title, ingredient, meal type, or diet type.
  - Sort recipes by title, preparation time, or meal type.
  - Edit existing recipes (title, prep time, meal type).
  - Remove recipes with confirmation.
- **Data Persistence:**
  - Automatically save the current recipe list to a file upon exit.
  - Automatically load recipes from the file on program startup.
  - Serialized storage format for complete recipe data.
- **Foundation:**
  - Object-oriented design with `Recipe` inheritance (`VeganRecipe`, `VegetarianRecipe`, `OmnivoreRecipe`).
  - Custom `LinkedList` template class for managing recipes and ingredients.
  - Ingredient validation and blacklist system.
  - Enums (`MealType`, `DietType`) are defined in their own headers (`MealType.h`, `DietType.h`) for UML compliance.

## Implementation Details
- **OOP Design**:
  - Abstract `Recipe` base class with pure virtual methods
  - Specialized recipe types (Vegan, Vegetarian, Omnivore) with diet-specific validation
  - Ingredient class with name and quantity management
  - Polymorphic recipe hierarchy for extensible design

- **Data Structures**:
  - Custom `LinkedList<T>` template class with iterator support
  - Efficient ingredient storage and management
  - Sorting and searching algorithms
  - Memory-safe smart pointer usage

- **Templates & Polymorphism**:
  - `LinkedList<T>` template class for flexible data storage
  - Polymorphic recipe hierarchy for extensible design
  - Iterator implementation for standard-library compatibility
  - Type-safe ingredient validation

## Building and Running
```bash
# Compile the project
g++ -std=c++17 src/*.cpp -o recipe_manager

# Run the program
./recipe_manager
```

## Project Structure
```
src/
├── Recipe.h/cpp         # Abstract base class
├── VeganRecipe.h/cpp    # Vegan recipe implementation
├── VegetarianRecipe.h/cpp
├── OmnivoreRecipe.h/cpp
├── Ingredient.h/cpp     # Ingredient management
├── LinkedList.h/tpp    # Custom linked list implementation
├── RecipeManager.h/cpp  # Recipe creation and management
├── MealType.h           # Enum for meal types
├── DietType.h           # Enum for diet types
└── main.cpp            # Program entry and UI
```

## File Format: recipes.txt
Each recipe is stored as a single line in the following format:
```
Type|Title|PrepTime|MealType|DietType|ingredient1:quantity1;ingredient2:quantity2;...
```
- **Type**: Vegan, Vegetarian, or Omnivore
- **Title**: Recipe name
- **PrepTime**: Preparation time in minutes (integer)
- **MealType**: Breakfast, Lunch, Dinner, Snack, Dessert, or Other
- **DietType**: Vegan, Vegetarian, Omnivore, or Other
- **Ingredients**: Each ingredient is `name:quantity`, separated by semicolons

**Example:**
```
Vegan|Tofu Scramble|15|Breakfast|Vegan|tofu:200g;spinach:50g;onion:30g;turmeric:1tsp
```

## Development Status
### Completed Features ✓
- Basic recipe class hierarchy with inheritance
- Custom `LinkedList<T>` implementation with iterators
- Recipe management (add, edit, remove)
- Ingredient management with validation
- File I/O with serialization
- Search functionality
- Sort functionality
- Diet-specific ingredient validation
- Blacklist system for ingredients
- UML-compliant enums and file structure

### Future Enhancements
- Recipe instructions and steps
- Enhanced recipe categories and tags
- Recipe export/import functionality
- GUI interface
- Recipe scaling functionality
