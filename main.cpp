#include <iostream>

using namespace std;

/**
 * @author - Austin Nolz, Procedural Project for COP 2001
 * @return - 0 means everything ran fine
 */



void printMenu();
void produceItems();
void addEmployeeAccount();
void addMusicPlayer();
void addMoviePlayer();
void displayProductionStatistics();

int main() {
    std::cout << "Production Line Tracker\n\n";

    int inputNumber = 0;
    bool programIsRunning=true;

    while(programIsRunning) {

        printMenu();

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

void printMenu() {
    std::cout << "1. Produce Items\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add Music Player\n";
    std::cout << "4. Add Movie Player\n";
    std::cout << "5. Display Production Statistics\n";
    std::cout << "6. Exit\n";
}

void produceItems() {
    std::cout << "Produce Items Stub\n";
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
