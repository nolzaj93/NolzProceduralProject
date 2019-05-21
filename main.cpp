#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "mainPrototypes.h"


/** @file main.cpp
 *  @brief This file is C++ source code for the Procedural Project.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

/**
 * @brief This is the main function which is the starting point of the program.
 * @return - If the program runs to completion then this function returns zero.
 */
int main() {

    //Welcome message printed to the console.
    std::cout << "Welcome to the Production Line Tracker!\n";

    //Declare and initialize inputNumber which is used to hold number input by user.
    int inputNumber = 0;

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
            case 1:
                produceItems();
                break;
            case 2:
                addEmployeeAccount();
                break;
            case 3:
                addNewProduct();
                break;
            case 4:
                displayProductionStatistics();
                break;
            case 5:
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

    if (currentCatalogFile.is_open()) {
        std::cout << '\n' << "Existing products: " << '\n';

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
    std::string itemTypeCode;

    // write code to set the item type code based on the selected item type
    // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
    switch (itemTypeChoice) {
        case 1:
            itemTypeCode = "Audio";
            break;
        case 2:
            itemTypeCode = "Visual";
            break;
        case 3:
            itemTypeCode = "AudioMobile";
            break;
        case 4:
            itemTypeCode = "VisualMobile";
            break;
        default:
            break;
    }

    std::string newProduct = manufacturer + " " + prodName + " " + itemTypeCode;

    std::ofstream catalogFile;
    catalogFile.open("catalog.txt", std::ios::app);
    catalogFile << newProduct << std::endl;
    catalogFile.close();

    std::cout << newProduct << " has been added to the product catalog.\n" << std::endl;


}

void produceItems() {

    static int productionNumber;
    static int audioSerialNum;
    static int audioMobileSerialNum;
    static int visualSerialNum;
    static int visualMobileSerialNum;

    std::string line;
    std::ifstream itemNumbers("itemNumbers.txt");
    if (itemNumbers.is_open()) {

        itemNumbers >> productionNumber >> audioSerialNum >> audioMobileSerialNum >> visualSerialNum
                    >> visualMobileSerialNum;
        itemNumbers.close();
    } else {
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

    //Ignores the newline character read when the user presses enter/return.
    std::cin.ignore();

    std::cout << "Enter the Product Name\n";
    std::string prodName;
    std::getline(std::cin, prodName);

    std::cout << "Enter the item type\n";
    std::cout << "1. Audio\n" <<
              "2. Visual\n" <<
              "3. AudioMobile\n" <<
              "4. VisualMobile\n";

    int itemTypeChoice;
    std::cin >> itemTypeChoice;
    std::string itemType;
    std::string itemTypeCode;

    // write code to set the item type code based on the selected item type
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

    std::ofstream productionFile;
    productionFile.open("production.txt", std::ios::app);


    // add a loop to record production, for now simply by
    // outputting production number and serial number
    for (int counter = 0; counter < numProduced; counter++) {

        std::ostringstream productInfo;
        productInfo << "Manufacturer: " << manufacturer << " Product Name: " << prodName
                    << " Item Type: " << itemType << " Production Number: " << std::to_string(productionNumber++)
                    << " Serial Number: " << manufacturer.substr(0, 3) << itemTypeCode;

        if (itemTypeCode == "MM")
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(audioSerialNum++);
        else if (itemTypeCode == "VI")
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(audioMobileSerialNum++);
        else if (itemTypeCode == "AM")
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(visualSerialNum++);
        else
            productInfo << std::setfill('0') << std::setw(5) << std::to_string(visualMobileSerialNum++);

        std::string prodAndSerialString = productInfo.str();
        std::cout << prodAndSerialString << std::endl;
        productionFile << prodAndSerialString << std::endl;

    }
    productionFile.close();


    std::ofstream itemNumbersOut;
    itemNumbersOut.open("itemNumbers.txt");
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
