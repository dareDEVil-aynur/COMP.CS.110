#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"

using namespace std;

class Book
{
public:
    Book();

    Book(string author, string title);

    ~Book();

    void print() const;

    void loan(Date& date);

    void advance();

    void renew();

    void give_back();

private:

    string title_;
    string author_;
    bool loaned_ = false;
    Date loan_date_;
    Date return_date_;

};

#endif // BOOK_HH
