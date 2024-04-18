#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

/// \brief A constant to define the shift for the password encryption.
const int shift = 3;

/// \brief The main password to access the program.
const std::string mainPassword = "pas";



/**
 * \brief Clears the console output.
 *
 * Function to clear the console by printing out 50 empty lines.
 */
void clearConsole() {
    for (int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }
}


void tryAgain();







/**
 * \struct PasswordData
 * \brief A structure to store password data.
 *
 * This structure is used to hold all details about a password,
 * including its name, the password, the category, the website, and the login.
 */
struct PasswordData {

    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;


    /**
     * \brief Converts password data to a string.
     *
     * This method is used to convert all password data to a single string.
     * Each piece of data is separated by a newline character.
     *
     * \return A string containing all password data.
     */
    std::string toString() const {
        std::string result;
        result += name + "\n";
        result += password + "\n";
        result += category + "\n";
        result += website + "\n";
        result += login + "\n" + "\n";
        return result;
    }

};




/**
 * \class PasswordManager
 * \brief A class to manage passwords.
 *
 * This class provides functionality for managing passwords. It allows
 * storing, retrieving, and manipulating password data stored in a
 * specified file.
 */
class PasswordManager {

private:
    std::string fileName;
    std::vector<PasswordData> passwords = loadToVector();


public:
    PasswordManager(const std::string& fileName) : fileName(fileName) {

        std::ofstream file(fileName, std::ios::app);


    }

    /**
 * \brief Main application loop.
 *
 * This method continuously displays a command menu and waits for user input. Depending on the input,
 * it calls appropriate methods to perform actions such as searching passwords, sorting passwords,
 * adding or editing a password, and adding or deleting a category. If the input is not recognized,
 * it prints an error message and waits for another input.
 */
    void run() {
        std::string command;

        while (true) {

            std::cout << "-------------------------------" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "| Pick a number of a command  |" << std::endl;
            std::cout << "| that you would like to use  |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "| 1. Search                   |" << std::endl;
            std::cout << "| 2. Sort passwords           |" << std::endl;
            std::cout << "| 3. Add password             |" << std::endl;
            std::cout << "| 4. Edit password(x)         |" << std::endl;
            std::cout << "| 5. Delete password          |" << std::endl;
            std::cout << "| 6. Add category(x)          |" << std::endl;
            std::cout << "| 7. Delete category(x)       |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "-------------------------------" << std::endl;

            std::cin >> command;

            if (command == "1") {
                searchPasswords();
            } else if (command == "2") {
                sortPasswords();
            } else if (command == "3") {
                addPassword();
            } else if (command == "4") {
                editPassword();
            } else if (command == "5") {
                deletePassword();
            } else if (command == "6") {
                addCategory();
            } else if (command == "7") {
                deleteCategory();
            } else {
                std::cout << "-------------------------------" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|       Unknown command.      |" << std::endl;
                std::cout << "|       Please try again.     |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "-------------------------------" << std::endl;
            }
        }
    }



    /**
 * \brief Loads password data from the source file into vectors.
 *
 * This method opens the source file specified by fileName, reads each line of the file, and uses the lines
 * to create PasswordData objects which are then stored in a vector. Empty lines are skipped during this process.
 * The vector of loaded passwords is then returned.
 *
 * \return A vector of PasswordData objects representing all passwords loaded from the source file.
 */
    std::vector<PasswordData> loadToVector(){

        std::ifstream file(fileName);
        std::string line;
        std::vector<PasswordData> loadedPasswords;

            while (std::getline(file, line)) {

                if (line.empty()) {
                    continue;
                }

                PasswordData data;

                data.name = line;
                std::getline(file, data.password);
                std::getline(file, data.category);
                std::getline(file, data.website);
                std::getline(file, data.login);

                loadedPasswords.push_back(data);
            }


            file.close();
            return loadedPasswords;
    }


private:






    /**
 * \brief Encrypts the provided data.
 *
 * This static method performs a basic Caesar cipher encryption on the provided data string,
 * shifting each character in the string by a fixed amount defined by the 'shift' constant.
 * The encrypted data is then returned.
 *
 * \param data The data to be encrypted.
 * \return A string representing the encrypted data.
 */
    static std::string encryptData(const std::string& data) {
        std::string encryptedData = data;
        for (char& c : encryptedData) {
            c += shift;
        }
        return encryptedData;
    }




    /**
 * \brief Decrypts the provided data.
 *
 * This static method performs a basic Caesar cipher decryption on the provided encrypted data string,
 * shifting each character in the string back by a fixed amount defined by the 'shift' constant.
 * The decrypted data is then returned.
 *
 * \param encryptedData The encrypted data to be decrypted.
 * \return A string representing the decrypted data.
 */
    static std::string decryptData(const std::string& encryptedData) {
        std::string decryptedData = encryptedData;
        for (char& c : decryptedData) {
            c -= shift;
        }
        return decryptedData;
    }



    /**
 * \brief Add new password to the program.
 *
 * This method prompts the user to input details for a new password set.
 * It encrypts each entered data and stores them in a PasswordData structure.
 * The encrypted data is then written to the file and added to the passwords vector.
 */
    void addPassword() {

        clearConsole();


        PasswordData newPasswordSet;
        std::string temp;

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|       Type in the name      |" << std::endl;
        std::cout << "|     of the password set:    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cin >> temp;
        newPasswordSet.name = encryptData(temp);


        clearConsole();

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|          optional           |" << std::endl;
        std::cout << "|     (for none type 'x')     |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|      Type in the login      |" << std::endl;
        std::cout << "|        for this set:        |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cin >> temp;
        newPasswordSet.login = encryptData(temp);

        clearConsole();

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|     Type in the password    |" << std::endl;
        std::cout << "|        for this set:        |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cin >> temp;
        newPasswordSet.password = encryptData(temp);

        clearConsole();

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|     Type in the category    |" << std::endl;
        std::cout << "|     of the password set:    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cin >> temp;
        newPasswordSet.category = encryptData(temp);

        clearConsole();

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|          optional           |" << std::endl;
        std::cout << "|     (for none type 'x')     |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|     Type in the website     |" << std::endl;
        std::cout << "|    for the password set:    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cin >> temp;
        newPasswordSet.website = encryptData(temp);



        std::string enryptedPasswordSet = newPasswordSet.toString();

        std::ofstream file(fileName, std::ios::app);

        if(file.is_open()){
            file << enryptedPasswordSet;
            file.close();
            passwords.push_back(newPasswordSet);
            std::cout << "-------------------------------" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|     Password  has been      |" << std::endl;
            std::cout << "|     successfully added      |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "-------------------------------" << std::endl;
        }else{
            clearConsole();
            passwords.push_back(newPasswordSet);
            std::cout << "-------------------------------" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|      An error occurred      |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "-------------------------------" << std::endl;
        }
    }




    /**
 * \brief Search password data by the password set name.
 *
 * This method allows the user to search for a password set by its name.
 * It iterates over the passwords vector, and for each password set,
 * it decrypts the name and checks if it matches the entered search term.
 * If a match is found, it displays the details of the password set.
 */
    void searchPasswords() {

        clearConsole();


        std::string searchTerm;
        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|       Search the name       |" << std::endl;
        std::cout << "|       of the password:      |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cin >> searchTerm;



        bool found = false;

        for(const auto& password : passwords){

            if((decryptData(password.name)) == searchTerm){

                std::cout << "-------------------------------" << std::endl;
                std::cout << "Name: " << decryptData(password.name) << std::endl;
                std::cout << "Category: " << decryptData(password.category) << std::endl;
                std::cout << "Website: " << decryptData(password.website) << std::endl;
                std::cout << "Login: " << decryptData(password.login) << std::endl;
                std::cout << "Password: " << decryptData(password.password)<< std::endl;
                std::cout << "-------------------------------" << std::endl;
                found = true;

            }
        }

        if (!found) {
            std::cout << "-------------------------------" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|   Can't find any matches.   |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "-------------------------------" << std::endl;
        }
    }


    /**
 * @brief Sorts a vector of passwords.
 *
 * This function sorts the list of passwords based on user input. The user can choose to sort the passwords alphabetically or by category.
 * If the user chooses to sort by category, they will be prompted to enter the desired category, and the function will print out the
 * passwords belonging to that category. If the category doesn't exist in the list of passwords, the user will be informed that no
 * matches were found.
 *
 * If the user chooses to sort the passwords alphabetically, the function will make a copy of the passwords vector, sort the copy
 * alphabetically by the password name, and print out the sorted list.
 *
 * @note The function assumes that the `PasswordData` structure contains encrypted data. Therefore, it decrypts the data before
 * printing and comparing.
 *
 * @note This function interacts with the user through the console, prompting the user to enter commands and categories and printing out results.
 *
 * @see compareAlphabetic()
 */
    void sortPasswords() {

        clearConsole();

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|      How do you want to     |" << std::endl;
        std::cout << "|     sort your passwords?    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|       to proceed type:      |" << std::endl;
        std::cout << "|    (alphabetic/category)    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;

        std::string command;
        std::cin >> command;

        if(command == "category"){
            clearConsole();
            std::cout << "-------------------------------" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|    Type in the category:    |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "-------------------------------" << std::endl;

            std::string category;
            std::cin >> category;


            bool foundCategory = false;

            clearConsole();
            for(const auto& password : passwords){

                if((decryptData(password.category)) == category){

                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Name: " << decryptData(password.name) << std::endl;
                    std::cout << "Category: " << decryptData(password.category) << std::endl;
                    std::cout << "Website: " << decryptData(password.website) << std::endl;
                    std::cout << "Login: " << decryptData(password.login) << std::endl;
                    std::cout << "Password: " << decryptData(password.password)<< std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    foundCategory = true;

                }
            }
            if(!foundCategory){

                clearConsole();
                std::cout << "-------------------------------" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|   Can't find any matches.   |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "|                             |" << std::endl;
                std::cout << "-------------------------------" << std::endl;
            }



        }
        else if(command == "alphabetic"){

            std::vector<PasswordData> sortedPasswords = passwords;
            std::sort(sortedPasswords.begin(), sortedPasswords.end(), compareAlphabetic);

            clearConsole();
            for (const auto& password : sortedPasswords){
                std::cout << "-------------------------------" << std::endl;
                std::cout << "Name: " << decryptData(password.name) << std::endl;
                std::cout << "Category: " << decryptData(password.category) << std::endl;
                std::cout << "Website: " << decryptData(password.website) << std::endl;
                std::cout << "Login: " << decryptData(password.login) << std::endl;
                std::cout << "Password: " << decryptData(password.password)<< std::endl;
                std::cout << "-------------------------------" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }

    }

    /**
 * @brief Compares two PasswordData objects alphabetically by name.
 *
 * This function decrypts the `name` fields of two `PasswordData` objects and compares them. It's used by the `std::sort` function in `sortPasswords()`
 * to sort a vector of `PasswordData` alphabetically.
 *
 * @param x The first PasswordData object to compare.
 * @param y The second PasswordData object to compare.
 *
 * @return True if the name of the first PasswordData object is less than the name of the second one, False otherwise.
 */
    static bool compareAlphabetic(const PasswordData& x, const PasswordData& y) {
        return decryptData(x.name) < decryptData(y.name);
    }



    void editPassword() {
        //TODO
    }




    /**
 * @brief Deletes a chosen password set.
 *
 * This function allows the user to delete a password from the list of passwords. The user is asked to type the name of the password
 * they want to delete, which is then encrypted. The user is then asked for confirmation before the password is deleted. If the user
 * confirms the deletion, the password is deleted from the file and the vector of passwords.
 *
 * @note The function assumes that the password names in the vector of passwords are encrypted. Therefore, it encrypts the user's input
 * before comparing it with the password names.
 *
 * @note This function interacts with the user through the console, prompting the user to enter the name of the password and confirm the
 * delete and informing the user that the password has been deleted.
 *
 * @see encryptData()
 * @see deletePasswordFromFile()
 */
    void deletePassword() {

        clearConsole();

        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|        Type the name        |" << std::endl;
        std::cout << "|     of the password that    |" << std::endl;
        std::cout << "|      you want to delete:    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;

        std::string nameOfThePasswordToDeleteDEC;
        std::cin >> nameOfThePasswordToDeleteDEC;
        std::string nameOfThePasswordToDeleteENC = encryptData(nameOfThePasswordToDeleteDEC);


        clearConsole();
        std::cout << "-------------------------------" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|        Are you sure?        |" << std::endl;
        std::cout << "|    (type yes to confirm)    |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "|                             |" << std::endl;
        std::cout << "-------------------------------" << std::endl;

        std::string command;
        std::cin >> command;

        if(command == "yes") {


            deletePasswordFromFile(fileName, nameOfThePasswordToDeleteENC);


            for (auto it = passwords.begin(); it != passwords.end();) {
                if (it->name == nameOfThePasswordToDeleteENC) {
                    it = passwords.erase(it);
                } else {
                    ++it;
                }
            }

            clearConsole();
            std::cout << "-------------------------------" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|        Password has         |" << std::endl;
            std::cout << "|        been deleted.         |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "|                             |" << std::endl;
            std::cout << "-------------------------------" << std::endl;

        }
    }



    /**
 * @brief Helper method that removes a password set from a text file.
 *
 * This static function deletes a specific password from a file. The password to be deleted is identified by its encrypted name.
 * The function creates a temporary file where it writes all the data from the original file, excluding the password to be deleted.
 * After the data has been copied, the original file is deleted and the temporary file is renamed to the original file's name,
 * effectively replacing the original file with a version that does not contain the password to be deleted.
 *
 * @param fileName The name of the file from which the password is to be deleted.
 * @param nameOfThePasswordToDeleteENC The encrypted name of the password to be deleted.
 *
 * @note This function assumes that the password data is stored in the file as blocks of 6 lines, where the first line is the encrypted
 * name of the password and the following five lines are the remaining password data. Therefore, when the function finds the line
 * containing the password name, it skips the following five lines.
 */
    static void deletePasswordFromFile(const std::string& fileName, const std::string& nameOfThePasswordToDeleteENC){


        std::ifstream file(fileName);
        std::ofstream tmpFile("tmpFile.txt");

        int count = -1;


        std::string line;


        while(std::getline(file, line)){

            if(line == nameOfThePasswordToDeleteENC){
                count = 5;
                count--;
                continue;
            }
            if(count == 4 || count == 3 || count == 2 || count == 1 || count == 0){
                count--;
                continue;
            }

            tmpFile << line << std::endl;
        }

        file.close();
        tmpFile.close();


        std::remove(fileName.c_str());
        std::rename("tmpFile.txt", fileName.c_str());

    }


    void addCategory() {
        //TODO
    }

    void deleteCategory() {
        //TODO
    }

};





















//main menu
void menuTypePassword(){

    clearConsole();

    std::cout << "-------------------------------" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|           Hello             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|         Welcome to          |" << std::endl;
    std::cout << "|    The Password Manager     |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|    To start, type in the    |" << std::endl;
    std::cout << "|     name of the source      |" << std::endl;
    std::cout << "|           file:             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "-------------------------------" << std::endl;

    std::string fileName;
    std::cin >> fileName;


    clearConsole();

    std::cout << "-------------------------------" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|   To continue, type in the  |" << std::endl;
    std::cout << "|     general password:       |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "-------------------------------" << std::endl;

    std::string typedPassword;
    std::cin >> typedPassword;

    if(typedPassword == mainPassword) {
        clearConsole();
        PasswordManager manager(fileName);
        manager.run();
    }
    else{
        tryAgain();
    }

}

//wrong password screen
void tryAgain(){
    clearConsole();

    std::cout << "-------------------------------" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|        Wrong password       |" << std::endl;
    std::cout << "|    type 'x' to try again:   |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "|                             |" << std::endl;
    std::cout << "-------------------------------" << std::endl;

    std::string command;
    std::cin >> command;

    if(command == "x"){
        menuTypePassword();
    }
}





int main() {

    menuTypePassword();



    return 0;
}
