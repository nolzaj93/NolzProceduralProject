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
void showCatalog();

/**
 * @brief Allows the user to track the production of each product within the catalog by writing to the production.txt
 *        file.
 */
void produceItems();

/**
 * @brief Allows an administrator to add an employee account.
 */
void addEmployeeAccount();

/**
 * @brief Allows the user to add a new product to the catalog by writing to the catalog.txt file.
 */
void addNewProduct();

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
 * @brief Takes the reference variable as 1st argument, variable name as 2nd argument, and confirms the user's input.
 * @param 1st parameter is named variable, which is a reference variable to the corresponding required input
 * @param 2nd parameter is named varName, which is a string literal referring to the variable's name.
 */
void returnConfirmedInput(std::string &, const std::string);