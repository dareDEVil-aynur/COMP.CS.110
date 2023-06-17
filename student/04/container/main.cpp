#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count) {

    int new_integer = 0;
    for(int i = 0; i < count; ++i) {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}


bool same_values(const std::vector< int > ints) {

    for(unsigned long i = 0; i < ints.size() - 1; ++i) {
        if (ints.at(i) != ints.at(i+1) ) {
            return false;
        }
    }
    return true;
}


bool is_ordered_non_strict_ascending(const std::vector< int > ints) {

    for(unsigned long i = 0; i < ints.size() - 1; ++i) {
        if (ints.at(i) > ints.at(i+1)) {
                return false;
        }
    }
    return true;
}


bool is_arithmetic_series(const std::vector< int > ints) {

    for(unsigned long i = 0; i < ints.size() - 3; ++i) {
        if (ints.at(i)-ints.at(i+1) != ints.at(i+2)-ints.at(i+3)) {
            return false;
        }
    }
    return true;
}


bool is_geometric_series(const std::vector< int > ints) {

    for(unsigned long i = 0; i < ints.size() - 3; ++i) {
        if (ints.at(i) != 0 and ints.at(i+1) != 0 and ints.at(i+2) != 0 and ints.at(i+3) != 0) {
            float num1 = ints.at(i);
            float num2 = ints.at(i+1);
            float num3 = ints.at(i+2);
            float num4 = ints.at(i+3);
            if (num1/num2 != num3/num4) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
