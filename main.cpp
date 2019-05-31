/** @file main.cpp
 *  @brief This file is C++ source code for the COP2001 Procedural Project.
 *
 *  @author Austin Nolz
 *  @bug - No known bugs currently.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "prototypes.h"

/**
 * @brief This is the main function which is the starting point of the program.
 * @return - If the program runs to completion then this function returns zero.
 */
int main() {

    run_program();

    return 0;
}

void run_program() {

    std::vector<std::string> products;

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

    //Vector to hold the production_records is declared and production.txt is opened if it exists.
    std::vector<std::string> production_records;
    std::ifstream production_file("production.txt");

    //If production.txt exists then these records are added line by line to the production_records vector.
    if (production_file.is_open()) {

        //Adds each line to the product catalog vector.
        while (getline(production_file, next_line)) {
            production_records.push_back(next_line);
        }
    }
    production_file.close();

    //Welcome message printed to the console.
    std::cout << "Welcome to the Production Line Tracker!\n";

    //Declare and initialize input_number which is used to hold number input by user.
    std::string input_text;
    int input_number = 0;

    //Declare and initialize program_is_running as a flag bool for the while loop.
    bool program_is_running = true;

    //While loop that is repeated until the user enters 6 to exit which sets program_is_running to false.
    while (program_is_running) {

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
            continue;
        }

        //Switch statement calls the corresponding function, or if the the user enters 6 the loop is broken.
        switch (input_number) {
            case 1:
                produce_items(products, production_records);
                break;
            case 2:
                add_employee_account();
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
                program_is_running = false;
                break;
            default:
                std::cout << "Your input was invalid. Please try again." << std::endl;
                break;
        }
    }
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

void produce_items(std::vector<std::string> &products, std::vector<std::string> &production_records) {

    //Ignores the newline character read when the user presses enter/return.
    std::cin.ignore();

    //Production and serial numbers are declared.
    int production_number = 1;
    int audio_serial_num = 1;
    int audio_mobile_serial_num = 1;
    int visual_serial_num = 1;
    int visual_mobile_serial_num = 1;

    //Declares production_file_read ifstream object to set serial numbers depending on frequency of item type codes.
    std::ifstream production_file_read("production.txt");
    std::string next_line;

    //If production.txt exists then these records are added line by line to the production_records vector.
    if (production_file_read.is_open()) {
        production_number = production_records.size() + 1;

        //Increments the respective serial_num depending on the item type code found within each record.
        while (getline(production_file_read, next_line)) {
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
    production_file_read.close();

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

void add_employee_account() {
    std::cout << "Add Employee Account Stub\n";
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