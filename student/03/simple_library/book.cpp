#include "date.hh"
#include "book.hh"
#include <iostream>
#include <string>

using namespace std;

Book::Book():
    title_(""), author_("")
{
}

Book::Book(string author, string title):
    title_(title), author_(author)
{

}

Book::~Book(){
}

void Book::print() const {

    cout << author_ << " : " << title_ << endl;

    if (loaned_ == false) {
        cout << "- available" << endl;
    } else {
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        return_date_.print();

    }

}

void Book::loan(Date& date) {

    if (loaned_) {
        cout << "Already loaned: cannot be loaned" << endl;
    } else {
        loaned_ = true;
        loan_date_ = date;
        return_date_ = loan_date_;
        return_date_.advance(28);
    }
}

void Book::renew() {

    if (loaned_) {

        return_date_.advance(28);

    } else {

        cout << "Not loaned: cannot be renewed" << endl;
    }



}

void Book::give_back() {

    loaned_ = false;

}
