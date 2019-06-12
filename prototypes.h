/** @file prototypes.h
 *  @brief This file is the header file which defines the function prototypes for the COP2001 Procedural Project.
 *
 * The function prototypes are stored here and are defined within main.cpp.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#ifndef COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
#define COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H

struct Production_Record {
    int production_number;
    std::string product;
    std::string serial_num;
};

struct Product {
    std::string manufacturer;
    std::string prod_name;
    std::string item_type_code;
    std::string product_specs;
    std::string product_info;
};

struct User {
    std::string username;
    std::string salt;
    std::string password;
    std::string access_level;
};

struct Statistics {
    int production_number;
    int audio_serial_num;
    int audio_mobile_serial_num;
    int visual_serial_num;
    int visual_mobile_serial_num;
};

/**
 * @brief This function only allows the user to continue to the program if the username and password matches.
 *
 * If the users vector is empty, then add_employee_account is called, which creates the first user with access level
 * set to "admin". The user is required to authenticate if the vector is not empty, which prompts the user for the
 * username and password. The username contains first syllable of first name and all of last in all lowercase, and
 * the Password must contain at least one uppercase, one lowercase, and one digit with no spaces or special characters.
 *
 * @param users - Reference vector of type User, which holds username, salt, password, and access level.
 */
void authenticate(std::vector<User> &);

/**
 * @brief The function loads existing data into the respective vectors if the files exists.
 *
 * If the corresponding files exist, then the lines from catalog.txt are added to the products vector, and the lines
 * from production.txt are added to the production_records vector. The respective serial numbers are incremented
 * depending on the substr containing the item_type_code.
 *
 * @param products - Reference vector of type Product, which holds manufacturer, product name, item type code, product
 *                  specs, and product_info which concatenates all info together.
 * @param prod_record - Reference vector of type Production_Record, which holds production number, product, and serial
 *                      number.
 * @param stats - Instance of type Statistics, which holds the next production number, and serial numbers for each type.
 * @param users - Reference vector of type User, which holds username, salt, password, and access level.
 *
 * @return void
 */
void load_existing_data(std::vector<Product> &, std::vector<Production_Record> &, Statistics &, std::vector<User> &);

/**
 * @brief This function prompts the user to enter a number to run a corresponding function from the menu printed to the
 *        screen.
 *
 * This function is called within main, which returns either true or false then assigned to the flag bool,
 * program_is_running. The function is called continuously within main until the user enters 6 which returns false and
 * the loop is broken.
 *
 * @param products - Reference vector of type Product, which holds manufacturer, product name, item type code, product
 *                  specs, and product_info which concatenates all info together.
 * @param prod_record - Reference vector of type Production_Record, which holds production number, product, and serial
 *                      number.
 * @param stats - Instance of type Statistics, which holds the next production number, and serial numbers for each type.
 * @param users - Reference vector of type User, which holds username, salt, password, and access level.
 * @return True is returned if the entry is invalid or if a number other than 6 is entered. False is returned if
 *         the user enters 6 which exits the while loop within main and completes the program.
 */
bool prompt_menu_choice(std::vector<Product> &, std::vector<Production_Record> &, Statistics &, std::vector<User> &);

/**
 * @brief Prints the catalog to the console, and prints that the catalog is empty if no products have been added.
 *
 * Uses a for loop to iterate through the products within the catalog if the vector is not empty, and print these
 * elements to the console. It also prints out a number in front of each element to allow the user to choose a product
 * within the function named produce_items.
 *
 * @param products - Reference vector of type Product, which holds manufacturer, product name, item type code, product
 *                  specs, and product_info which concatenates all info together.
 * @return void
 */
void show_catalog(const std::vector<Product> &);


/**
 * @brief Allows the user to track the production of each product within the catalog by writing to the production.txt
 *        file.
 *
 * This function calls the show_catalog function to prompt the user to enter the number corresponding to the product
 * they wish to track. Then. the user is prompted to enter the number of units produced. Each item tracked is added
 * to the production_records vector and written to a file named production.txt.
 *
 * @param products - Reference vector of type Product, which holds manufacturer, product name, item type code, product
 *                  specs, and product_info which concatenates all info together.
 * @param prod_record - Reference vector of type Production_Record, which holds production number, product, and serial
 *                      number.
 * @param stats - Instance of type Statistics, which holds the next production number, and serial numbers for each type.
 * @return void
 */
void produce_items(std::vector<Product> &, std::vector<Production_Record> &, Statistics &);

/**
 * @brief Allows an administrator to add an employee account.
 *
 * This function allows existing users to add an employee account. The passwords are "encrypted" with a cipher using
 * encrypt_string(str), then a unique pseudo-random salt value is prepended. This string is then hashed using SHA256.
 *
 * @param users - Reference vector of type User, which holds username, salt, password, and access level.
 *
 * @return void
 */
void add_employee_account(std::vector<User> &);

/**
 * @brief Encrypts user passwords combined with a pseudo-random long long.
 *
 * This function shifts the ASCII value of each password character and operates on the password string which is
 * prepended with a pseuo-random salt value.
 *
 * @param str - String composed of salt and encrypted password.
 * @return Encrypted ciphertext is returned with prepended randomly generated salt which is then hashed.
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
 * @param products - Reference vector of type Product, which holds manufacturer, product name, item type code, product
 *                  specs, and product_info which concatenates all info together.
 * @return void
 */
void add_new_product(std::vector<Product> &);

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
void display_production_statistics(const Statistics&);

/**
 * @brief User inputs a serial number and the respective production number is output.
 *
 * If the production_records vector is empty then the user is notified. Otherwise, the user is prompted to enter
 * a serial number, which is then compared to the serial number substring of each element of the production_records
 * vector. If the element is found, then the production number is found by adding 1 to the index where it was found.
 * If it is not found, then the user is notified and returned to the menu within run_program.
 *
 * @param prod_record - Reference vector of type Production_Record, which holds production number, product, and serial
 *                      number.
 * @return void
 */
void find_production_number(const std::vector<Production_Record> &);

#endif //COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
