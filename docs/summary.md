# Fork & Function — Recipe Manager: High-Level Summary

Fork & Function is a C++11 command-line application designed for efficient recipe management. Built by a four-member team, it demonstrates robust Object-Oriented Programming, reusable data structures, and reliable persistence and search features. The program offers advanced search and sort capabilities, a modular architecture, and a seamless CLI experience.

## Key Features
- **Flexible Data Storage:** Uses a templated `LinkedList<T>` for type-safe, efficient collections of recipes and ingredients.
- **Advanced Search & Sort:** Linear search across multiple fields and in-list insertion sort for fast retrieval and ordering.
- **Automatic Persistence:** Loads recipes from `recipes.txt` on startup and saves on exit.
- **Polymorphic OOP Design:** Abstract `Recipe` base class with `VeganRecipe`, `VegetarianRecipe`, and `OmnivoreRecipe` subclasses.
- **Extensible Architecture:** UML-driven design and clean separation of concerns for easy future enhancements. 