/* Mystery carpet
 *
 * Desc:
 *   This program implements a mystery carpet applying pattern matching.
 * The carpet consists of squares of different colors, which also holds
 * true for the pattern, but the size of the pattern is always 2 x 2, i.e.
 * it has four colored squares. The program searches for pattern
 * occurrences from the carpet.
 *   At first, the program asks for the size of the carpet (width and heigth).
 * The user is also asked for if the carpet (grid) will be filled with
 * randomly drawn colors, or with user-given ones. In the first option,
 * a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input as many colors as the
 * there are squares in the carpet, whereupon the user lists the first
 * letters of the colors as one long string.
 *   On each round, the user is asked for a pattern to be searched for
 * (a string consisting of four letters/colors). The program prints, how
 * many occurrences was found and from which coordinates they were found.
 *   The program checks if the user-given colors are among accepted ones.
 * The program terminates when the user gives a quitting command ('q' or 'Q').
 *
 * Program author
 * Name: Aynur Rahman Talukdar
 * Student number: 150189473
 * UserID: qkayta
 * E-Mail: aynurrahman.talukdar@tuni.fi
 *
 * */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

enum Color {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};
const char* ColorChar = "RGBYW";

std::vector<std::vector<Color>> carpet;
using Location = std::pair<int, int>;

Color charToColor(char c) {
    for (int i = 0; i < NUMBER_OF_COLORS; i++) {
        if (toupper(c) == ColorChar[i]) {
            return static_cast<Color>(i);
        }
    }
    throw std::invalid_argument("Unknown color");
}

void fillCarpetRandom(int width, int height, int seed) {
    srand(seed);
    carpet.resize(height, std::vector<Color>(width));
    for (auto& row : carpet) {
        for (auto& c : row) {
            c = static_cast<Color>(rand() % NUMBER_OF_COLORS);
        }
    }
}

void fillCarpetInput(int width, int height, const std::string& input) {
    if (input.size() != width * height) {
        throw std::invalid_argument("Wrong amount of colors");
    }
    carpet.resize(height, std::vector<Color>(width));
    int i = 0;
    for (auto& row : carpet) {
        for (auto& c : row) {
            c = charToColor(input[i++]);
        }
    }
}

void printCarpet() {
    for (const auto& row : carpet) {
        for (const auto& c : row) {
            std::cout << ColorChar[c];
        }
        std::cout << '\n';
    }
}

std::vector<Location> searchPattern(const std::string& pattern) {
    int patWidth = 2, patHeight = 2;
    std::vector<std::vector<Color>> pat(patHeight, std::vector<Color>(patWidth));

    if (pattern.size() != patWidth * patHeight) {
        throw std::invalid_argument("Wrong pattern size");
    }

    int i = 0;
    for (auto& row : pat) {
        for (auto& c : row) {
            c = charToColor(pattern[i++]);
        }
    }

    std::vector<Location> locations;
    for (int y = 0; y <= carpet.size() - patHeight; y++) {
        for (int x = 0; x <= carpet[0].size() - patWidth; x++) {
            bool match = true;
            for (int py = 0; match && py < patHeight; py++) {
                for (int px = 0; px < patWidth; px++) {
                    if (carpet[y + py][x + px] != pat[py][px]) {
                        match = false;
                        break;
                    }
                }
            }
            if (match) {
                locations.emplace_back(x, y);
            }
        }
    }
    return locations;
}

int main() {
    int width, height, seed;
    char start;
    std::string input;

    std::cout << "Enter carpet's width and height: ";
    std::cin >> width >> height;
    if (width < 2 || height < 2) {
        std::cout << "Error: Carpet cannot be smaller than pattern.\n";
        return EXIT_FAILURE;
    }

    while (true) {
        std::cout << "Select start (R for random, I for input): ";
        std::cin >> start;
        if (toupper(start) == 'R') {
            while (true) {
                std::cout << "Enter a seed value: ";
                std::cin >> seed;
                if (std::cin.fail() || seed <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a positive integer.\n";
                    continue;
                }
                fillCarpetRandom(width, height, seed);
                break;
            }
            break;
        }
        else if (toupper(start) == 'I') {
            std::cout << "Input: ";
            std::cin >> input;
            try {
                fillCarpetInput(width, height, input);
                break;
            }
            catch (std::exception& e) {
                std::cout << " Error: " << e.what() << '\n';
            }
        }
    }
    printCarpet();
    std::string pattern;
    std::cout << "Enter the pattern to be searched: ";
    std::cin >> pattern;
    auto locations = searchPattern(pattern);
    std::cout << "Pattern found " << locations.size() << " times at the following locations: ";
    for (const auto& loc : locations) {
        std::cout << "(" << loc.first << ", " << loc.second << ")\n";
    }
}
