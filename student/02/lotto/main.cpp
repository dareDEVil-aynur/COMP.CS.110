#include <iostream>

using namespace std;
// jees

unsigned long factorial(int num){
    unsigned long factorial = 1;
    unsigned long converted_num = num;
    for (unsigned long count = 2; count <= converted_num; ++count) {
        factorial = factorial * count;
    }
    return factorial;
}

int main()
{
    int balls = 1;
    int drawn_balls = 1;
    unsigned long rows = 1;

    cout << "Enter the total number of lottery balls: ";
    cin >> balls;

    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    if ((balls <= 0) or (drawn_balls <= 0)) {
        cout << "The number of balls must be a positive number." << endl;
    }else if (drawn_balls > balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }else {
        rows = factorial(balls)/(factorial(balls - drawn_balls)*factorial(drawn_balls));

        cout << "The probability of guessing all " << drawn_balls << " balls correctly is " << "1/" << rows << endl;
    }
    return EXIT_SUCCESS;
}
