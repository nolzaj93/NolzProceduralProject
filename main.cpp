/** @file main.cpp
 *  @brief This file is C++ source code for the COP2001 Procedural Project.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "mainPrototypes.h"

/**
 * @brief This is the main function which is the starting point of the program.
 * @return - If the program runs to completion then this function returns zero.
 */
int main() {

    //Welcome message printed to the console.
    std::cout << "Welcome to the Production Line Tracker!\n";

    //Declare and initialize inputNumber which is used to hold number input by user.
    char inputNumber = '0';

    //Declare and initialize programIsRunning as a flag bool for the while loop.
    bool programIsRunning = true;

    //While loop that is repeated until the user enters 6 to exit which sets programIsRunning to false.
    while (programIsRunning) {

        //Prompts the user to enter a number between 1 and 5
        std::cout << "\n" << "Type in a number between 1 and 5 to run the respective function and press enter.\n\n";

        showMenu();

        std::cin >> inputNumber;

        //Switch statement calls the corresponding function, or if the the user enters 6 the loop is broken.
        switch (inputNumber) {
            case '1':
                produceItems();
                break;
            case '2':
                addEmployeeAccount();
                break;
            case '3':
                addNewProduct();
                break;
            case '4':
                displayProductionStatistics();
                break;
            case '5':
                programIsRunning = false;
                break;
            default:
                std::cout << "Your input was invalid. Please try again.\n";
                break;
        }
    }
    return 0;
}

void showMenu() {

    //prints the menu to the console
    std::cout << "1. Produce Items\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add New Product\n";
    std::cout << "4. Display Production Statistics\n";
    std::cout << "5. Exit\n";
}

void showCatalog() {

    //Existing products are printed from catalog.txt if the file exists already
    std::string nextLine;
    std::ifstream currentCatalogFile("catalog.txt");

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (currentCatalogFile.is_open()) {
        std::cout << '\n' << "Current catalog: " << '\n';

        while (getline(currentCatalogFile, nextLine)) {
            std::cout << nextLine << '\n';
        }
        currentCatalogFile.close();
    } else std::cout << "The product catalog is empty.\n";
}

void addNewProduct() {

    showCatalog();

    std::cout << "\n" << "Enter the Manufacturer" << std::endl;
    std::string manufacturer;
    std::cin >> manufacturer;

    //Ignores the newline character read when the user presses enter/return.
    std::cin.ignore();

    std::string prodName;
    std::cout << "Enter the Product Name" << std::endl;
    std::getline(std::cin, prodName);

    std::cout << "Enter the item type\n";
    std::cout << "1. Audio\n" <<
              "2. Visual\n" <<
              "3. AudioMobile\n" <<
              "4. VisualMobile\n";
    int itemTypeChoice;
    std::cin >> itemTypeChoice;
    std::string itemType;

    // itemType is set depending on itemTypeChoice
    switch (itemTypeChoice) {
        case 1:
            itemType = "Audio";
            break;
        case 2:
            itemType = "Visual";
            break;
        case 3:
            itemType = "AudioMobile";
            break;
        case 4:
            itemType = "VisualMobile";
            break;
        default:
            break;
    }

    //newProduct string is set by concatenating manufacturer prodName itemType
    std::string newProduct = manufacturer + " " + prodName + " " + itemType;

    //newProduct string is appended to catalog.txt file
    std::ofstream catalogFile;
    catalogFile.open("catalog.txt", std::ios::app);
    catalogFile << newProduct << std::endl;
    catalogFile.close();

    std::cout << newProduct << " has been added to the product catalog.\n" << std::endl;
}

void produceItems() {

    //Production and serial numbers are declared.
    static int productionNumber;
    static int audioSerialNum;
    static int audioMobileSerialNum;
    static int visualSerialNum;
    static int visualMobileSerialNum;

    std::fstream itemNumbers("itemNumbers.txt");
    if (itemNumbers.is_open()) {
        // Production and serial numbers are written to a file
        itemNumbers >> productionNumber >> audioSerialNum >> audioMobileSerialNum >> visualSerialNum
                    >> visualMobileSerialNum;
        itemNumbers.close();
    } else {

        // Production and serial numbers are set to 1 if itemNumbers.txt does not exist.
        productionNumber = 1;
        audioSerialNum = 1;
        audioMobileSerialNum = 1;
        visualSerialNum = 1;
        visualMobileSerialNum = 1;
    }

    showCatalog();

    // Eventually the user will be able to choose the item to produce.
    std::cout << "\n" << "Enter the Manufacturer\n";
    std::string manufacturer;
    std::cin >> manufacturer;

    std::cout << "Enter the Product Name\n";
    std::string prodName;
    std::getline(std::cin, prodName);

    //Ignores the newline character read when the user presses enter/return.
    std::cin.ignore();

    std::cout << "Enter the item type\n";
    std::cout << "1. Audio\n" <<
              "2. Visual\n" <<
              "3. AudioMobile\n" <<
              "4. VisualMobile\n";

    int itemTypeChoice;
    std::cin >> itemTypeChoice;
    std::string itemType;
    std::string itemTypeCode;

    // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
    switch (itemTypeChoice) {
        case 1:
            itemType = "Audio";
            itemTypeCode = "MM";
            break;
        case 2:
            itemType = "Visual";
            itemTypeCode = "VI";
            break;
        case 3:
            itemType = "AudioMobile";
            itemTypeCode = "AM";
            break;
        case 4:
            itemType = "VisualMobile";
            itemTypeCode = "VM";
            break;
        default:
            break;
    }

    std::cout << "Enter the number of items that were produced\n";
    int numProduced;
    std::cin >> numProduced;

    // Declares productionFile object and opens production.txt
    std::ofstream productionFile;
    productionFile.open("production.txt", std::ios::app);


    // add a loop to record production, for now simply by
    // outputting production number and serial number
    for (int counter = 0; counter < numProduced; counter++) {

        //productInfo output string stream holds all product information to be written to production.txt
        std::ostringstream productInfo;
        productInfo << "Manufacturer: " << manufacturer << " Product Name: " << prodName
                    << " Item Type: " << itemType << " Production Number: " << std::to_string(productionNumber++)
                    << " Serial Number: " << manufacturer.substr(0, 3) << itemTypeCode;

        //Adds respective serial number to the productInfo ostringstream object
        if (itemTypeCode == "MM")
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(audioSerialNum++);
        else if (itemTypeCode == "VI")
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(audioMobileSerialNum++);
        else if (itemTypeCode == "AM")
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(visualSerialNum++);
        else
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(visualMobileSerialNum++);

        //Outputs a string from the productInfo object on each iteration, and writes it to production.txt
        std::cout << productInfo.str() << std::endl;
        productionFile << productInfo.str() << std::endl;
    }
    productionFile.close();

    //itemNumbersOut object created and itemNumbers.txt is opened if it exists, else a new text file is created.
    std::ofstream itemNumbersOut;
    itemNumbersOut.open("itemNumbers.txt");

    //Writes the production and serial numbers to the itemNumbers.txt file.
    itemNumbersOut << productionNumber << " " << audioSerialNum << " " << audioMobileSerialNum << " " << visualSerialNum
                   << " " << visualMobileSerialNum;
    itemNumbersOut.close();

}

void addEmployeeAccount() {
    std::cout << "Add Employee Account Stub\n";
}

void addMusicPlayer() {

    //Adds Audio or AudioMobile player
    std::cout << "Add Music Player Stub\n";
}

void addMoviePlayer() {

    //Adds Visual or VisualMobile player
    std::cout << "Add Movie Player Stub\n";
}

void displayProductionStatistics() {
    std::cout << "Display Production Statistics Stub\n";
}
