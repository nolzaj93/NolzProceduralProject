/** @file prototypes.h
 *  @brief This file is the header file which defines the function prototypes for the COP2001 Procedural Project.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#ifndef COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
#define COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H

/**
 * @brief
 *
 * @param usernames
 * @param salts
 * @param user_passwords
 */
void authenticate(std::vector<std::string> &usernames, std::vector<std::string> &salts,
                  std::vector<std::string> &user_passwords);

/**
 * @brief The function loads existing data into the respective vectors if the files exists.
 *
 * If the corresponding files exist, then the lines from catalog.txt are added to the products vector, and the lines
 * from production.txt are added to the production_records vector.
 *
 * @param products - Reference vector which holds the products in the catalog.
 * @param production_records - Reference vector of strings which tracks a record of all units produced on the
 *                             production line.
 * @param usernames - Vector to hold usernames.
 * @param user_passwords - Vector to hold user_passwords.
 * @param audio_serial_num - This integer holds the next serial number for the audio (MM) product type.
 * @param audio_mobile_serial_num - This int holds the next serial number for the audio-mobile (AM) product type.
 * @param visual_serial_num - This int holds the next serial number for the visual (VI) product type.
 * @param visual_mobile_serial_num - This int holds the next serial number for the visual-mobile (VM) product type.
 * @return void
 */
void load_existing_data(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
                        std::vector<std::string> &, std::vector<std::string> &, int &, int &, int &, int &);

/**
 * @brief This function prompts the user to enter a number to run a corresponding function from the menu printed to the
 *        screen.
 *
 * This function is called within main, which returns either true or false then assigned to the flag bool,
 * program_is_running. The function is called continuously within main until the user enters 6 which returns false and
 * the loop is broken.
 *
 * @param products - Reference vector which holds the products in the catalog.
 * @param production_records - Reference vector of strings which tracks a record of all units produced on the
 *                             production line.
 * @param usernames - Vector to hold usernames.
 * @param salts - Vector to hold salts.
 * @param user_passwords - Vector to hold user_passwords.
 * @param audio_serial_num - This integer holds the next serial number for the audio (MM) product type.
 * @param audio_mobile_serial_num - This int holds the next serial number for the audio-mobile (AM) product type.
 * @param visual_serial_num - This int holds the next serial number for the visual (VI) product type.
 * @param visual_mobile_serial_num - This int holds the next serial number for the visual-mobile (VM) product type.
 * @return True is returned if the entry is invalid or if a number other than 6 is entered. False is returned if
 *         the user enters 6 which exits the while loop within main and completes the program.
 */
bool prompt_menu_choice(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &,
                        std::vector<std::string> &, std::vector<std::string> &, int &, int &, int &, int &);

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
 * @param audio_serial_num - This integer holds the next serial number for the audio (MM) product type.
 * @param audio_mobile_serial_num - This int holds the next serial number for the audio-mobile (AM) product type.
 * @param visual_serial_num - This int holds the next serial number for the visual (VI) product type.
 * @param visual_mobile_serial_num - This int holds the next serial number for the visual-mobile (VM) product type.
 * @return void
 */
void produce_items(std::vector<std::string> &, std::vector<std::string> &, int &, int &, int &, int &);

/**
 * @brief Allows an administrator to add an employee account.
 *
 * This function will eventually allow certain users to add an employee account.
 * @param usernames - Vector to hold usernames.
 * @param user_passwords - Vector to hold user_passwords.
 *
 * @return void
 */
void add_employee_account(std::vector<std::string> &, std::vector<std::string> &, std::vector<std::string> &);

/**
 *
 * @param str
 * @return
 */
std::string encrypt_string(std::string str);

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
