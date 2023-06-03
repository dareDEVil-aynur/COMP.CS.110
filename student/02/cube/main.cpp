#include <iostream>

using namespace std;
int main()
{
    cout << "Enter a positive number: ";

    int product = 0;
    cin >> product;

    int final_factor1 = 1;
    int final_factor2 = product;

    if (product > 0){
        for (int number = 2; number <= (product / 2); ++number) {
            if ((product % number) == 0){
                if (abs(number - product/number) < abs(final_factor1 - final_factor2)){
                    final_factor1 = number;
                    final_factor2 = product/number;
                }
            }
        }
        cout << product << " = " << final_factor1 << " * " << final_factor2 << endl;
    } else{
        cout << "Only positive numbers accepted" << endl;
    }




    return 0;
}
