#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"


class Book
{
public:
    Book(const std::string& author, const std::string& book_name);

    void print() const;
    void loan(Date const &date);
    void renew();
    void give_back();

private:
    std::string author_;
    std::string book_name_;
    Date loan_date_;
    Date return_date_;
    bool available_;
};

#endif // BOOK_HH
