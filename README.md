# Fork & Function: Recipe Manager

## Project Overview
A C++ recipe management system that helps users organize and filter recipes based on dietary preferences and ingredients.

## Current Features
- Recipe Management:
  - Add new recipes with title and prep time
  - List all recipes with details
  - Add ingredients to existing recipes

- Easy Input System:
  - Quick meal type selection (use number or first letter):
    - 1/b - Breakfast
    - 2/l - Lunch
    - 3/d - Dinner
    - 4/s - Snack
  - Simple diet type selection:
    - 1/v - Vegan
    - 2/g - Vegetarian
    - 3/p - Pescatarian
    - 4/o - Omnivore

- Data Persistence:
  - Save recipes to file
  - Load recipes on startup

## Implementation Details
- **OOP Design**:
  - Abstract `Recipe` base class
  - Specialized recipe types (Vegan, Vegetarian, Pescatarian, Omnivore)
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
├── PescatarianRecipe.h/cpp
├── OmnivoreRecipe.h/cpp
├── Ingredient.h/cpp     # Ingredient management
├── LinkedList.h/tpp    # Custom linked list implementation
└── main.cpp            # Program entry and UI
```

## Development Roadmap
### Stage 1: Core Structure ✓
- Basic recipe class hierarchy
- Custom LinkedList implementation
- Console UI foundation

### Stage 2: Recipe Management ✓
- Add/list recipes
- Ingredient management
- File I/O for persistence

### Stage 3: Advanced Features (In Progress)
- Recipe search and filtering
- Sorting implementation
- Enhanced user interface

### Stage 4: Polish (Planned)
- Input validation
- Error handling
- User experience improvements
