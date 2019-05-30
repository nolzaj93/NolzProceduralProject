# NolzProceduralProject

  This procedural project is a part of the COP2001 curriculum

## Sprint 1 Backlog (SBL)

### 1. Output a greeting and menu in main.
  
## Sprint 2 Backlog (SBL) - Conditions, Loops, Functions, Files intro. 

### 1. Only accept values that are listed in the menu
### 2. If the user selects a different value, they are asked to choose again
### 3. Menu is printed from a run_program function
### 4. Menu choices result in calls to functions
### 5. After output of menu choice, show menu again
### 6. Add new products that are able to be produced:
- Manufacturer, Name, and ItemType 
- The user should be prompted to enter the Manufacturer, like Apple. Tip: while testing, you can comment out the line that reads in the user's response and just assign to the variable. 
- The user should be prompted to enter the Name, like iPod. Tip: while testing, you can comment out the line that reads in the user's response and just assign to the variable.
- The user should be given a menu choice for ItemType: Audio ("MM"), Visual ("VI"), AudioMobile ("AM"), or VisualMobile ("VM").
- Optional: save products that can be produced to a text file named catalog.txt
### 7. Track production of products
- Be able to track production for at least one product. 
- Optional: Display the catalog to show the user available products. 
- The record for the produced product should include the Manufacturer, Name, ItemType, ProductionNumber, and SerialNumber 
- ProductionNumber should be unique, sequential for all products, and automatically assigned.
- The SerialNumber should start with the first three letters of the Manufacturer, then the two letter ItemType code, then five digits (with leading 0s if necessary) that are unique and sequential for the item type. The entire Serial Number should be automatically assigned. 
- Save records of production to a text file named production.txt in a format like Production Number: 1 Serial Number: AppAM00001
- Create a repl in repl.it demonstrating saving to a file and include a link to the repl in your README.
- repl link: https://repl.it/@AustinNolz/ProceduralSBL1

- Optional: Music Players store AudioSpecification (the file format, like wav or mp3) and MediaType (what stores the audio file like CD, DVD, Blu-Ray), both input by the user.
- Optional: Movie Players store MonitorType, which is a Screen.
Screen stores: resolution, refresh rate, response time.

## Sprint 3 - Arrays and Vectors, Searching and Sorting

### 1. Store the products that are able to be produced in a collection.
### 2. When tracking production of products, the user should be prompted to enter the product to be produced from the collection of products that are able to be produced.
### 3. The record of products produced should be stored in a collection.
### 4. The products that can be produced should be sorted by name.
### 5. Given a Serial Number, output the Production Number

## Sprint 4 - Pointers, Characters, Strings, Recursion

### 1. Create an Employee account.
- Allow user to input full name in format FirstName LastName.  
- Generate user id, which is their first initial and surname in all lowercase
### 2. Associate Employee with a department id
### 3. deptId - recursively using a method named reverseString()

## Sprint 5 - Data Structures, Structs, Files

### 1. Store Products in structs
### 2. Create a directory and file structure by combining the path and file name.
### 3. Save the products, production info, and employee info to file.
### 4. Add ability to ViewFileInfo
### 5. Add ability to load data from file

## Sprint 6 - Quality Analysis

### 1. Bugs
### 2. Style
### 3. Documentation
### 4. Deployment
