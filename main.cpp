/** @file main.cpp
 *  @brief This file is C++ source code for the COP2001 Procedural Project.
 *
 * The Production Line Tracker requires a valid username and password to enter the program. The user is
 * given the option at the menu to add a new product to the production line, add employe
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>
#include <random>
#include <algorithm>
#include <cstring>
#include "sha256.h"
#include "prototypes.h"


/**
* @brief This is the main function which is the starting point of the program. It prints the menu to the console and
*        allows the user to enter a number which will run a respective function.
*
* The products and production_records vectors are initialized here. If catalog.txt already exists then all products
* are added to the products vector, then if production.txt exists then all of the production records are added to
* the production_records vector. The function prompt_menu_choice is called and a welcome message is printed, then
* a while loop runs, which prints the menu and prompts the user to enter the number next to the respective function
* they wish to call. Exception handling is used to ensure that a valid integer is entered.
*
* @return - If the program runs to completion then this function returns zero.
*/
int main() {

    //Declare vectors of records, products and users. Initialize stats to starting values.
    std::vector<Production_Record> prod_record;
    std::vector<Product> products;
    std::vector<User> users;
    Statistics stats{1, 0, 0, 0, 0};

    //Loads existing products and production records if the respective text files exist, user info, and serial numbers.
    load_existing_data(products, prod_record, stats, users);

    //Welcome message printed to the console.
    std::cout << "Welcome to the Production Line Tracker!\n";

    //If users is not empty, then authenticate is called to confirm employee ID. Otherwise, administrator registers
    // a master account.
    if (!users.empty())
        authenticate(users);
    else {
        std::cout << "Administrator registration\n";
        add_employee_account(users);
    }

    //Declare and initialize program_is_running as a flag bool for the while loop.
    bool program_is_running = true;

    //While loop that is repeated until the user enters 6 to exit which sets program_is_running to false.
    while (program_is_running) {

        //The loop calls prompt_menu_choice until the function returns false, which only occurs when the user enters 6.
        program_is_running = prompt_menu_choice(
                products, prod_record,
                stats, users);
    }
    return 0;
}

void authenticate(std::vector<User> &users) {

    bool user_is_valid = false;
    int user_index = -1;

    do {
        while (!user_is_valid) {
            //Prompts for username and stores in input_username.
            std::cout << "\nPlease enter your username. It is the first letter of your first name\n"
                         "followed by your last name in all lowercase." << std::endl;
            std::string input_username;
            std::cin >> input_username;

            //Iterates through the usernames vector and checks if the input is the same as an element and sets
            // user_index to the index where the input matches.
            for (int index = 0; index < users.size(); index++) {
                if (users[index].username == input_username) {
                    user_is_valid = true;
                    user_index = index;
                    break;
                }
            }
            //If the match for input_username is not found, then the user is notified and the loop continues to the
            //next iteration.
            if (!user_is_valid) {
                std::cout << "The username you entered does not exist in the system. Please try again\n"
                             "or add an employee account." << std::endl;
                continue;
            }
        }

        //Prompts for password and stores in input_password.
        std::cout << "Please enter your password." << std::endl;
        std::string input_password;
        std::cin >> input_password;

        //Prepends the user's randomly generated salt, encrypts the string with a Caesar cipher, and is sent through
        // the hash function.
        input_password = sha256(encrypt_string(users[user_index].salt + input_password));

        //If the string stored in input_password is equal to the stored hashed password, then user_is_valid is set to
        // true, and the user continues to the program.
        if (users[user_index].password == input_password) {

            std::cout << "Welcome back, " + users[user_index].username + "!" << std::endl;
            user_is_valid = true;

        } else {
            //If the hashed input_password does not match, then the loop continues because user_is_valid is set to false
            std::cout << "The password did not match to the username you entered." << std::endl;
            user_is_valid = false;
        }

    } while (!user_is_valid);
}

void load_existing_data(std::vector<Product> &products, std::vector<Production_Record> &prod_record, Statistics &stats,
                        std::vector<User> &users) {

    //Existing products are added to vector named products from catalog.txt if the file exists already
    std::string next_line;
    std::ifstream current_catalog_file("ProductLine.csv");
    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (current_catalog_file.is_open()) {

        std::stringstream s_str;
        std::string specs_and_type;

        //Adds each line to the products catalog vector.
        while (getline(current_catalog_file, next_line)) {
            Product next_product;
            s_str << next_line << std::endl;
            next_product.product_info = next_line;
            s_str >> next_product.manufacturer;
            s_str >> next_product.prod_name;

            getline(s_str, specs_and_type);
            next_product.product_specs = specs_and_type.substr(0, specs_and_type.size() - 2);
            next_product.item_type_code = specs_and_type.substr(specs_and_type.size() - 2, 2);

            products.emplace_back(next_product);
        }
    }
    current_catalog_file.close();


    std::ifstream production_file("ProductionLog.csv");

    //If ProductionLog.csv exists then these records are added line by line to the prod_records vector.
    if (production_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(production_file, next_line)) {
            Production_Record record;
            std::stringstream s_str;

            //Sends the line to the string stream
            s_str << next_line << std::endl;
            //Sends the first string from string stream to record.production_number,
            // ex. 194 Apple iPod MP3 Digital AM AppAM00088, 194 is placed into record.production_number
            s_str >> record.production_number;
            int prod_num_length = std::to_string(record.production_number).length();

            //The rest of the string stream contains the product info and serial num which we separate and assign.
            std::string product_and_serial_num = s_str.str();
            record.product = product_and_serial_num.substr(prod_num_length + 1,
                                                           product_and_serial_num.size() - 13 - prod_num_length);
            record.serial_num = product_and_serial_num.substr(product_and_serial_num.size() - 11, 10);

            //Increments the respective serial_num depending on the item type code found within each record.
            if (next_line.substr(next_line.length() - 7, 2) == "MM")
                stats.audio_serial_num += 1;
            else if (next_line.substr(next_line.length() - 7, 2) == "AM")
                stats.audio_mobile_serial_num += 1;
            else if (next_line.substr(next_line.length() - 7, 2) == "VI")
                stats.visual_serial_num += 1;
            else if (next_line.substr(next_line.length() - 7, 2) == "VM")
                stats.visual_mobile_serial_num += 1;

            //Adds the record to the prod_record vector.
            prod_record.emplace_back(record);
        }
    }
    //We assign stats.production_number which is the updated production counter equal to number of production records
    // + 1 to prepare for the next unit tracked.
    stats.production_number = prod_record.size() + 1;
    production_file.close();

    //Instance of User struct is used to load the vector of type User, named users.
    User next_user;
    std::ifstream user_info_file("Users.txt");
    std::stringstream s_str;

    //If Users.txt exists then these records are added line by line to the users vector.
    if (user_info_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(user_info_file, next_line)) {
            s_str << next_line << std::endl;
            s_str >> next_user.username;
            s_str >> next_user.salt;
            s_str >> next_user.password;
            s_str >> next_user.access_level;
            users.emplace_back(next_user);
        }
    }
    user_info_file.close();
}

bool prompt_menu_choice(
        std::vector<Product> &products,
        std::vector<Production_Record> &prod_record, Statistics &stats, std::vector<User> &users) {

    //Declare and initialize input_number which is used to hold number input by user.
    std::string input_text;
    int input_number = 0;

    //Prompts the user to enter a number between 1 and
    std::cout << "\n" << "Type in a number between 1 and 6 to run the respective function and press enter.\n"
              << std::endl;

    //prints the menu to the console
    std::cout << "1. Produce Items\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add New Product\n";
    std::cout << "4. Display Production Statistics\n";
    std::cout << "5. Find Production Number." << std::endl;
    std::cout << "6. Exit" << std::endl;

    std::cin >> input_text;

    try {
        input_number = std::stoi(input_text);
    } catch (std::invalid_argument const &e) {
        std::cout << "You entered text or a number with a decimal. Please enter a number." << std::endl;
        return true;
    }

    //Switch statement calls the corresponding function, or if the the user enters 6 the loop is broken.
    switch (input_number) {
        case 1:
            produce_items(products, prod_record, stats);
            break;
        case 2:
            std::cin.ignore();
            add_employee_account(users);
            break;
        case 3:
            add_new_product(products);
            break;
        case 4:
            display_production_statistics(stats, products, prod_record);
            break;
        case 5:
            find_production_number(prod_record);
            break;
        case 6:
            return false;
        default:
            std::cout << "Your input was invalid. Please try again." << std::endl;
            break;
    }
    return true;
}

void show_catalog(std::vector<Product> &products) {

    //If ProductionLine.csv has been read and products has been loaded the catalog will be printed, otherwise
    // it is printed that the catalog is empty.
    if (!products.empty()) {

        std::cout << '\n' << "Current catalog: " << std::endl;

        for (int counter = 0; counter < products.size(); counter++) {

            std::cout << std::to_string(counter + 1) + ". " << products[counter].product_info << std::endl;
        }

    } else std::cout << "The product catalog is empty." << std::endl;
}

void produce_items(std::vector<Product> &products, std::vector<Production_Record> &prod_record,
                   Statistics &stats) {

    //If the products vector is empty, then the user is sent back to the menu to add a new product.
    if (products.empty()) {
        std::cout << "The product catalog is empty. Please add a product to track production." << std::endl;
        return;
    }

    //Ignores the newline character read when the user presses enter/return.
    std::cin.ignore();

    std::string entry_is_correct = "0";
    std::string product_choice;
    int choice_number = 0;
    int num_produced = 0;
    Product chosen_product;

    //Iterates at least once, and the loop will repeat if the user enters zero when prompted to confirm the input
    // or if the user does not enter a number 1 to products.size().
    do {
        show_catalog(products);

        std::cout << "\n" << "Please enter the number next to the product you are tracking." << std::endl;
        std::getline(std::cin, product_choice);

        try {
            //Attempts to convert product_choice from string to int and store in choice_number
            choice_number = std::stoi(product_choice);

            //If choice_number is not within the correct range a general exception is thrown.
            if (choice_number < 1 || choice_number > products.size())
                throw std::exception();

        } catch (std::invalid_argument const &e) {
            std::cout << "You entered a string or a number with a decimal. Please enter a number." << std::endl;
            continue;

        } catch (std::exception &ex) {
            std::cout << "You entered a number that does not match with a product. Please enter a number.\n"
                         "between 1 and " + std::to_string(products.size()) + "." << std::endl;
            continue;
        }
        //Sets the chosen product to the values of the respective product in the ProductLine (products).
        chosen_product = products[(choice_number - 1)];

        std::cout << "Please enter the number of items that were produced." << std::endl;
        std::cin >> num_produced;

        //Allows the user to confirm their choice. Loop continues if entry_is_correct is assigned 0 (false)
        std::cout << "You chose " + chosen_product.product_info + " and recorded that " +
                     std::to_string(num_produced) + " units were produced.\n"
                     + "If this is incorrect enter 0 to try again, or enter anything else \n"
                     + "to continue." << std::endl;
        std::cin >> entry_is_correct;

    } while (entry_is_correct == "0");

    // Declares production_file_write object and opens ProductionLog.csv. New text is appended.
    std::ofstream production_file_write;
    production_file_write.open("ProductionLog.csv", std::ios::app);

    //For loop prints product Info for each product
    for (int counter = 0; counter < num_produced; counter++) {
        /*
         * Declares a new record and sets the product to the chosen product's entire product info,
         * sets the production number or overall unit number produced, and sets the
         * 10 digit serial number based on the item type, (ex. AppAM00100).
         */

        Production_Record new_record;
        new_record.product = chosen_product.product_info;
        new_record.production_number = stats.production_number;

        std::ostringstream serial_num;
        serial_num << new_record.product.substr(0, 3) << chosen_product.item_type_code;

        if (chosen_product.item_type_code == "MM")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(stats.audio_serial_num++);
        else if (chosen_product.item_type_code == "AM")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(stats.audio_mobile_serial_num++);
        else if (chosen_product.item_type_code == "VI")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(stats.visual_serial_num++);
        else if (chosen_product.item_type_code == "VM")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(stats.visual_mobile_serial_num++);

        new_record.serial_num = serial_num.str();

        //Outputs a string from the product_info object on each iteration, and writes it to production.txt
        prod_record.emplace_back(new_record);
        production_file_write << stats.production_number++ << " " << new_record.product
                              << " " + new_record.serial_num << std::endl;
    }
    production_file_write.close();
    std::cout << "Production record has been saved to file." << std::endl;
}

void add_employee_account(std::vector<User> &users) {

    //Username is constructed from first letter of first name concatenated with last name in all lowercase.
    // If there is a duplicate username, then username_valid is set to false, and they are prompted to add
    // a number to their last name.
    std::string first_name;
    std::string last_name;

    //Used to test whether the user entered a valid username, if the input contains a digit, a space, or
    // any special characters.
    bool first_name_valid;
    bool last_name_valid;
    bool is_digit;
    bool is_space;
    bool is_not_alpha;

    do {
        first_name_valid = false;
        is_digit = false;
        is_space = false;
        is_not_alpha = false;

        try {
            std::cout << "\nPlease enter your first name. For example, John\n";
            std::getline(std::cin, first_name);

            //Iterates through each character of first_name checking if the character is a digit, space, or special ch.
            for (char next_char : first_name) {
                if (!is_digit && isdigit(next_char))
                    is_digit = true;
                else if (!is_space && isspace(next_char))
                    is_space = true;
                else if (!is_not_alpha && !isalnum(next_char))
                    is_not_alpha = true;
            }

            //Exception is thrown if any of these are true.
            if (is_digit || is_space || is_not_alpha)
                throw std::exception();
            else
                first_name_valid = true;

        } catch (std::exception &ex) {
            //User is prompted with each
            if (is_digit)
                std::cout << "\nYou accidentally typed a number in your first name.\n";
            if (is_space)
                std::cout << "\nYour first name cannot contain a space.\n";
            if (is_not_alpha)
                std::cout << "\nYour first name cannot contain a special character.\n";
            continue;
        }

        do {
            //Last name is not checked for digits so that users with duplicate usernames can use digits.
            //It is
            last_name_valid = false;
            is_space = false;
            is_not_alpha = false;
            try {

                std::cout << "\nPlease enter your last name. For example, Smith\n";
                std::getline(std::cin, last_name);

                //Iterates through each character of first_name checking if the character is a digit, space, or special ch.
                for (char next_char : last_name) {
                    if (!is_space && isspace(next_char))
                        is_space = true;
                    else if (!is_not_alpha && !isalnum(next_char))
                        is_not_alpha = true;
                }

                if (is_space || is_not_alpha)
                    throw std::exception();
                else
                    last_name_valid = true;

            } catch (std::exception &ex) {
                if (is_space)
                    std::cout << "\nYour last name cannot contain a space.\n";
                if (is_not_alpha)
                    std::cout << "\nYour last name cannot contain a special character.\n";
                continue;
            }
        } while (!last_name_valid);

    } while (!first_name_valid);

    // Takes first letter of first_name and changes to lowercase.
    char first_letter = tolower(first_name[0]);

    // Changes last_name to all lowercase.
    std::transform(last_name.begin(), last_name.end(), last_name.begin(), tolower);
    std::stringstream s_str;
    s_str << first_letter << last_name;
    std::string new_username = s_str.str();

    User new_user;
    for (const User &next_user : users) {
        if (next_user.username == new_username) {
            std::cout << "The username " << s_str.str() << " is already in use. Please try again by \n"
                                                           "adding a number to your last name."
                      << std::endl;
            add_employee_account(users);
            return;
        }
    }

    new_user.username = new_username;
    std::cout << "User name: " + new_user.username << std::endl;

    bool password_is_incorrect;
    bool upper_is_found;
    bool lower_is_found;
    bool digit_is_found;
    bool space_is_found;
    bool special_is_found;
    std::string pw_str;

    do {
        password_is_incorrect = true;
        upper_is_found = false;
        lower_is_found = false;
        digit_is_found = false;
        space_is_found = false;
        special_is_found = false;

        std::cout << "\nPlease enter a password between 8 and 20 characters long and at least one\n"
                     "digit, one lowercase letter, and one uppercase letter." << std::endl;
        std::getline(std::cin, pw_str);
        char password[pw_str.length()];

        strcpy(password, pw_str.c_str());

        if (strlen(password) < 8 || strlen(password) > 20) {
            std::cout << "The password length is not between 8 and 20 characters." << std::endl;
            continue;
        }

        //Checks character array for a digit, uppercase and lowercase letters.
        for (char next_char : password) {
            if (!space_is_found && isspace(next_char))
                space_is_found = true;
            else if (!special_is_found && !isalnum(next_char))
                special_is_found = true;
            else if (!digit_is_found && isdigit(next_char))
                digit_is_found = true;
            else if (!lower_is_found && islower(next_char))
                lower_is_found = true;
            else if (!upper_is_found && isupper(next_char))
                upper_is_found = true;
        }

        //Breaks the loop if it has an uppercase, lowercase, digit, no spaces, and no special characters.
        if (upper_is_found && lower_is_found && digit_is_found && !space_is_found && !special_is_found) {
            std::cout << "Your password has been saved." << std::endl;
            break;
        }
        std::cout
                << ((space_is_found || special_is_found) ? "The password cannot contain spaces or special characters.\n"
                                                         : "");
        std::cout << (!digit_is_found ? "The password did not contain a digit.\n" : "");
        std::cout << (!upper_is_found ? "The password did not contain an uppercase letter.\n" : "");
        std::cout << (!lower_is_found ? "The password did not contain a lowercase letter.\n" : "");

        std::cin.ignore();

    } while (password_is_incorrect);

    //Generates pseudo-random salt.
    std::random_device rd;
    srand(rd());
    new_user.salt = std::to_string((ULLONG_MAX / rd()));

    //Prepends salt to pw_str, encrypts, then runs through hash function.
    pw_str = encrypt_string(new_user.salt + pw_str);
    pw_str = sha256(pw_str);
    new_user.password = pw_str;
    pw_str = " ";

    //Sets access level depending if the user is the first to use the software. Will work on function to change
    // employee access level.
    if (users.empty())
        new_user.access_level = "admin";
    else
        new_user.access_level = "employee";

    // Declares userinfo_file object and opens userinfo.txt. New text is appended.
    std::ofstream userinfo_file;
    userinfo_file.open("Users.txt", std::ios::app);

    //Writes to users.txt the contents of new_user separated by spaces.
    userinfo_file << new_user.username << " " << new_user.salt << " " << new_user.password << " "
                  << new_user.access_level << std::endl;

    userinfo_file.close();
    users.emplace_back(new_user);
}

std::string encrypt_string(std::string str) {
    if (str.length() == 1) {
        return str;
    } else {
        //Recursively call through the string adding to the ASCII value of each element.
        return char((int) str[0] + 7) + encrypt_string(str.substr(1, str.length() - 1));
    }
}

void add_new_product(std::vector<Product> &products) {

    //prints the current catalog or let's the user know if it is empty.
    show_catalog(products);

    std::string entry_is_correct;
    int item_type_choice = 0;
    std::string item_type_code;
    std::string item_type;
    Product new_product;

    do {
        //Ignores the newline character read when the user presses enter/return.
        std::cin.ignore();

        std::cout << "\n" << "Please enter the manufacturer." << std::endl;
        std::getline(std::cin, new_product.manufacturer);

        std::cout << "Please enter the product name." << std::endl;
        std::getline(std::cin, new_product.prod_name);

        std::cout << "Please enter the number next to the product's item type\n";
        std::cout << "1. Audio (MM)\n" <<
                  "2. Visual (VI)\n" <<
                  "3. AudioMobile (AM)\n" <<
                  "4. VisualMobile (VM)" << std::endl;

        std::cin >> item_type_code;

        try {
            item_type_choice = std::stoi(item_type_code);

        } catch (std::invalid_argument const &e) {
            std::cout << "You entered a string or a number with a decimal." << std::endl;
            entry_is_correct = "0";
            continue;
        }

        switch (item_type_choice) {
            case 1:
                item_type = "Audio";
                item_type_code = "MM";
                break;
            case 2:
                item_type = "Visual";
                item_type_code = "VI";
                break;
            case 3:
                item_type = "AudioMobile";
                item_type_code = "AM";
                break;
            case 4:
                item_type = "VisualMobile";
                item_type_code = "VM";
                break;
            default:
                std::cout << "Your input was invalid. Please try again." << std::endl;
                continue;
        }
        new_product.item_type_code = item_type_code;

        // ProductSpecs is set depending on item_type_choice calling either add_music_player or addMoviePLayer.
        if (item_type_choice == 1 || item_type_choice == 3)
            new_product.product_specs = add_music_player();
        else
            new_product.product_specs = add_movie_player();

        //Allows the user to confirm their choice. Loop continues if entry_is_correct is assigned 0 (false)
        std::cout
                << "You entered " + new_product.manufacturer + " " + new_product.prod_name + " " +
                   new_product.product_specs + " " + new_product.item_type_code + ": " + item_type + ".\n"
                   + "If this is incorrect enter 0 to try again, or enter anything else to continue." << std::endl;

        std::cin >> entry_is_correct;

    } while (entry_is_correct == "0");

    //new_product string is set by concatenating manufacturer prod_name item_type_code
    new_product.product_info =
            new_product.manufacturer + " " + new_product.prod_name + " " + new_product.product_specs + " " +
            new_product.item_type_code;

    //new_product string is appended to ProductLine.csv file
    std::ofstream catalog_file;
    catalog_file.open("ProductLine.csv", std::ios::app);
    catalog_file << new_product.product_info << std::endl;
    catalog_file.close();

    std::cout << new_product.product_info << " has been added to the product catalog.\n" << std::endl;

    //new_product string is added to the product vector.
    products.emplace_back(new_product);

    selection_sort(products);
}

std::string add_music_player() {

    /*
     * Music Players store AudioSpecification (the file format, like wav or mp3)
     * and MediaType (what stores the audio file like CD, DVD, Blu-Ray), both input by the user.
     */

    //Clears the newline character from the previous choice within addNewProduct()
    std::cin.ignore();

    std::string audio_specs;
    std::string media_type;

    std::cout << "Please enter the supported file format(s) for the music player. If there are multiple supported\n"
                 "formats then separate them with a space. For example, WAV MP3, or WAV FLAC MP3." << std::endl;
    std::getline(std::cin, audio_specs);

    std::cout << "Please enter the media type(s) for the music player. For example, Digital, CD, DVD, or Blu-Ray."
              << std::endl;
    std::getline(std::cin, media_type);

    std::string music_player_specs = audio_specs + " " + media_type;

    return music_player_specs;
}

std::string add_movie_player() {

    /*
     * Movie Players store MonitorType, which is a Screen.
     * Screen stores: resolution, refresh rate, response time.
     */
    std::string monitor_type;
    int screen_choice;
    std::string entry_is_correct;

    //stores the screen's resolution, refresh rate, response time.
    std::string screen_specs;

    do {
        std::cout << "Please enter the number before the type of screen for this product.\n"
                     "1. LCD \n"
                     "2. LED \n"
                     "3. OLED" << std::endl;
        std::cin >> monitor_type;

        try {
            screen_choice = std::stoi(monitor_type);

        } catch (std::invalid_argument const &e) {
            std::cout << "You entered a string or a number with a decimal." << std::endl;
            entry_is_correct = "0";
            continue;
        }

        switch (screen_choice) {
            case 1:
                monitor_type = "LCD";
                break;
            case 2:
                monitor_type = "LED";
                break;
            case 3:
                monitor_type = "OLED";
                break;
            default:
                std::cout << "Your input is invalid. Please try again.\n";
                continue;
        }
    } while (entry_is_correct == "0");

    std::cin.ignore();
    std::cout << "Please enter the screen's resolution, refresh rate, and response time. For example,"
                 " 1080p 144 Hz 1 ms." << std::endl;
    std::getline(std::cin, screen_specs);

    std::string movie_player_specs = monitor_type + " " + screen_specs;

    return movie_player_specs;
}

void display_production_statistics(const Statistics &stats, std::vector<Product> &products,
                                   const std::vector<Production_Record> &prod_record) {
    std::cout << "Current production number: " << stats.production_number << std::endl;
    std::cout << "Audio serial number: " << stats.audio_serial_num << std::endl;
    std::cout << "Audio Mobile serial number: " << stats.audio_mobile_serial_num << std::endl;
    std::cout << "Visual serial number: " << stats.visual_serial_num << std::endl;
    std::cout << "Visual Mobile serial number: " << stats.visual_mobile_serial_num << std::endl;

    std::cout << "Total audio units produced: " << (stats.audio_serial_num + stats.audio_mobile_serial_num)
              << std::endl;
    std::cout << "Total visual units produced: " << (stats.visual_serial_num + stats.visual_mobile_serial_num)
              << std::endl;
    bool input_is_valid = false;
    do {
        std::cout
                << "\nPlease enter 1 to see the current production catalog or enter 2 to print the entire production log."
                << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "1") {
            input_is_valid = true;
            selection_sort(products);
            show_catalog(products);
        } else if (input == "2") {
            input_is_valid = true;
            if (prod_record.empty()) {
                std::cout << "The production log is empty. Enter 1 at the menu to add to the production log."
                          << std::endl;
                continue;
            }
            for (const Production_Record &record : prod_record) {
                std::cout << record.production_number << " " << record.product << " " << record.serial_num << std::endl;
            }
        } else {
            std::cout << "Your input was not either 1 or 2. Please try again." << std::endl;
        }

    } while (!input_is_valid);
}

void find_production_number(const std::vector<Production_Record> &prod_record) {

    if (prod_record.empty()) {
        std::cout << "No products have been produced. Please choose \"Produce Items\" at the menu to track production\n"
                     "which will generate production numbers and serial numbers." << std::endl;

    } else {

        std::cout << "Please enter the serial number of a product and the program will output the production number.\n";
        std::string input_serial_num;
        std::cin >> input_serial_num;

        bool serial_num_found = false;

        //Iterates through the production record checking if the input serial number matches the substring of the
        // serial number within the production record.
        for (int count = 0; count < prod_record.size(); count++) {

            if (prod_record[count].serial_num == input_serial_num) {
                std::cout << "The production number for the serial number you entered is " + std::to_string(count + 1);
                serial_num_found = true;
            }
        }

        if (!serial_num_found) {
            std::cout << "The serial number you entered does not exist.";
        }
    }
}

void selection_sort(std::vector<Product> &products) {
    //Selection sort of available products by name when a new product is added.
    std::string minimum_string;
    std::string temp;
    Product temp_product;
    for (int unsorted_boundary = 0; unsorted_boundary < (products.size() - 1); unsorted_boundary++) {

        //Finds minimum element in unsorted subarray
        int minimum_index = unsorted_boundary;
        minimum_string = products[unsorted_boundary].manufacturer;
        for (int unsorted_index = unsorted_boundary + 1; unsorted_index < products.size(); unsorted_index++) {

            if (minimum_string.compare(products[unsorted_index].manufacturer) > 0) {
                minimum_string = products[unsorted_index].manufacturer;
                minimum_index = unsorted_index;
            }
        }

        //Swaps the found minimum element with the first element of subarray
        if (minimum_index != unsorted_boundary) {
            temp_product = products[unsorted_boundary];

            products[unsorted_boundary] = products[minimum_index];

            products[minimum_index] = temp_product;
        }
    }
}