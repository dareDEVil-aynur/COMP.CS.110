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
#include <algorithm>
#include <iostream>
#include <set>

void Library::addBook(const std::string& library, const Book& book) {
    libraries[library].push_back(book);
}

void Library::material(const std::string& library) const {
    auto it = libraries.find(library);

    if (it == libraries.end()){
        std::cout << "Error: unknown library" << std::endl;
    } else {
        std::vector<Book> library_books = it->second;

        std::sort(library_books.begin(), library_books.end(),
                  [](const Book& a, const Book& b) {
            return a.author < b.author;
        });

        for (const auto& book : library_books) {
            std::cout << book.author << ": " << book.title << std::endl;
        }
    }
}

void Library::printBooks(const std::string& library, const std::string& author) const {
    auto it = libraries.find(library);

    if (it == libraries.end()){
        std::cout << "Error: unknown library" << std::endl;
    } else {
        std::vector<Book> library_books = it->second;

        std::sort(library_books.begin(), library_books.end(), [](const Book& a, const Book& b) {
            return a.title < b.title;
        });

        bool author_exists = false;

        for (const auto& book : library_books) {
            if (book.author == author){
                author_exists = true;

                if (book.reservations == 0){
                    std::cout << book.title << " --- on the shelf" << std::endl;
                } else {
                    std::cout << book.title << " --- " << book.reservations
                              << " reservations" << std::endl;
                }
            }
        }

        if (!author_exists){
            std::cout << "Error: unknown author" << std::endl;
        }
    }
}

void Library::reservable(const std::string& author, const std::string& book_title) const {
    bool found_book = false;
    int min_reservations = 100;
    std::map<int, std::vector<std::string>> queues;

    for (const auto& [library_name, library_books] : libraries) {
        for (const auto& book : library_books) {
            if (book.author == author && book.title == book_title) {
                found_book = true;

                if (book.reservations >= 100) {
                    std::cout << "Book is not reservable from any library" << std::endl;
                    return;
                }

                if (book.reservations == 0) {
                    std::cout << "on the shelf" << std::endl;
                    std::cout << "--- " << library_name << std::endl;
                    return;
                }

                if (book.reservations < min_reservations){
                    min_reservations = book.reservations;
                }

                queues[book.reservations].push_back(library_name);
            }
        }
    }

    if (!found_book) {
        std::cout << "Book is not a library book" << std::endl;
        return;
    }

    // Print the shortest reservation queue and available libraries
    if (!queues.empty()) {
        auto shortest_queue = queues.begin()->second;
        std::cout << min_reservations << " reservations" << std::endl;
        for (const auto& library_name : shortest_queue) {
            std::cout << "--- " << library_name << std::endl;
        }
    } else {
        std::cout << "Error: no reservation queues found" << std::endl;
    }
}

void Library::loanable() const {
    std::set<std::string> seen_books;
    std::vector<std::string> loanable_books;

    for (const auto& [library_name, library_books] : libraries) {
        for (const auto& book : library_books) {
            if (book.reservations == 0 && seen_books.find(book.author + " " + book.title)
                    == seen_books.end()) {
                seen_books.insert(book.author + " " + book.title);
                loanable_books.push_back(book.author + ": " + book.title);
            }
        }
    }

    // Sort the loanable books in alphabetical order based on author and title
    std::sort(loanable_books.begin(), loanable_books.end());

    // Print the loanable books
    for (const auto& book : loanable_books) {
        std::cout << book << std::endl;
    }
}

std::vector<std::string> Library::getLibraries() const {
    std::vector<std::string> libraryNames;

    for (const auto& library : libraries) {
        libraryNames.push_back(library.first);
    }

    return libraryNames;
}


