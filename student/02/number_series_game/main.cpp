#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    int count = 0;
    std::cin >> count;

    for (int number = 1; number <= count; ++number) {

        if ((number % 3) == 0 && (number % 7) == 0){
            std::cout << "zip boing" << std::endl;
        }
        else if ((number % 3) == 0) {
             std::cout << "zip" << std::endl;
        }
        else if ((number % 7) == 0){
            std::cout << "boing" << std::endl;
        }
        else {
            std::cout << number << std::endl;
        }

    }

    return 0;
}
