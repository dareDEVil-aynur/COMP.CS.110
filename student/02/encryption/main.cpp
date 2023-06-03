#include <iostream>
#include <cctype>

using namespace std;


bool key_check(string characters) {
    string key_check;

    if (characters.length() < 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    }

    for (unsigned long number = 0; number < characters.length(); ++number) {
        int index = number;
        if (isalpha(characters.at(index)) == false or islower(characters.at(index)) == false) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }

        if (key_check.find(characters.at(index)) == string::npos) {
            key_check = key_check + (characters.at(index));
        }
    }

    if (key_check.length() != 26) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return false;
    }
    return true;
}

int main()
{
    cout << "Enter the encryption key: ";

    string key = " ";
    cin >> key;

    if (key_check(key) == false) {
         return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    string text = "";
    cin >> text;

    for ( unsigned long long number = 0; number < text.length(); ++number) {
        int index = number;
        if (isalpha(text.at(index)) == false or islower(text.at(index)) == false ) {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    string encrypted = "";

    for (unsigned long i = 0; i < text.length(); ++i) {
        int index = i;

        int acii_number = int(text.at(index));

        encrypted = encrypted + key.at(acii_number - 97); // acii number of a is 097
    }

    cout <<"Encrypted text: " << encrypted << endl;

    return 0;
}
