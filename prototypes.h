/** @file prototypes.h
 *  @brief This file is the header file which defines the function prototypes for the COP2001 Procedural Project.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#ifndef COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
#define COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H

#endif //COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H

/**
 * @brief Prints the menu to the console.
 */
void showMenu();

/**
 * @brief Prints the catalog to the console, and prints that the catalog is empty if no products have been added.
 */
void showCatalog(std::vector <std::string>&);

/**
 * @brief Allows the user to track the production of each product within the catalog by writing to the production.txt
 *        file.
 */
void produceItems(std::vector <std::string>&, std::vector<std::string>&, std::vector<std::string>&);

/**
 * @brief Allows an administrator to add an employee account.
 */
void addEmployeeAccount();

/**
 * @brief Allows the user to add a new product to the catalog by writing to the catalog.txt file.
 */
void addNewProduct(std::vector <std::string>&);

/**
 * @brief This function adds a music player to the catalog.
 * @return Sends the Music Player specifications to the addNewProduct function to be added to productInfo.
 */
std::string addMusicPlayer();

/**
 * @brief This function adds a movie player to the catalog.
 * @return Sends the Movie Player specifications to the addNewProduct function to be added to productInfo.
 */

std::string addMoviePlayer();

/**
 * @brief Displays productions statistics to the user.
 */
void displayProductionStatistics();

/**
 * @brief User inputs a serial number and the respective production number is output.
 */
void findProductionNumber(std::vector<std::string> serialNumbers);