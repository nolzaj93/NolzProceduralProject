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

    //Vectors are declared.
    std::vector<std::string> products;
    std::vector<std::string> production_records;
    std::vector<std::string> usernames;
    std::vector<std::string> salts;
    std::vector<std::string> user_passwords;

    //Production and serial numbers are declared.
    int audio_serial_num = 1;
    int audio_mobile_serial_num = 1;
    int visual_serial_num = 1;
    int visual_mobile_serial_num = 1;

    //Loads existing products and production records if the respective text files exist, user info, and serial numbers.
    load_existing_data(products, production_records, usernames, salts, user_passwords, audio_serial_num,
                       audio_mobile_serial_num,
                       visual_serial_num, visual_mobile_serial_num);

    //Welcome message printed to the console.
    std::cout << "Welcome to the Production Line Tracker!\n";

    //If usernames is not empty, then authenticate is called to confirm employee ID. Otherwise, administrator registers
    // a master account.
    if (!usernames.empty())
        authenticate(usernames, salts, user_passwords);
    else {

        std::cout << "Administrator registration\n";
        add_employee_account(usernames, salts, user_passwords);
    }

    //Declare and initialize program_is_running as a flag bool for the while loop.
    bool program_is_running = true;

    //While loop that is repeated until the user enters 6 to exit which sets program_is_running to false.
    while (program_is_running) {

        //The loop calls prompt_menu_choice until the function returns false, which only occurs when the user enters 6.
        program_is_running = prompt_menu_choice(products, production_records, usernames, salts, user_passwords,
                                                audio_serial_num, audio_mobile_serial_num,
                                                visual_serial_num, visual_mobile_serial_num);
    }
    return 0;
}

void authenticate(std::vector<std::string> &usernames, std::vector<std::string> &salts,
                  std::vector<std::string> &user_passwords) {

    bool user_is_valid = false;
    int user_index = 0;

    do {

        while (!user_is_valid) {
            //Prompts for username and stores in input_username.
            std::cout << "\nPlease enter your username. It is the first letter of your first name\n"
                         "followed by your last name in all lowercase." << std::endl;
            std::string input_username;
            std::cin >> input_username;

            //Iterates through the usernames vector and checks if the input is the same as an element and sets
            // user_index to the index where the input matches.
            for (int index = 0; index < usernames.size(); index++) {
                if (usernames[index] == input_username) {
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
        input_password = sha256(encrypt_string(salts[user_index] + input_password));

        //If the string stored in input_password is equal to the stored hashed password, then user_is_valid is set to
        // true, and the user continues to the program.
        if (user_passwords[user_index] == input_password) {

            std::cout << "Welcome back, " + usernames[user_index] + "!" << std::endl;
            user_is_valid = true;

        } else {
            //If the hashed input_password does not match, then the loop continues because user_is_valid is set to false
            std::cout << "The password did not match to the username you entered." << std::endl;
            user_is_valid = false;
        }

    } while (!user_is_valid);
}

void load_existing_data(std::vector<std::string> &products, std::vector<std::string> &production_records,
                        std::vector<std::string> &usernames, std::vector<std::string> &salts,
                        std::vector<std::string> &user_passwords,
                        int &audio_serial_num, int &audio_mobile_serial_num, int &visual_serial_num,
                        int &visual_mobile_serial_num) {

    //Existing products are added to vector named products from catalog.txt if the file exists already
    std::string next_line;
    std::ifstream current_catalog_file("catalog.txt");

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (current_catalog_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(current_catalog_file, next_line)) {
            products.push_back(next_line);
        }
    }
    current_catalog_file.close();

    std::ifstream production_file("production.txt");

    //If production.txt exists then these records are added line by line to the production_records vector.
    if (production_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(production_file, next_line)) {
            production_records.push_back(next_line);

            //Increments the respective serial_num depending on the item type code found within each record.
            if (next_line.substr(next_line.length() - 7, 2) == "MM")
                audio_serial_num += 1;
            else if (next_line.substr(next_line.length() - 7, 2) == "AM")
                audio_mobile_serial_num += 1;
            else if (next_line.substr(next_line.length() - 7, 2) == "VI")
                visual_serial_num += 1;
            else if (next_line.substr(next_line.length() - 7, 2) == "VM")
                visual_mobile_serial_num += 1;
        }
    }
    production_file.close();

    std::ifstream user_info_file("usernames.txt");

    //If usernames.txt exists then these records are added line by line to the usernames vector.
    if (user_info_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(user_info_file, next_line)) {
            usernames.push_back(next_line);
        }
    }
    user_info_file.close();

    std::ifstream salts_file("salts.txt");

    //If userinfo.txt exists then these records are added line by line to the usernames vector.
    if (salts_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(salts_file, next_line)) {
            salts.push_back(next_line);
        }
    }
    salts_file.close();

    std::ifstream user_pw_file("userpws.txt");

    //If userinfo.txt exists then these records are added line by line to the usernames vector.
    if (user_pw_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(user_pw_file, next_line)) {
            user_passwords.push_back(next_line);
        }
    }
    user_pw_file.close();
}

bool prompt_menu_choice(std::vector<std::string> &products, std::vector<std::string> &production_records,
                        std::vector<std::string> &usernames, std::vector<std::string> &salts,
                        std::vector<std::string> &user_passwords, int &audio_serial_num, int &audio_mobile_serial_num,
                        int &visual_serial_num, int &visual_mobile_serial_num) {

    //Declare and initialize input_number which is used to hold number input by user.
    std::string input_text;
    int input_number = 0;

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

    std::cin >> input_text;

    try {
        input_number = std::stoi(input_text);
    } catch (std::invalid_argument const &e) {
        std::cout << "You entered a string or a number with a decimal. Please enter a number." << std::endl;
        return true;
    }

    //Switch statement calls the corresponding function, or if the the user enters 6 the loop is broken.
    switch (input_number) {
        case 1:
            produce_items(products, production_records, audio_serial_num, audio_mobile_serial_num, visual_serial_num,
                          visual_mobile_serial_num);
            break;
        case 2:
            std::cin.ignore();
            add_employee_account(usernames, salts, user_passwords);
            break;
        case 3:
            add_new_product(products);
            break;
        case 4:
            display_production_statistics();
            break;
        case 5:
            find_production_number(production_records);
            break;
        case 6:
            return false;
        default:
            std::cout << "Your input was invalid. Please try again." << std::endl;
            break;
    }
    return true;
}

void show_catalog(std::vector<std::string> products) {

    //If catalog.txt exists then existing products are printed, otherwise it is printed that the catalog is empty.
    if (!products.empty()) {

        std::cout << '\n' << "Current catalog: " << std::endl;

        for (int counter = 0; counter < products.size(); counter++) {

            std::cout << std::to_string(counter + 1) + ". " << products[counter] << std::endl;
        }

    } else std::cout << "The product catalog is empty." << std::endl;
}

void produce_items(std::vector<std::string> &products, std::vector<std::string> &production_records,
                   int &audio_serial_num, int &audio_mobile_serial_num, int &visual_serial_num,
                   int &visual_mobile_serial_num) {

    if (products.empty()) {
        std::cout << "The product catalog is empty. Please add a product to track production." << std::endl;
        return;
    }

    //Ignores the newline character read when the user presses enter/return.
    std::cin.ignore();

    int production_number;
    production_number = production_records.size() + 1;

    std::string entry_is_correct = "0";
    std::string product_choice;
    int choice_number = 0;
    int num_produced = 0;

    //Iterates at least once, and the loop will repeat if the user enters zero when prompted to confirm the input
    // or if the user does not enter a number 1-4.
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
        product_choice = products[(choice_number - 1)];

        std::cout << "Please enter the number of items that were produced." << std::endl;
        std::cin >> num_produced;

        //Allows the user to confirm their choice. Loop continues if entry_is_correct is assigned 0 (false)
        std::cout << "You chose " + product_choice + " and recorded that " +
                     std::to_string(num_produced) + " units were produced.\n"
                     + "If this is incorrect enter 0 to try again, or enter anything else \n"
                     + "to continue." << std::endl;
        std::cin >> entry_is_correct;

    } while (entry_is_correct == "0");

    // Declares production_file_write object and opens production.txt. New text is appended.
    std::ofstream production_file_write;
    production_file_write.open("production.txt", std::ios::app);

    //Assigns respective substrings from the product_choice to construct the serial number string.
    std::string item_type_code = product_choice.substr((product_choice.length() - 2), 2);
    std::string manufacturer_substr = product_choice.substr(0, 3);

    //For loop prints product Info for each product
    for (int counter = 0; counter < num_produced; counter++) {

        //product_info output string stream holds all product information to be written to production.txt
        std::ostringstream product_info;
        product_info << product_choice << " " << std::to_string(production_number++) << " ";

        /*
         * Adds respective serial number to the product_info ostringstream object, serial number is 5 characters wide
         * filled with zeros and added to the end of the first three letters of manufacturer and itemtypecode.
         */
        std::ostringstream serial_num;
        serial_num << manufacturer_substr << item_type_code;

        if (item_type_code == "MM")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(audio_serial_num++);
        else if (item_type_code == "AM")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(audio_mobile_serial_num++);
        else if (item_type_code == "VI")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(visual_serial_num++);
        else if (item_type_code == "VM")
            serial_num << std::setfill('0') << std::setw(5) << std::to_string(visual_mobile_serial_num++);

        product_info << serial_num.str();

        //Outputs a string from the product_info object on each iteration, and writes it to production.txt
        production_records.push_back(product_info.str());
        production_file_write << production_records[production_records.size() - 1] << std::endl;
    }
    production_file_write.close();
    std::cout << "Production record has been saved to file." << std::endl;
}

void add_employee_account(std::vector<std::string> &usernames, std::vector<std::string> &salts,
                          std::vector<std::string> &user_passwords) {

    std::string first_name;
    std::string last_name;
    bool username_valid;
    bool is_digit;
    bool is_space;
    bool is_not_alpha;

    do {
        username_valid = false;
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

            if (is_digit || is_space || is_not_alpha)
                throw std::exception();
            else
                username_valid = true;

        } catch (std::exception &ex) {
            if (is_digit)
                std::cout << "\nYou accidentally typed a number in your first name.\n";
            if (is_space)
                std::cout << "\nYour first name cannot contain a space.\n";
            if (is_not_alpha)
                std::cout << "\nYour first name cannot contain a special character.\n";
            continue;
        }

        username_valid = false;
        is_digit = false;
        is_space = false;
        is_not_alpha = false;

        try {

            std::cout << "\nPlease enter your last name. For example, Smith\n";
            std::getline(std::cin, last_name);

            //Iterates through each character of first_name checking if the character is a digit, space, or special ch.
            for (char next_char : last_name) {
                if (!is_digit && isdigit(next_char))
                    is_digit = true;
                else if (!is_space && isspace(next_char))
                    is_space = true;
                else if (!is_not_alpha && !isalnum(next_char))
                    is_not_alpha = true;
            }

            if (is_digit || is_space || is_not_alpha)
                throw std::exception();
            else
                username_valid = true;

        } catch (std::exception &ex) {
            if (is_digit)
                std::cout << "\nYou accidentally typed a number in your last name.\n";
            if (is_space)
                std::cout << "\nYour last name cannot contain a space.\n";
            if (is_not_alpha)
                std::cout << "\nYour last name cannot contain a special character.\n";
            continue;
        }

    } while (!username_valid);


    // Takes first letter of first_name and changes to lowercase.
    char first_letter = tolower(first_name[0]);

    // Changes last_name to all lowercase.
    std::transform(last_name.begin(), last_name.end(), last_name.begin(), tolower);

    // create user name in proper format
    std::string user_name = first_letter + last_name;

    std::cout << "User name: " + user_name << std::endl;

    bool password_is_incorrect;
    std::string pw_str;

    bool upper_is_found;
    bool lower_is_found;
    bool digit_is_found;
    bool space_is_found;
    bool special_is_found;

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
        std::cout << ((space_is_found || special_is_found)
                      ? "The password cannot contain spaces or special characters.\n" : "");

        std::cout << (!digit_is_found ? "The password did not contain a digit.\n" : "");
        std::cout << (!upper_is_found ? "The password did not contain an uppercase letter.\n" : "");
        std::cout << (!lower_is_found ? "The password did not contain a lowercase letter.\n" : "");

        std::cin.ignore();

    } while (password_is_incorrect);

    //Generates pseudo-random salt.
    std::random_device rd;
    srand(rd());
    std::string salt;
    salt = std::to_string((ULLONG_MAX / rd()));
    salts.push_back(salt);

    // Declares salts_file object and opens salts.txt. New text is appended.
    std::ofstream salts_file;
    salts_file.open("salts.txt", std::ios::app);

    salts_file << salt << std::endl;

    salts_file.close();

    // Declares userinfo_file object and opens userinfo.txt. New text is appended.
    std::ofstream userinfo_file;
    userinfo_file.open("usernames.txt", std::ios::app);

    userinfo_file << user_name << std::endl;

    userinfo_file.close();
    usernames.push_back(user_name);

    //Prepends salt to pw_str, encrypts, then runs through hash function.
    pw_str = encrypt_string(salt + pw_str);
    pw_str = sha256(pw_str);
    user_passwords.push_back(pw_str);

    // Declares pw_file object and opens userpws.txt. New text is appended.
    std::ofstream pw_file;
    pw_file.open("userpws.txt", std::ios::app);

    pw_file << pw_str << std::endl;

    pw_file.close();
}

std::string encrypt_string(std::string str) {
    if (str.length() == 1) {
        return str;
    } else {
        //Recursively call through the string adding to the ASCII value of each element.
        return char((int) str[0] + 7) + encrypt_string(str.substr(1, str.length() - 1));
    }
}

void add_new_product(std::vector<std::string> &products) {

    //prints the current catalog or let's the user know if it is empty.
    show_catalog(products);

    std::string entry_is_correct;
    std::string manufacturer;
    std::string prod_name;

    int item_type_choice = 0;
    std::string item_type_code;
    std::string item_type;

    std::string product_specs;

    do {
        //Ignores the newline character read when the user presses enter/return.
        std::cin.ignore();

        std::cout << "\n" << "Please enter the manufacturer." << std::endl;
        std::getline(std::cin, manufacturer);

        std::cout << "Please enter the product name." << std::endl;
        std::getline(std::cin, prod_name);

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

        // ProductSpecs is set depending on item_type_choice calling either add_music_player or addMoviePLayer.
        if (item_type_choice == 1 || item_type_choice == 3)
            product_specs = add_music_player();
        else
            product_specs = add_movie_player();

        //Allows the user to confirm their choice. Loop continues if entry_is_correct is assigned 0 (false)
        std::cout
                << "You entered " + manufacturer + " " + prod_name + " " + product_specs + " " + item_type_code
                   + ": " + item_type + ". If this is incorrect enter 0 to try again, or enter anything else\n"
                   + "to continue." << std::endl;

        std::cin >> entry_is_correct;

    } while (entry_is_correct == "0");

    //new_product string is set by concatenating manufacturer prod_name item_type_code
    std::string new_product = manufacturer + " " + prod_name + " " + product_specs + " " + item_type_code;

    //new_product string is appended to catalog.txt file
    std::ofstream catalog_file;
    catalog_file.open("catalog.txt", std::ios::app);
    catalog_file << new_product << std::endl;
    catalog_file.close();

    std::cout << new_product << " has been added to the product catalog.\n" << std::endl;

    //new_product string is added to the product vector.
    products.push_back(new_product);

    //Selection sort of available products by name when a new product is added.
    std::string minimum_string;
    std::string temp;
    for (int unsorted_boundary = 0; unsorted_boundary < (products.size() - 1); unsorted_boundary++) {

        //Finds minimum element in unsorted subarray
        int minimum_index = unsorted_boundary;
        minimum_string = products[unsorted_boundary];
        for (int unsorted_index = unsorted_boundary + 1; unsorted_index < products.size(); unsorted_index++) {

            if (minimum_string.compare(products[unsorted_index]) > 0) {
                minimum_string = products[unsorted_index];
                minimum_index = unsorted_index;
            }
        }

        //Swaps the found minimum element with the first element of subarray
        if (minimum_index != unsorted_boundary) {
            temp = products[unsorted_boundary];
            products[unsorted_boundary] = products[minimum_index];
            products[minimum_index] = temp;
        }
    }
}

std::string add_music_player() {

    /*
     * Music Players store AudioSpecification (the file format, like wav or mp3)
     * and MediaType (what stores the audio file like CD, DVD, Blu-Ray), both input by the user.
     */

    //Clears the newline character from the previous choice within addNewProduct()
    std::cin.ignore();

    std::string entry_is_correct;
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
                     "3. OLED." << std::endl;
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

void display_production_statistics() {
    std::cout << "Display Production Statistics Stub\n";
}

void find_production_number(std::vector<std::string> production_records) {

    if (production_records.empty()) {
        std::cout << "No products have been produced. Please choose \"Produce Items\" at the menu to track production\n"
                     "which will generate production numbers and serial numbers." << std::endl;

    } else {

        std::cout << "Please enter the serial number of a product and the program will output the production number.\n";
        std::string input_serial_num;
        std::cin >> input_serial_num;

        bool serial_num_found = false;
        std::string record;

        for (int count = 0; count < production_records.size(); count++) {
            record = production_records[count];

            if (record.substr(record.length() - 10, 10) == input_serial_num) {
                std::cout << "The production number for the serial number you entered is " + std::to_string(count + 1);
                serial_num_found = true;
            }
        }

        if (!serial_num_found) {
            std::cout << "The serial number you entered does not exist.";
        }
    }
}