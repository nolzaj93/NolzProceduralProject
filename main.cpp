#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @author - Austin Nolz, Procedural Project for COP 2001
 * @return - 0 means everything ran fine
 */



void showMenu();
void produceItems();
void addEmployeeAccount();
void addMusicPlayer();
void addMoviePlayer();
void displayProductionStatistics();

int main() {
    std::cout << "Welcome to the Production Line Tracker!\n\n";

    int inputNumber = 0;
    bool programIsRunning=true;

    while(programIsRunning) {

        std::cout << "Type in a number between 1 and 6 to run the respective function.\n\n";


        showMenu();

        std::cin >> inputNumber;

        switch (inputNumber) {
            case 1: produceItems();
                break;
            case 2: addEmployeeAccount();
                break;
            case 3: addMusicPlayer();
                break;
            case 4: addMoviePlayer();
                break;
            case 5: displayProductionStatistics();
                break;
            case 6: programIsRunning = false;
                break;
            default: std::cout << "Not a valid selection\n";
                break;
        }
    }
    return 0;

}

void showMenu() {


    std::cout << "1. Produce Items\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add Music Player\n";
    std::cout << "4. Add Movie Player\n";
    std::cout << "5. Display Production Statistics\n";
    std::cout << "6. Exit\n";
}

void produceItems() {
    int prodNum = 1;
    int audioSerialNum = 1;
    int audioMobileSerialNum = 1;
    int visualSerialNum = 1;
    int visualMobileSerialNum = 1;

    std::cout << "Produce Items Stub\n";

    // Eventually the user will be able to choose the item to produce.
    // For now, just have them input the information.
    cout << "Enter the Manufacturer\n";
    string manufacturer;
    cin >> manufacturer;

    cout << "Enter the Product Name\n";
    string prodName;
    cin >> prodName;

    cout << "Enter the item type\n";
    cout << "1. Audio\n" <<
         "2. Visual\n" <<
         "3. AudioMobile\n" <<
         "4. VisualMobile\n";
    int itemTypeChoice;
    cin >> itemTypeChoice;
    string itemTypeCode;

    // write code to set the item type code based on the selected item type
    // Audio "MM", Visual "VI", AudioMobile "AM", or VisualMobile "VM".
    switch(itemTypeChoice) {
        case 1: itemTypeCode = "MM";
            break;
        case 2: itemTypeCode = "VI";
            break;
        case 3: itemTypeCode = "AM";
            break;
        case 4: itemTypeCode = "VM";
            break;
        default:
            break;
    }

    cout << "Enter the number of items that were produced\n";
    int numProduced;
    cin >> numProduced;

    // add a loop to record production, for now simply by
    // outputting production number and serial number
    for(int counter = 0; counter < numProduced; counter++) {
        cout << "Production Number: " + std::to_string(counter+1)
                + " Serial Number: " + manufacturer.substr(0,3) + itemTypeCode;
        cout << setfill('0') << setw(5) << std::to_string(counter+1)<< endl;
    }
}

void addEmployeeAccount() {
    std::cout << "Add Employee Account Stub\n";
}

void addMusicPlayer() {
    std::cout << "Add Music Player Stub\n";
}

void addMoviePlayer() {
    std::cout << "Add Movie Player Stub\n";
}

void displayProductionStatistics() {
    std::cout << "Display Production Statistics Stub\n";
}
