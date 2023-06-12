#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();

}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

string Account::get_owner() const {
    return owner_;
}

float Account::get_balance() const {
    return balance_;
}

void Account::print() const {

    std::cout << owner_ << " : " << iban_ << " : " << get_balance() << " euros" << endl;
}

void Account::set_credit_limit(float credit_limit) {

    if (has_credit_) {
        credit_limit_ = credit_limit;
    } else {
        cout << "Cannot set credit limit: the account has no credit card" << endl;
    }
}

void Account::save_money(float deposit) {

    balance_ += deposit;

}

bool Account::take_money(float withdrawal) {

    if (balance_ - withdrawal < 0) {
        if (has_credit_) {
            if (balance_ - withdrawal > -1 * credit_limit_) {
                balance_ -= withdrawal;
                cout << withdrawal << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << endl;
                return true;
            } else {
                cout << "Cannot take money: credit limit overflow" << endl;
                return false;
            }
        } else {
            cout << "Cannot take money: balance underflow" << endl;
            return false;
        }
    } else {
        balance_ -= withdrawal;
        cout << withdrawal << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << endl;
        return true;
    }
}

void Account::transfer_to(Account&(target), float deposit) {

    if (take_money(deposit)) {

        target.save_money(deposit);

    } else {

        cout << "Transfer from " << iban_ << " failed" << endl;
    }
}










