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

#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <map>
#include <string>
#include <vector>

struct Book {
    std::string title;
    std::string author;
    int reservations;
};

class Library {
    public:
        void addBook(const std::string& library, const Book& book);
        void material(const std::string& library) const;
        void printBooks(const std::string& library, const std::string& author) const;
        void reservable(const std::string& author, const std::string& book_title) const;
        void loanable() const;
        std::vector<std::string> getLibraries() const;
    private:
        std::map<std::string, std::vector<Book>> libraries;
};

#endif //LIBRARY_HH
