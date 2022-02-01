#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    iban_(""),
    owner_(owner),
    has_credit_(has_credit),
    balance_(0),
    credit_limit_(0)
{
    generate_iban();
}

void Account::print() const{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

void Account::set_credit_limit(int limit)
{
    credit_limit_ = limit;
}

void Account::save_money(int amount)
{
    balance_ += amount;
}

void Account::take_money(int amount)
{
    if(check_if_amount_ok(amount))
    {
        balance_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is "
                  << balance_ << " euros" << std::endl;
    }

}

void Account::transfer_to(Account &account, int amount)
{
    if(check_if_amount_ok(amount))
    {
        balance_ -= amount;
        account.save_money(amount);
        std::cout << amount << " euros taken: new balance of " << iban_ << " is "
                  << balance_ << " euros" << std::endl;
        return;
    }

    std::cout << "Transfer from " << iban_ << " failed" << std::endl;
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

bool Account::check_if_amount_ok(int amount)
{
    int new_balance = balance_ -amount;
    if (new_balance < 0)
    {
        if(!has_credit_)
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            return false;
        }

        if (new_balance + credit_limit_ < 0)
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            return false;
        }
    }

    return true;
}
