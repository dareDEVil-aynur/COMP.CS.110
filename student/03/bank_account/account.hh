#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
using namespace std;

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);
    string get_owner() const;

    float get_balance() const;

    void print() const;

    void set_credit_limit(float credit_limit);

    void save_money(float deposit);

    bool take_money(float withdrawal);

    void transfer_to(Account&(target), float deposit);



    // More methods

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    string owner_;
    bool has_credit_;

    float balance_ = 0;
    string iban_;
    float credit_limit_ = 0;

    // More attributes/methods
};

#endif // ACCOUNT_HH
