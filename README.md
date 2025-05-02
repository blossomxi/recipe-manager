# Fork & Function: Recipe Manager

## Project Overview
A C++ recipe management system that helps users organize and filter recipes based on dietary preferences and ingredients.

## Current Features
- **Comprehensive Recipe Management:**
  - Add new recipes specifying title, preparation time, meal type (`breakfast`, `lunch`, `dinner`, `snack`, `dessert`), and diet type (`vegan`, `vegetarian`, `omnivore`).
  - Add multiple ingredients with name and quantity to existing recipes using a bulk entry format.
  - List all stored recipes, displaying their details.
- **Data Persistence:**
  - Automatically save the current recipe list to a file upon exit.
  - Automatically load recipes from the file on program startup.
- **Foundation:**
  - Object-oriented design with `Recipe` inheritance (`VeganRecipe`, `VegetarianRecipe`, `OmnivoreRecipe`).
  - Custom `LinkedList` template class for managing recipes and ingredients.

## Implementation Details
- **OOP Design**:
  - Abstract `Recipe` base class
  - Specialized recipe types (Vegan, Vegetarian, Omnivore)
  - Ingredient class with name and quantity management

- **Data Structures**:
  - Custom `LinkedList<T>` template class
  - Iterator support for traversal
  - Memory-efficient ingredient storage

- **Templates & Polymorphism**:
  - `LinkedList<T>` template class for flexible data storage
  - Polymorphic recipe hierarchy for extensible design
  - Iterator implementation for standard-library compatibility

## Planned Features
- Recipe search by title/ingredients
- Ingredient blacklist filtering
- Recipe sorting by name/prep time
- Enhanced recipe categories and tags
- Recipe instructions and steps

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
└── main.cpp            # Program entry and UI
```

## Development Roadmap
### Stage 1: Core Structure ✓
- Basic recipe class hierarchy (`Recipe`, `Vegan`, `Vegetarian`, `Omnivore`)
- Custom `LinkedList<T>` implementation with iterators
- Foundational console UI structure in `main.cpp`

### Stage 2: Recipe Management & Persistence ✓
- Implement functions to add recipes with core details (title, prep time).
- Implement functions to add ingredients to recipes.
- Implement listing of all recipes.
- Integrate file I/O for saving and loading recipes.

### Stage 3: Advanced Input & Features (Partially Complete)
- Streamlined recipe input (single-line creation with meal/diet keywords, bulk ingredients) ✓
- Recipe search by title/ingredients (Planned)
- Ingredient blacklist filtering (Planned)
- Sorting implementation (Planned)

### Stage 4: Polish (Planned)
- Robust input validation
- Comprehensive error handling
- General user experience improvements
