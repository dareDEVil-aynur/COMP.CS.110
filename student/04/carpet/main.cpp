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
#include <cctype>
#include <limits>
#include <random>

enum Color {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};
const char* ColorChar = "RGBYW";

std::vector<std::vector<Color>> carpet;
std::vector<Color> pattern;

Color charToColor(char c) {
    for (int i = 0; i < NUMBER_OF_COLORS; i++) {
        if (toupper(c) == ColorChar[i]) {
            return static_cast<Color>(i);
        }
    }
    throw std::invalid_argument("Unknown color.");
}

void printCarpet() {
    for (auto row : carpet) {
        for (auto c : row) {
            std::cout << ' ' << ColorChar[c];
        }
        std::cout << '\n';
    }
}

void fillCarpetRandom(int width, int height, int seed) {
    std::default_random_engine rand_gen(seed);
    std::uniform_int_distribution<int> distribution(0, NUMBER_OF_COLORS-1);
    carpet.resize(height, std::vector<Color>(width));
    for (auto& row : carpet) {
        for (auto& c : row) {
            c = static_cast<Color>(distribution(rand_gen));
        }
    }
}

void fillCarpetInput(int width, int height, const std::string& input) {
    if (static_cast<int>(input.size()) != width * height) {
        throw std::invalid_argument("Wrong amount of colors.");
    }
    carpet.resize(height, std::vector<Color>(width));
    int i = 0;
    for (auto& row : carpet) {
        for (auto& c : row) {
            c = charToColor(input[i++]);
        }
    }
}

int findPattern() {
    int matches = 0;
    for (std::size_t i = 0; i < carpet.size() - 1; i++) {
        for (std::size_t j = 0; j < carpet[i].size() - 1; j++) {
            if (carpet[i][j] == pattern[0] && carpet[i][j + 1] == pattern[1] &&
                carpet[i + 1][j] == pattern[2] && carpet[i + 1][j + 1] == pattern[3]) {
                std::cout << " - Found at (" << j + 1 << ", " << i + 1 << ")\n";
                matches++;
            }
        }
    }
    return matches;
}

int main() {
    int width, height, seed;
    char start;
    std::string input;

    std::cout << "Enter carpet's width and height: ";
    std::cin >> width >> height;
    if (width < 2 || height < 2) {
        std::cout << " Error: Carpet cannot be smaller than pattern.\n";
        return EXIT_FAILURE;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Select start (R for random, I for input): ";
        std::cin >> start;
        start = toupper(start);
        if (start == 'R') {
            while (true) {
                std::cout << "Enter seed value: ";
                if (std::cin >> seed && seed >= 1 && seed <= 20){
                    fillCarpetRandom(width, height, seed);
                    break;
                } else if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << " Error: You must enter a valid integer.\n";
                } else {
                    std::cout << " Error: Wrong seed value.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            break;
        } else if (start == 'I') {
            std::cin.ignore();
            std::cout << "Input: ";
            getline(std::cin, input);
            try {
                fillCarpetInput(width, height, input);
                break;
            } catch (std::exception& e) {
                std::cout << " Error: " << e.what() << '\n';
            }
        }
    }

    printCarpet();

    while (true) {
        std::cout << "Enter 4 colors, or q to quit: ";
        std::cin >> input;
        if (toupper(input[0]) == 'Q') {
            return EXIT_SUCCESS;
        } else if (input.size() != 4) {
            std::cout << " Error: Wrong amount of colors.\n";
        } else {
            try {
                pattern.clear();
                for (char c : input) {
                    pattern.push_back(charToColor(c));
                }
                int matches = findPattern();
                std::cout << " = Matches found: " << matches << '\n';
            } catch (std::exception& e) {
                std::cout << " Error: " << e.what() << '\n';
            }
        }
    }
}


