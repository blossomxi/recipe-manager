# Developer Documentation: Usage, Setup, and Structure

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

## Project Structure

```
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
├── screenshots/             # Program screenshots
├── tests/
│   └── test_main.cpp        # Main test entry point
```

- See `docs/UML.png` for the full class diagram.
- See `docs/Proposal.pdf` for the original project proposal. 