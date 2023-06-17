#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string str, char splitter, bool ignore_empty_parts = false) {
    std::vector<std::string> parts;
    std::string string;

    for (unsigned long i = 0; i < str.size(); ++i) {
        if (str.at(i) == splitter) {
            parts.push_back(string);
            string.clear();
        } else {
            string.push_back(str.at(i));
        }
    }
    parts.push_back(string);

    if (ignore_empty_parts) {
        std::vector<std::string> parts_no_empty;
        for (std::string sample : parts) {
            if (!sample.empty()) {
                parts_no_empty.push_back(sample);
            }
        }
        return parts_no_empty;
    }
    return parts;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
