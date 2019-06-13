# NolzProceduralProject

  This procedural project is a part of the COP2001 curriculum

## Sprint 1 Backlog (SBL)

### 1. Output a greeting and menu in main.
  
## Sprint 2 Backlog (SBL) - Conditions, Loops, Functions, Files intro. 

### 1. Create a working menu
- The only menu options necessary for this sprint are Log Production and Exit.
- Only accept values that are listed in the menu.
- If the user selects a different value, they are asked to choose again.
- Menus is printed from a showMenu function that is called from main.
- Menu choices result in calls to functions.
- After output of menu choice, show menu again until user chooses to exit.
### 2. Add functionality to log production for the products from the previous sprint.
- The user should be able to choose which of the products was produced.
- Able to enter how many of the products were produced.
- A record should be output that displays the production number, manufacturer, product name, item type and serial number. 
- ProductionNumber should be unique, sequential for all products, and automatically assigned.
- The SerialNumber should start with the first three letters of the Manufacturer, two letter itemType code, then five digits (leading 0s if necessary that are unique and sequential for the item type. The entire Serial Number should be automatically assigned.

## Sprint 3 - Arrays and Vectors, Searching and Sorting

### 1. Store the product line in a collection (parallel vectors).
- Use code to populate some products.
- Allow the user to add products.
- All user to view the product line.
### 2. When logging production, the user should be prompted to enter the product produced from the product line.
### 3. Store the production log in a collection (parallel vectors). 
### 4. Output the product line sorted by name.
### 5. Given a Serial Number, output the Production Number 

## Sprint 4 - Pointers, Characters, Strings, Recursion

### 1. Create an Employee account.
1. Allow user to input full name in format FirstName LastName.  
- Generate user id, which is their first initial and surname in all lowercase
- Optional: Don't allow duplicate user names.
2. Allow user to input a password.
- The password must contain at least one digit, at least one lowercase letter, and at least one uppercase letter. The password cannot contain a space or any other symbols. 
- Use a recursive function to encrypt the password. 
### 2. Optional: Require users to log in. Track which employee recorded production.

## Sprint 5 - Data Structures, Structs, Files
### 1. Store product line, production records, and production statistics in structs.
### 2. Save products that can be produced to a text file named ProductLine.csv
### 3. Save the production log to a text file name ProductionLog.csv
### 4. Save the user names and encrypted passwords to a text file name Users.txt
### 5. Load data from the files into vectors of structs when the program starts.

## Sprint 6 - Quality Analysis

### 1. Output production statistics such as total number of items produced and number of items of each type.
### 2. Clear all warnings from Inspect Code.
### 3. Format code using standard style guidelines.
### 4. Enhance documentation:
- Javadoc style comments for Doxygen
- Comments in code
- README, create animated gif of program running
### 5. Deployment
