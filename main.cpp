/******************************************************************************
 * Project: Simple Password Manager - Console App
 * File: main.cpp
 * Description:
 *   The entry point and main logic to the entire app.
 *
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.0
 * Author: Ghost
 * Created On: 1-30-2025
 * Last Modified: 1-30-2025
 *****************************************************************************/

#include <iostream> // for displaying to the terminal
#include <fstream> // for writing/reading from file
#include <limits>
#include <string>

// Display message to console
void displayMessage(const std::string& msg) {
    std::cout << msg << std::endl; // endl = end-line which just moves cursor to next line after message
}

// Display main menu
void displayMenu() {
    displayMessage("\nPassword Manager");
    displayMessage(" 1. Add Password");
    displayMessage(" 2. View Passwords");
    displayMessage(" 3. Exit");
    displayMessage("Enter your choice: ");
}

// Function to save password to a file
void SavePassword(const std::string& site, const std::string& password) {
    std::ofstream file("passwords.txt", std::ios::app); // Append(app) mode - any new data is written at end-of-file
    if (file.is_open()) { // best practice is to test if the file was correctly opened before using
        file << site << " " << password << "\n"; // inserts strings into file using space in between to read later
        file.close(); // not required, once out of scope the file closes, but its best practice to manually close it
        displayMessage("Password saved successfully!");
    } else { // if there was an error opening file, we handle it here
        std::cerr << "Error: Unable to open file for writing.\n";
    }
}

// Function to load and display saved passwords
void LoadPasswords() {
    std::ifstream file("passwords.txt");
    if (file.is_open()) {
        std::string site, password;
        displayMessage("\nSaved Passwords:");
        while (file >> site >> password) {
            std::cout << "  Site: " << site << ", Password: " << password << "\n";
        }
        file.close();
    } else {
        std::cerr << "\n[System] No passwords saved yet.\n";
    }
}

int main() {
    int choice;
    std::string site, password;
    
    do {
        displayMenu();
        
        std::cin >> choice; // get menu selection from user
        
        // incase of error, this clears it up. Incase user enters something other than number 
        if (std::cin.fail()) {
            std::cin.clear(); // clears any fail flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 
        }

        switch (choice) { // better than if-statements in this case
            case 1:
                displayMessage("Enter site name: ");
                std::cin >> site;
                displayMessage("Enter password: ");
                std::cin >> password;
                SavePassword(site, password);
                break;
            case 2:
                LoadPasswords();
                break;
            case 3:
                displayMessage("\n[System] Exiting...");
                break;
            default:
                displayMessage("\n[System] Invalid choice. Please try again.");
        }
    
    } while (choice != 3);
    
    return 0;
}
