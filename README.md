# Fork & Function

## Overview
This project is a **Recipe Manager** application developed in C++ using full Object-Oriented Programming principles. It allows users to:
- Add, edit, and remove recipes
- Categorize recipes by meal type or dietary restriction
- Filter recipes by ingredients
- Search for recipes by title or keyword
- Sort recipes alphabetically, by prep time, or by dietary category

## Features
- Add, edit, delete recipes
- Ingredient and dietary filtering
- Categorization by:
	- Meal type (breakfast, lunch, dinner)
	- Dietary restrictions (vegetarian, vegan, pescatarian, omnivore)
- Search (by title or ingredient)
- Sort recipes (by name, prep time, or category)
- Blacklist ingredients to exclude unwanted items

## How Project Meets Guidelines
- **OOP Concepts**:
	- Heavy use of inheritance, composition, abstract classes, and polymorphism
- **Data Structures**:
	- Custom `LinkedList` for recipe management, including support for dynamic insertion, removal, sorting, and searching
- **Algorithms**:
	- Insertion sort to sort recipes alphabetically or by prep time
	- Linear search for finding recipes based on title or ingredients
- **File I/O**:
	- Reading/writing recipes to a `.txt` file to persist user data across sessions
- **Templates/Polymorphism**:
	- `LinkedList<T>` uses templates; recipe management uses polymorphism
- **Focus**:
	- Primarily an **OOP application** focused on user-driven management and filtering of recipes

## Stages of Development

### Stage 1: Basic Class Structure
- Build basic classes: `Recipe`, `Ingredient`
- Implement `LinkedList<T>` template

### Stage 2: Core Features
- Implement recipe creation, editing, and deletion
- Basic search by title

### Stage 3: Advanced Filtering
- Add filtering by meal type, dietary restriction, and blacklist ingredients

### Stage 4: Sorting and File I/O
- Implement Insertion Sort for recipe lists
- Implement file loading/saving for persistence

### Stage 5: UI Polish & Testing
- Refine console interface
- Final testing and bug fixes

### Stage 6: Stretch Features (Optional)
- Add ratings or tags
- Enhance blacklist system with suggestions for substitutions
