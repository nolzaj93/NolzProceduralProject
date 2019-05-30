/** @file prototypes.h
 *  @brief This file is the header file which defines the function prototypes for the COP2001 Procedural Project.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#ifndef COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
#define COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H

/**
 * @brief Prints the menu to the console and allows the user to enter a number which will run a respective function.
 *
 * The products and production_records vectors are initialized here. If catalog.txt already exists then all products
 * are added to the products vector, then if production.txt exists then all of the production records are added to
 * the production_records vector. A welcome message is printed and then a while loop runs, which prints the menu
 * and prompts the user to enter the number next to the respective function they wish to call. Exception handling
 * is used to ensure that a valid integer is entered.
 *
 * @return void
 */
void run_program();

/**
 * @brief Prints the catalog to the console, and prints that the catalog is empty if no products have been added.
 *
 * Uses a for loop to iterate through the products within the catalog if the vector is not empty, and print these
 * elements to the console. It also prints out a number in front of each element to allow the user to choose a product
 * within the function named produce_items.
 *
 * @param products - Vector which holds the products in the catalog.
 * @return void
 */
void show_catalog(std::vector<std::string>);

/**
 * @brief Allows the user to track the production of each product within the catalog by writing to the production.txt
 *        file.
 *
 * This function calls the show_catalog function to prompt the user to enter the number corresponding to the product
 * they wish to track. Then. the user is prompted to enter the number of units produced. Each item tracked is added
 * to the production_records vector and written to a file named production.txt.
 *
 * @param products - Reference vector which holds the products in the catalog.
 * @param production_records - Reference vector of strings which tracks a record of all units produced on the
 * production line.
 * @return void
 */
void produce_items(std::vector<std::string> &, std::vector<std::string> &);

/**
 * @brief Allows an administrator to add an employee account.
 *
 * This function will eventually allow certain users to add an employee account.
 *
 * @return void
 */
void add_employee_account();

/**
 * @brief Allows the user to add a new product to the catalog by writing to the catalog.txt file.
 *
 * This function allows the user to add a new product to the catalog. The user is prompted to enter the manufacturer,
 * product name, item type, and depending on item type either addMusicPlayer or addMoviePlayer is called to add
 * product specifications. If the user confirms the information they entered is correct, then the new product is
 * added to the products vector and written to catalog.txt.
 *
 * @param products - Reference vector which holds products in the catalog.
 * @return void
 */
void add_new_product(std::vector<std::string> &);

/**
 * @brief This function adds a music player to the catalog.
 *
 * This function is called from the add_new_product function and returns the specifications of that product. The
 * user is first prompted to enter the supported file formats and then is prompted to enter the media type.
 *
 * @return Sends the Music Player specifications to the add_new_product function to be added to productInfo.
 */
std::string add_music_player();

/**
 * @brief This function adds a movie player to the catalog.
 *
 * This function is called from the add_new_product function and returns the specifications of that product. The
 * user is prompted to enter the monitor type, then prompted to enter the screen's specifications. These two inputs
 * are concatenated and returned to the add_new_product function.
 *
 * @return Sends the Movie Player specifications to the addNewProduct function to be added to productInfo.
 */

std::string add_movie_player();

/**
 * @brief Displays productions statistics to the user.
 *
 * This function will eventually print production statistics to the user, like total number of units tracked, as well
 * as number of units tracked for each item type.
 *
 * @return void
 */
void display_production_statistics();

/**
 * @brief User inputs a serial number and the respective production number is output.
 *
 * If the production_records vector is empty then the user is notified. Otherwise, the user is prompted to enter
 * a serial number, which is then compared to the serial number substring of each element of the production_records
 * vector. If the element is found, then the production number is found by adding 1 to the index where it was found.
 * If it is not found, then the user is notified and returned to the menu within run_program.
 *
 * @param production_records - Vector which holds the production records of all units that have been tracked.
 * @return void
 */
void find_production_number(std::vector<std::string>);

#endif //COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
