#include "assignment1.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cmath>

// Constructor for Get_Data class
Get_Data::Get_Data() {
    data_size = 0;
}

// Read data from a file and store it in the data_array
void Get_Data::ReadFile(const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Print an error message if the file cannot be opened
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line) && data_size < 150) {
        std::istringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (data_size < 150) {
                try {
                    // Convert each token in the file to an integer and store it in data_array
                    data_array[data_size++] = std::stoi(token);
                } catch (const std::invalid_argument& e) {
                    // Handle invalid data in the file and print an error message
                    std::cerr << "Error: Invalid data in file '" << filename << "': " << e.what() << std::endl;
                }
            }
        }
    }

    file.close();
}

// Print the data_array to the standard output
void Get_Data::PrintData() {
    for (int i = 0; i < data_size; ++i) {
        // Print each element in data_array
        std::cout << data_array[i];
        if (i < data_size - 1) {
            std::cout << ", ";
        }
    }
}

// Constructor for the ArraySearch class
Get_Data::ArraySearch::ArraySearch(int* arr, int size) {
    array = arr;
    arraySize = size;
}

// Search for a target value in the array and return its index
int Get_Data::ArraySearch::findIndex(int target) {
    for (int i = 0; i < arraySize; ++i) {
        if (array[i] == target) {
            // Return the index if the target is found
            return i;
        }
    }

    // If the target is not found, return -1 to indicate it was not found.
    return -1;
}

// Modify the value at a specified index in the data_array
int Get_Data::ModifyValue(int index, int newValue) {
    try {
        // Check for non-integer input for newValue
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            throw std::invalid_argument("Invalid input for newValue. Please enter a valid integer.");
        }

        if (index >= 0 && index < data_size) {
            // Check for non-integer input for newValue
            std::ostringstream oss;
            oss << newValue;
            if (!oss.str().empty() && oss.str().find_first_not_of("-0123456789") != std::string::npos) {
                throw std::invalid_argument("Invalid value (decimal) for ModifyValue function.");
            }

            int oldValue = data_array[index];
            data_array[index] = newValue;
            return oldValue; // Return the old value
        } else {
            // Handle an invalid index and print an error message
            throw std::out_of_range("Invalid index for ModifyValue function.");
        }
    } catch (const std::invalid_argument& ex) {
        // Print an error message for invalid argument exception and exit with an error code
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1); // Exit the program with an error code
    } catch (const std::out_of_range& ex) {
        // Print an error message for out of range exception and exit with an error code
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1); // Exit the program with an error code
    }
}

// Add an integer to the end of the data_array
void Get_Data::AddInteger(int value) {
    try {
        if (data_size < 150) {
            // Check if the input value is an integer
            if (std::cin.fail()) {
                std::cin.clear(); // Clear the fail state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                throw std::invalid_argument("Invalid input for value. Please enter a valid integer.");
            }

            data_array[data_size++] = value; // Add the integer to data_array if there is space
        } else {
            // Handle overflow error when the array is full and print an error message
            throw std::overflow_error("Array is full. Cannot add more integers.");
        }
    } catch (const std::invalid_argument& ex) {
        // Print an error message for invalid argument exception and exit with an error code
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1); // Exit the program with an error code
    } catch (const std::overflow_error& ex) {
        // Print an error message for overflow error and exit with an error code
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1); // Exit the program with an error code
    }
}



// Replace the value at a specified index with 0
void Get_Data::ReplaceWithZero(int index) {
    if (index >= 0 && index < data_size) {
        // Replace the value at the specified index with 0
        data_array[index] = 0;
    } else {
        // Handle an invalid index and print an error message
        std::cerr << "Error: Invalid index for ReplaceWithZero function." << std::endl;
    }
}

// Main function
int main() {
    Get_Data data;
    const char* filename = "data.csv"; // Enter file name here

    data.ReadFile(filename);
    
    int myArray[100]; // Create a new array of the same size
    for (int i = 0; i < data.data_size; ++i) {
        // Copy each element from data_array to myArray
        myArray[i] = data.data_array[i];
    }
    int arraySize = data.data_size;

    Get_Data::ArraySearch searcher(myArray, arraySize);

    int target;
    std::cout << "\nEnter an integer to search for: "; // Prompt user for input
    std::cin >> target;

    int index = searcher.findIndex(target);

    if (index != -1) {
        // Print the result if the target is found
        std::cout << "The integer " << target << " is present at index " << index << std::endl;
    } else {
        // Print a message if the target is not found
        std::cout << "The integer " << target << " was not found in the array." << std::endl;
    }
    
    // Modify the value at a specified index
    int indexToModify;
    int newValue;
    std::cout << "Enter an index to modify: ";
    std::cin >> indexToModify;
    std::cout << "Enter a new value: ";
    std::cin >> newValue;

    int oldValue = data.ModifyValue(indexToModify, newValue);
    if (oldValue != -1) {
        // Print the old value if modification is successful
        std::cout << "Modified value at index " << indexToModify << ". Old value: " << oldValue << std::endl;
    }

    // Add a new integer to the end of the array
    int newInteger;
    std::cout << "Enter a new integer to add to the array: ";
    std::cin >> newInteger;
    data.AddInteger(newInteger);

    // Replace the value at a specified index with 0
    int indexToReplace;
    std::cout << "Enter an index to replace with 0: ";
    std::cin >> indexToReplace;
    data.ReplaceWithZero(indexToReplace);

    // Print the updated array
    data.PrintData();
    return 0;
}
