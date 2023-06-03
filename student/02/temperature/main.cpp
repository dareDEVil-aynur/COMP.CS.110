#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    double temperature = 0;
    cin >> temperature;
    double temp_fahrenheit = temperature * 1.8 +32;
    double temp_celsius = (temperature-32)/1.8;

    cout << temperature << " degrees Celsius is " << temp_fahrenheit << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << temp_celsius << " degrees Celsius" << endl;


    return 0;
}
