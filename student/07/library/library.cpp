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

bool readInput(std::map<std::string, Library>& libraries){
    std::string input_file = "";

    std::cout << "Input file: ";
    getline(std::cin, input_file);

    std::ifstream file_object(input_file);
    //File must be able to open, otherwise quit with EXIT_FAILURE
    if( not file_object ){
        std::cout << "Error: input file cannot be opened" << std::endl;
        return false;
    } else {
        std::string line = "";
        while(getline(file_object, line)){
            std::istringstream ss(line);
            std::string library_name = "";
            std::string author = "";
            std::string title = "";
            std::string status = "";
            int reservations = 0;

            getline(ss, library_name, ';');
            getline(ss, author, ';');
            getline(ss, title, ';');
            getline(ss, status, ';');

            //Any empty field in the input data results in EXIT_FAILURE
            if (library_name.empty() or title.empty() or author.empty() or status.empty()){
                std::cout << "Error: empty field" << std::endl;
                return false;
            }

            if (status != "on-the-shelf"){
                reservations = std::stoi(status);
            }

            Book book;
            book.author = author;
            book.title = title;
            book.reservations = reservations;

            // check if library already exists, if not, create a new one
            if(libraries.find(library_name) == libraries.end()){
                Library newLibrary(library_name);
                libraries[library_name] = newLibrary;
            }

            libraries[library_name].addBook(book);
        }
        file_object.close();
        return true;
    }
}

void printLibraries(const std::map<std::string, Library>& libraries) {
    for(auto& pair : libraries) {
        const Library& lib = pair.second;
        std::cout << "Library " << lib.getLibraryName() << ":\n";
        const std::vector<Book>& books = lib.getBooks();
        for(const Book& book : books) {
            std::cout << book.title << ", " << book.author;
            if(book.reservations > 0)
                std::cout << ", " << book.reservations << " reservations";
            std::cout << "\n";
        }
    }
}

void addLibrary(std::map<std::string, Library>& libraries, std::string library_name) {
    libraries[library_name] = Library(library_name);
}

void addBook(std::map<std::string, Library>& libraries, std::string library_name, Book book) {
    libraries[library_name].addBook(book);
}

bool removeLibrary(std::map<std::string, Library>& libraries, std::string library_name) {
    auto it = libraries.find(library_name);
    if(it != libraries.end()) {
        libraries.erase(it);
        return true;
    }
    return false;
}

bool removeBook(std::map<std::string, Library>& libraries, std::string library_name, std::string book_title) {
    auto it = libraries.find(library_name);
    if(it != libraries.end()) {
        return it->second.removeBook(book_title);
    }
    return false;
}
