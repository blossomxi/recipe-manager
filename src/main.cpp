// src/main.cpp
#include <iostream>
#include "driver.h"
#include "testDriver.h"


bool TEST = false;//test flag

int main() {

    if (TEST) {
        std::cout << "Running in test mode." << std::endl;
        
        return testDriver(); // Start the test function
    } else {
        std::cout << "Running in normal mode." << std::endl;
        return driver(); // Start the driver function
    }
}

