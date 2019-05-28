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
#include <vector>
#include "prototypes.h"

/**
 * @brief This is the main function which is the starting point of the program.
 * @return - If the program runs to completion then this function returns zero.
 */
int main() {

    showMenu();

    return 0;
}

void showMenu() {
    std::vector<std::string> productCatalog;

    //Existing products are printed from catalog.txt if the file exists already
    std::string nextLine;
    std::ifstream currentCatalogFile("catalog.txt");

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (currentCatalogFile.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(currentCatalogFile, nextLine)) {
            productCatalog.push_back(nextLine);

        }

    }
    currentCatalogFile.close();

    std::vector<std::string> productionRecord;
    std::ifstream productionFile("production.txt");

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (productionFile.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(productionFile, nextLine)) {
            productionRecord.push_back(nextLine);
        }
    }
    productionFile.close();

    std::vector<std::string> serialNumbers;
    std::ifstream serialNumbersFile("serialnumbers.txt");

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (serialNumbersFile.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(serialNumbersFile, nextLine)) {
            serialNumbers.push_back(nextLine);
        }
    }
    serialNumbersFile.close();

    //Welcome message printed to the console.
    std::cout << "Welcome to the Production Line Tracker!\n";

    //Declare and initialize inputNumber which is used to hold number input by user.
    char inputNumber = '0';

    //Declare and initialize programIsRunning as a flag bool for the while loop.
    bool programIsRunning = true;

    //While loop that is repeated until the user enters 6 to exit which sets programIsRunning to false.
    while (programIsRunning) {

        //Prompts the user to enter a number between 1 and 5
        std::cout << "\n" << "Type in a number between 1 and 5 to run the respective function and press enter.\n"
                  << std::endl;

        //prints the menu to the console
        std::cout << "1. Produce Items\n";
        std::cout << "2. Add Employee Account\n";
        std::cout << "3. Add New Product\n";
        std::cout << "4. Display Production Statistics\n";
        std::cout << "5. Find Production Number." << std::endl;
        std::cout << "6. Exit" << std::endl;

        std::cin >> inputNumber;

        //Switch statement calls the corresponding function, or if the the user enters 6 the loop is broken.
        switch (inputNumber) {
            case '1':
                produceItems(productCatalog, productionRecord, serialNumbers);
                break;
            case '2':
                addEmployeeAccount();
                break;
            case '3':
                addNewProduct(productCatalog);
                break;
            case '4':
                displayProductionStatistics();
                break;
            case '5':
                findProductionNumber(serialNumbers);
                break;
            case '6':
                programIsRunning = false;
                break;
            default:
                std::cout << "Your input was invalid. Please try again." << std::endl;
                break;
        }
    }

}

void showCatalog(std::vector<std::string> &productCatalog) {

    //Existing products are printed from catalog.txt if the file exists already
    std::string nextLine;
    std::ifstream currentCatalogFile("catalog.txt");

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (currentCatalogFile.is_open()) {
        std::cout << '\n' << "Current catalog: " << std::endl;

        //Adds each line to the product catalog vector.
        while (getline(currentCatalogFile, nextLine)) {
            productCatalog.push_back(nextLine);

        }

        //Selection sort of available products by name.
        std::string minimumString;
        std::string temp;
        for (int unsortedBoundary = 0; unsortedBoundary < (productCatalog.size() - 1); unsortedBoundary++) {

            //Finds minimum element in unsorted subarray
            int minimumIndex = unsortedBoundary;
            minimumString = productCatalog[unsortedBoundary];
            for (int unsortedIndex = unsortedBoundary + 1; unsortedIndex < productCatalog.size(); unsortedIndex++) {

                if (minimumString.compare(productCatalog[unsortedIndex]) > 0) {
                    minimumString = productCatalog[unsortedIndex];
                    minimumIndex = unsortedIndex;
                }
            }

            //Swaps the found minimum element with the first element of subarray
            if (minimumIndex != unsortedBoundary) {
                temp = productCatalog[unsortedBoundary];
                productCatalog[unsortedBoundary] = productCatalog[minimumIndex];
                productCatalog[minimumIndex] = temp;
            }

        }

        for (std::string product : productCatalog) {

            std::cout << product << std::endl;
        }
        currentCatalogFile.close();

    } else std::cout << "The product catalog is empty." << std::endl;
}

void produceItems(std::vector<std::string> &productCatalog, std::vector<std::string> &productionRecord,
                  std::vector<std::string> &serialNumbers) {

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

    showCatalog(productCatalog);

    std::string manufacturer;
    std::string prodName;

    //Variables declared to accept input for itemType, itemTypeCode, and itemTypeChoice
    char itemTypeChoice;
    std::string itemType;
    std::string itemTypeCode;
    int numProduced;

    std::string entryIsCorrect;


    //Iterates at least once, and the loop will repeat if the user enters zero when prompted to confirm the input
    // or if the user does not enter a number 1-4.
    do {
        //Ignores the newline character read when the user presses enter/return.
        std::cin.ignore();

        std::cout << "\n" << "Please enter the manufacturer." << std::endl;
        std::getline(std::cin, manufacturer);

        //Ignores the newline character read when the user presses enter/return.
        std::cin.ignore();

        std::cout << "\n" << "Please enter the product name." << std::endl;
        std::getline(std::cin, prodName);


        std::cout << "Please enter the item type\n";
        std::cout << "1. Audio\n" <<
                  "2. Visual\n" <<
                  "3. AudioMobile\n" <<
                  "4. VisualMobile" << std::endl;
        std::cin >> itemTypeChoice;

        switch (itemTypeChoice) {
            case '1':
                itemType = "Audio";
                itemTypeCode = "MM";
                break;
            case '2':
                itemType = "Visual";
                itemTypeCode = "VI";
                break;
            case '3':
                itemType = "AudioMobile";
                itemTypeCode = "AM";
                break;
            case '4':
                itemType = "VisualMobile";
                itemTypeCode = "VM";
                break;
            default:
                std::cout << "Your input was invalid. Please try again." << std::endl;
                continue;
        }

        std::cout << "Please enter the number of items that were produced." << std::endl;
        std::cin >> numProduced;

        //Allows the user to confirm their choice. Loop continues if entryIsCorrect is assigned 0 (false)
        std::cout << "You entered " + manufacturer + " " + prodName + " " + itemType + "Number produced: " +
                     std::to_string(numProduced) + ".\n"
                     + "If this is incorrect enter 0 to try again, or enter any other\n"
                     + "letter or word to continue." << std::endl;
        std::cin >> entryIsCorrect;

    } while (entryIsCorrect == "0");

    // Declares productionFile object and opens production.txt
    std::ofstream productionFile;
    productionFile.open("production.txt", std::ios::app);

    std::ofstream serialNumberFile;
    serialNumberFile.open("serialnumbers.txt", std::ios::app);

    //For loop prints product Info for each product
    for (auto counter = 0; counter < numProduced; counter++) {

        //productInfo output string stream holds all product information to be written to production.txt
        std::ostringstream productInfo;
        productInfo << "Manufacturer: " << manufacturer << " | Product Name: " << prodName
                    << " | Item Type: " << itemType << " | Production Number: " << std::to_string(productionNumber++)
                    << " | Serial Number: ";

        /*
         * Adds respective serial number to the productInfo ostringstream object, serial number is 5 characters wide
         * filled with zeros and added to the end.
         */
        std::ostringstream serialNum;
        serialNum << manufacturer.substr(0, 3) << itemTypeCode;

        if (itemTypeCode == "MM")
            serialNum << std::setfill('0') << std::setw(5) << std::to_string(audioSerialNum++);
        else if (itemTypeCode == "VI")
            serialNum << std::setfill('0') << std::setw(5) << std::to_string(audioMobileSerialNum++);
        else if (itemTypeCode == "AM")
            serialNum << std::setfill('0') << std::setw(5) << std::to_string(visualSerialNum++);
        else
            serialNum << std::setfill('0') << std::setw(5) << std::to_string(visualMobileSerialNum++);

        serialNumbers.push_back(serialNum.str());
        serialNumberFile << serialNumbers[serialNumbers.size() - 1] << std::endl;

        productInfo << serialNum.str();

        //Outputs a string from the productInfo object on each iteration, and writes it to production.txt
        productionRecord.push_back(productInfo.str());
        std::cout << productionRecord[productionRecord.size() - 1] << std::endl;
        productionFile << productionRecord[productionRecord.size() - 1] << std::endl;
    }
    serialNumberFile.close();
    productionFile.close();

    //itemNumbersOut object created and itemNumbers.txt is opened if it exists, else a new text file is created.
    std::ofstream itemNumbersOut;
    itemNumbersOut.open("itemNumbers.txt");

    //Writes the production and serial numbers to the itemNumbers.txt file.
    itemNumbersOut << productionNumber << " " << audioSerialNum << " " << audioMobileSerialNum << " "
                   << visualSerialNum << " " << visualMobileSerialNum;
    itemNumbersOut.close();

}

void addEmployeeAccount() {
    std::cout << "Add Employee Account Stub\n";
}

void addNewProduct(std::vector<std::string> &productCatalog) {
    //prints the current catalog or let's the user know if it is empty.
    showCatalog(productCatalog);

    std::string entryIsCorrect;
    std::string manufacturer;
    std::string prodName;
    char itemTypeChoice;
    std::string itemType;

    std::string productSpecs;

    do {
        //Ignores the newline character read when the user presses enter/return.
        std::cin.ignore();

        std::cout << "\n" << "Please enter the manufacturer." << std::endl;
        std::getline(std::cin, manufacturer);

        //Ignores the newline character read when the user presses enter/return.
        std::cin.ignore();

        std::cout << "\n" << "Please enter the product name." << std::endl;
        std::getline(std::cin, prodName);

        std::cout << "Please enter the item type\n";
        std::cout << "1. Audio\n" <<
                  "2. Visual\n" <<
                  "3. AudioMobile\n" <<
                  "4. VisualMobile" << std::endl;
        std::cin >> itemTypeChoice;

        switch (itemTypeChoice) {
            case '1':
                itemType = "Audio";
                break;
            case '2':
                itemType = "Visual";
                break;
            case '3':
                itemType = "AudioMobile";
                break;
            case '4':
                itemType = "VisualMobile";
                break;
            default:
                std::cout << "Your input was invalid. Please try again." << std::endl;
                continue;
        }

        //Allows the user to confirm their choice. Loop continues if entryIsCorrect is assigned 0 (false)
        std::cout << "You entered " + manufacturer + prodName + itemType +
                     ". If this is incorrect enter 0 to try again, or enter any other\n"
                     "letter or word to continue." << std::endl;
        std::cin >> entryIsCorrect;

    } while (entryIsCorrect == "0");

    // itemType is set depending on itemTypeChoice
    if (itemTypeChoice == '1' || itemTypeChoice == '3')
        productSpecs = addMusicPlayer();
    else
        productSpecs = addMoviePlayer();

    //newProduct string is set by concatenating manufacturer prodName itemType
    std::string newProduct = prodName + " " + manufacturer + " " + itemType + ", " + productSpecs;

    //newProduct string is appended to catalog.txt file
    std::ofstream catalogFile;
    catalogFile.open("catalog.txt", std::ios::app);
    catalogFile << newProduct << std::endl;
    catalogFile.close();

    std::cout << newProduct << " has been added to the product catalog.\n" << std::endl;
}

std::string addMusicPlayer() {

    /*
     * Music Players store AudioSpecification (the file format, like wav or mp3)
     * and MediaType (what stores the audio file like CD, DVD, Blu-Ray), both input by the user.
     */
    std::string entryIsCorrect;
    std::string audioSpecs;

    //Loop allows the user to enter 0 if they incorrectly typed the formats, or 1 if it is correct.
    do {
        //Ignores the newline character read when the user presses enter/return before within addNewProduct().
        std::cin.ignore();

        std::cout << "Please enter the supported file format(s) for the music player. If there are multiple supported\n"
                     "formats then separate them with a space. For example, WAV MP3, or WAV FLAC MP3." << std::endl;
        std::getline(std::cin, audioSpecs);

        std::cout << "You entered " + audioSpecs + ". If this is incorrect enter 0 to try again, or enter any other\n"
                                                   "letter or word to continue." << std::endl;
        std::cin >> entryIsCorrect;
    } while (entryIsCorrect == "0");

    std::string mediaType;

    //Loop runs until the user types 1 to confirm that the entry is correct.
    do {
        //Ignores the newline character within the buffer from the previous entry.
        std::cin.ignore();

        std::cout << "Please enter the media type(s) for the music player. For example, Digital, CD, DVD, or Blu-Ray."
                  << std::endl;
        std::getline(std::cin, mediaType);

        std::cout << "You entered " + mediaType + ". If this is incorrect enter 0 to try again, or enter any other\n"
                                                  "letter or word to continue." << std::endl;
        std::cin >> entryIsCorrect;
    } while (entryIsCorrect == "0");

    std::string musicPlayerSpecs = "File format(s): " + audioSpecs + ", " + "Media Type(s): " + mediaType;

    return musicPlayerSpecs;
}

std::string addMoviePlayer() {

    /*
     * Movie Players store MonitorType, which is a Screen.
     * Screen stores: resolution, refresh rate, response time.
     */
    std::string monitorType;
    char screen;
    std::string entryIsCorrect;

    //Loop runs until valid input is entered and the user enters 1 to confirm the correct entry.
    do {
        std::cout << "Please enter the number before the type of screen for this product.\n"
                     "1. LCD \n"
                     "2. LED \n"
                     "3. OLED." << std::endl;
        std::cin >> screen;

        switch (screen) {
            case '1':
                monitorType = "LCD";
                break;
            case '2':
                monitorType = "LED";
                break;
            case '3':
                monitorType = "OLED";
                break;
            default:
                std::cout << "Your input is invalid. Please try again.\n";
                continue;
        }
        //Confirms the user's entry.
        std::cout << "You chose " + monitorType + ". If this is incorrect enter 0 to try again, or enter any other\n"
                                                  "letter or word to continue." << std::endl;
        std::cin >> entryIsCorrect;

    } while (entryIsCorrect == "0");

    //stores the screen's resolution, refresh rate, response time.
    std::string screenSpecs;

    //Loop runs until the user types 1 to confirm that the entry is correct.
    do {
        //Ignores the newline character read when the user presses enter/return previously.
        std::cin.ignore();

        std::cout << "Please enter the screen's resolution, refresh rate, and response time. For example,"
                     " 1080p 144 Hz 1 ms." << std::endl;
        std::getline(std::cin, screenSpecs);

        std::cout << "You entered " + screenSpecs + ". If this is incorrect enter 0 to try again, or enter any other\n"
                                                    "letter or word to continue." << std::endl;
        std::cin >> entryIsCorrect;
    } while (entryIsCorrect == "0");

    std::string moviePlayerSpecs = "Monitor Type: " + monitorType + ", " + "Screen Specifications: " + screenSpecs;

    return moviePlayerSpecs;
}

void displayProductionStatistics() {
    std::cout << "Display Production Statistics Stub\n";
}

void findProductionNumber(std::vector<std::string> serialNumbers) {

    std::ofstream serialNumbersFile("serialnumbers.txt");

    if (!serialNumbersFile.is_open()) {
        std::cout << "No products have been produced. Please choose \"Produce Items\" at the menu to track production\n"
                     "which will generate production numbers and serial numbers." << std::endl;

    } else {

        std::cout << "Please enter the serial number of a product and the program will output the production number.\n";
        std::string inputSerialNum;
        std::cin >> inputSerialNum;

        for (int count = 0; count < serialNumbers.size(); count++) {
            if (serialNumbers[count] == inputSerialNum) {
                std::cout << "The production number for the serial number you entered is " + std::to_string(count + 1);
            }
        }
    }
    serialNumbersFile.close();

}