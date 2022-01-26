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
    std::string key = "";
    std::string text = "";

    std::cout << "Enter the encryption key: ";
    std::getline(std::cin, key);

    if(!check_key_lenght(key, ERROR_LENGHT) or !check_all_lower_case(key, ERROR_LOWER_CASE) or !check_all_alphabet(key, ERROR_ALPHABET))
    {
        return EXIT_FAILURE;
    }

    std::cout << "Enter the text to be encrypted: ";
    std::getline(std::cin, text);

    return 0;
}


bool check_key_lenght(const std::string &key, const std::string &error_message)
{
    if(key.length()== KEY_MAX_LENGHT)
    {
        return true;
    }
    std::cout << error_message << std::endl;
    return false;
}

bool check_all_lower_case(const std::string &key, const std::string &error_message)
{
    for(uint i = 0; i < key.length(); i++)
    {
        char c = key.at(i);
        if(c < ASCII_MIN && c > ASCII_MAX)
        {
            std::cout << error_message << std::endl;
            return false;
        }
    }
    return true;
}

bool check_all_alphabet(const std::string &key, const std::string &error_message)
{
    for(uint c = ASCII_MIN; c <= ASCII_MAX; c++)
    {
        if(key.find(c) == std::string::npos)
        {
            std::cout << error_message << std::endl;
            return false;
        }
    }
    return true;
}
