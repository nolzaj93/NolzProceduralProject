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

/**
 * @brief This type describes a single record within the ProductionLog/prod_record vector.
 *
 * A vector of this type is declared in main and passed by reference to load_existing_data(), where the vector reads
 * ProductionLog.csv if it exists. It is passed by reference to prompt_menu_choice(), then sent by reference to
 * produce_items() or passed by constant reference to find_production_number().
 *
 * @var production_number - The total number of units tracked by the factory, and equivalent to production number in
 *                          Statistics.
 * @var product - String containing all details and specifications about the product.
 * @var serial_num - String containing first three letters of the manufacturer name, item type code, and 5 digit
 *                   item specific serial count.
 */
struct Production_Record {
    int production_number;
    std::string product;
    std::string serial_num;
};

/**
 * @brief Product is the type of each element in the vector named products, which is a collection holding the catalog
 * saved to ProductLine.csv.
 *
 * A vector of this type named products is declared in main and passed first by reference to load_existing_data to
 * read and append each product of the product line to the vector. The vector is passed to prompt_menu_choice,
 * then to either produce_items() as a constant reference and to show_catalog(), or to add_new_product() by reference.
 *
 * @var manufacturer - String holding the manufacturer of the product.
 * @var prod_name - String with name of the product.
 * @var item_type_code - Two letter string designating item type - (MM AM VI VM)
 * @var product_specs - String containing any product specifications.
 * @var product_info - A concatenated string to be used in the production records.
 *
 */
struct Product {
    std::string manufacturer;
    std::string prod_name;
    std::string item_type_code;
    std::string product_specs;
    std::string product_info;
};

/**
 * @brief A struct which is instantiated for each new employee added, and the instance is then added to the users
 * vector in main.
 *
 * A vector of this type is declared in main named users and passed first to load_existing_data(). Users.txt is read
 * and each instance of a User is initialized and added to the users vector. If no users have been created, then
 * we can't call authenticate() because users is empty. We then call add_employee_account to add the administrator
 * credentials.
 *
 * @var username - All lowercase, first letter of first name concatenated with last name. If there are duplicate user
 *                 is prompted to add a number to the end of their name.
 * @var salt - A pseduo-randomly generated big number prepended to the password before encryption.
 * @var password - The hashed result of the string (salt + password)
 * @var access_level - First user to run the program has admin level, and all others are employee level.
 *
 */
struct User {
    std::string username;
    std::string salt;
    std::string password;
    std::string access_level;
};

/**
 * @brief Statistics is instantiated once to hold the production and serial number counts to add to the
 * production record.
 *
 * The only instance is initialized in main to the starting values, then passed by reference to load_existing_data().
 * The ProductionLog.csv file is read line by line and the item type code substring is compared to each item type code.
 * The respective serial num is incremented for each production record, and the production number is set to the
 * prod_record vector size + 1. The instance stats is passed by reference to prompt_menu_choice() where it is again
 * passed by reference to produce_items(), and by constant reference to display_production_statistics().
 *
 * @var production_number - The production number count is the overall unit production number including all item types
 *                            which is prepended to the record.
 * @var audio_serial_num - The audio type serial count is appended to the audio (MM) type production records.
 * @var audio_mobile_serial_num - The audio mobile type serial count is appended to the audio mobile (AM) type
 *                                  production records.
 * @var visual_serial_num - The visual type serial count is appended to the visual(VI) type production records.
 * @var visual_mobile_serial_num - The visual mobile type serial count is appended to the visual mobile (VM)
 *                                 type production records.
 */
struct Statistics {
    int production_number;
    int audio_serial_num;
    int audio_mobile_serial_num;
    int visual_serial_num;
    int visual_mobile_serial_num;
};

/**
 * @brief This function only allows the user to continue to the program if the username and password matches with is
 * stored in the users vector.
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
void show_catalog(std::vector<Product> &);


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
 * @param stats - Instance of struct named statistics holding counts for production and serial numbers.
 * @param products - Vector of type Product holding the details of each product in the product line.
 * @param prod_record - Vector of type Production_Record which holds a record of each unit produced in the factory.
 * @return void
 */
void display_production_statistics(const Statistics &, std::vector<Product> &,
                                   const std::vector<Production_Record> &);

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

/**
 * @brief Sorts the products within the product line alphabetically by comparing the manufacturer strings.
 *
 * This function uses a selection sort to put the products vector in ascending order (A - z). This function is called
 * after a new product is added.
 *
 * @param products - A vector of type Product which holds the product line information.
 * @return void
 */
void selection_sort(std::vector<Product> &);

#endif //COP2001PROCEDURALPROJECT_MAINPROTOTYPES_H
