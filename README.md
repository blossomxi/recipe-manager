# Fork & Function — Recipe Manager
*Group 1: Austin Luong, Damian Perez, John Rilles, & Max Owens*

## Quick Overview
Fork & Function is a C++11 command-line application for efficient recipe management, featuring robust OOP, custom data structures, and advanced search/sort capabilities.

- For a high-level summary, see `docs/summary.md`.
- For developer setup, usage, and structure, see `docs/documents.md`.
- For recap, future plans, and skipped features, see `docs/recap_and_future.md`.
- For UML and design docs, see `docs/UML.md`.
- For screenshots, see the `screenshots/` folder.

## Testing
All core tests are run via a single test entry point: `tests/test_main.cpp`. This file simply includes `src/testDriver.h` and calls `testDriver()`, which runs a comprehensive suite covering all major features.

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