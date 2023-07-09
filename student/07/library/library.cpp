/*Library

* Description:
* This software application provides a comprehensive solution for managing a library book catalogue.
* It includes a user-friendly interface that allows users to interact with the catalogue efficiently.
* The program imports library data from a CSV file and stores it in a well-organized data structure,
* facilitating easy retrieval and printing of the data.

* The CSV file contains rows of data, each consisting of four essential fields: library name, author,
* book name, and availability status (indicating the number of people waiting or if the book is currently
* available on the shelf). It is crucial that none of these fields are left empty.

* Upon launching the program, the user is prompted to select an input file. The file is automatically
* accessed from the build folder. If the file cannot be read, an error message is displayed, and
* the program terminates immediately. However, if the file is successfully located, it undergoes a validation
* process to ensure correct formatting, and the data is then imported into the data structure.

* Once the data structure is initialized, users can utilize various commands to retrieve specific information.
* For example, they can search for books in a particular library, books written by a specific author,
* book reservations, or loanable books. The program allows users to
* input commands repeatedly until they decide to quit by typing "quit.
*
* Name: Aynur Rahman Talukdar
* Student number: 150189473
* UserID: qkayta
* E-Mail: aynurrahman.talukdar@tuni.fi
*/

#include "library.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

bool readInput(std::map<std::string, std::vector<Book>>& books){
    std::string input_file = "";

    std::cout << "Input file: ";
    getline(cin, input_file);

    ifstream file_object(input_file);
    if( not file_object ){
        std::cout << "Error: input file cannot be opened" << std::endl;
        return false;
    } else {
        std::string line = "";
        while(getline(file_object, line)){
            std::istringstream ss(line);
            string library = "";
            string author = "";
            string title = "";
            string status = "";
            int reservations = 0;

            getline(ss, library, ';');
            getline(ss, author, ';');
            getline(ss, title, ';');
            getline(ss, status, ';');

            if (library.empty() or title.empty() or author.empty() or status.empty()){
                std::cout << "Error: empty field" << std::endl;
                return false;
            }

            if (status != "on-the-shelf"){
                reservations = stoi(status);
            }
            Book book;
            book.author = author;
            book.title = title;
            book.reservations = reservations;
            books[library].push_back(book);
        }
        file_object.close();
        return true;
    }
}
