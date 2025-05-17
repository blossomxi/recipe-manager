# Fork & Function — Recipe Manager
*Group 1: Austin Luong, Damian Perez, John Rilles, & Max Owens* 

## Overview
Fork & Function is a C++11 command‑line application built by a four‑member team. It showcases robust Object‑Oriented design, reusable data structures, and reliable persistence and search features. With advanced search/sort capabilities and a modular architecture, it delivers a seamless CLI experience.

## Key Features
- **Flexible Data Storage**  
  Templated `LinkedList<T>` for type‑safe, efficient collections of recipes and ingredients.  
- **Advanced Search & Sort**  
  Linear search across multiple fields and in‑list insertion sort for fast retrieval and ordering.  
- **Automatic Persistence**  
  Loads recipes from `recipes.txt` on startup and saves on exit, no extra steps required.  
- **Polymorphic OOP Design**  
  Abstract `Recipe` base class with `VeganRecipe`, `VegetarianRecipe`, and `OmnivoreRecipe` subclasses.  
- **Extensible Architecture**  
  UML‑driven design and clean separation of concerns make future enhancements straightforward.

## Architecture & Design
- **UML‑First Planning**  
  Complete class diagrams defined before coding to ensure maintainability.  
- **Header‑Only Templates**  
  Zero‑overhead `LinkedList<T>` implementation (`.h`/`.tpp`) for both recipes and ingredients.  
- **Central Controller**  
  `RecipeManager` orchestrates CRUD operations, searching, sorting, and file I/O.  
- **Resilient CLI**  
  Defensive input validation and meaningful feedback for all user interactions.

## Installation & Usage
```bash
# Clone the repository
git clone <repo-url>
cd recipe-manager

# Build
mkdir build && cd build
cmake ..
make

# Run
./recipe-manager
```

## Testing

All core tests are run via a single test entry point: `tests/test_main.cpp`. This file simply includes `src/testDriver.h` and calls `testDriver()`, which runs a comprehensive suite covering adding, editing, listing, saving/loading, removing, searching, and sorting recipes using the custom data structures and logic implemented in the project.

There are no class/function-specific test files in the `tests/` folder—everything is handled by `test_main.cpp` for simplicity and maintainability.

### Running the Test Driver

To run the tests:

```bash
g++ -std=c++11 -I./src tests/test_main.cpp -o test_driver
./test_driver
```

All tests should pass with the message:

```
Running tests...
All tests passed!
```

If any assertion fails, the test driver will indicate which test failed. This ensures the integrity of the main features and helps with regression testing during development.

## Screenshots

### Main Menu
![Main Menu](docs/images/main_menu.png)

### Search by Ingredient
![Search by Ingredient](docs/images/search_ingredient.png)

### List (Unsorted, Sample Data)
![List Unsorted](docs/images/list_unsorted.png)

### List Sorted by Prep Time
![List Sorted by Prep Time](docs/images/list_sorted.png)

### Add New Recipe
![Add New Recipe](docs/images/add_recipe.png)

### Add Ingredients to New Recipe
![Add Ingredients to New Recipe](docs/images/add_ingredients.png)

## Project Structure

```tree
recipe-manager/
├── .gitignore
├── README.md
├── recipes.txt              # Recipe database with 50+ pre-loaded recipes
├── recipe-manager           # Compiled binary (after build)
├── src/
│   ├── main.cpp
│   ├── driver.h
│   ├── Recipe.h/.cpp
│   ├── VeganRecipe.h/.cpp
│   ├── VegetarianRecipe.h/.cpp
│   ├── OmnivoreRecipe.h/.cpp
│   ├── Ingredient.h/.cpp
│   ├── LinkedList.h/.tpp
│   ├── RecipeManager.h/.cpp
│   ├── MealType.h
│   ├── DietType.h
├── docs/
│   ├── UML.png              # UML class diagram
│   ├── Proposal.pdf         # Project proposal document
│   └── images/
│       ├── main_menu.png
│       ├── search_ingredient.png
│       ├── list_unsorted.png
│       ├── list_sorted.png
│       ├── add_recipe.png
│       └── add_ingredients.png
```

- See `docs/UML.png` for the full class diagram.
- See `docs/Proposal.pdf` for the original project proposal.

## Future & Recap
### Completed Phases
- **Phase 1:** UML design and planning
- **Phase 2:** Core data structures and enums
- **Phase 3:** Recipe and ingredient management
- **Phase 4:** Persistence, search, and sort
- **Phase 5:** CLI polish and error handling

### Skipped
- Additional diet types
- Nutrition data
- GUI interface
- User authentication
- Recipe scaling

### Future Functionality Ideas
- GUI interface
- Nutrition module
- User accounts
- Import/export recipes
- Step-by-step instructions
- Grocery list generation

---

For questions or contributions, please open an issue or submit a pull request.

Special thanks to Professor Corey Carito for guidance.