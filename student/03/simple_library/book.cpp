#include "book.hh"
#include <iostream>

Book::Book(const std::string& author, const std::string& book_name):
    author_(author),
    book_name_(book_name),
    loan_date_(Date()),
    return_date_(Date()),
    available_(true)



{

}

void Book::print() const
{
    std::cout << author_<<" : " << book_name_ << std::endl;
    if(available_)
    {
        std::cout << "- available" << std::endl;
        return;
    }

    std::cout << "- loaned: ";
    loan_date_.print();
    std::cout << "- to be returned: ";
    return_date_.print();
}

void Book::loan(Date const &date)
{
    if(!available_)
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }
    loan_date_ = date;
    return_date_ = loan_date_;
    return_date_.advance(28);
    available_ = false;
}

void Book::renew()
{
    if(available_)
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }
    return_date_.advance(28);
}

void Book::give_back()
{
    available_ = true;
}
