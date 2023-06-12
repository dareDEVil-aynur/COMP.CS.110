#include <cstdlib>
#include <iostream>

void swap(int& intiger1, int& intiger2) {

    int placeholder = intiger1;
    intiger1 = intiger2;
    intiger2 = placeholder;

}



#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
