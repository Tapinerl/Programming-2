#include <iostream>

const int ASCII_MIN = 97;
const int ASCII_MAX = 122;
const int KEY_MAX_LENGHT = 26;

const std::string ERROR_LENGHT = "Error! The encryption key must contain 26 characters.";
const std::string ERROR_LOWER_CASE = "Error! The encryption key must contain only lower case characters.";
const std::string ERROR_ALPHABET = "Error! The encryption key must contain all alphabets a-z.";
const std::string ERROR_TEXT_LOWER_CASE = "Error! The text to be encrypted must contain only lower case characters.";

bool check_key_lenght(const std::string &key, const std::string &error_message);
bool check_all_lower_case(const std::string &key, const std::string &error_message);
bool check_all_alphabet(const std::string &key, const std::string &error_message);


int main()
{

    return 0;
}


bool check_key_lenght(const std::string &key, const std::string &error_message)
{

}

bool check_all_lower_case(const std::string &key, const std::string &error_message)
{

}

bool check_all_alphabet(const std::string &key, const std::string &error_message)
{

}
