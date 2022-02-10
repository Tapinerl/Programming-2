#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string const &line, const char separator, bool ignore_empty = false)
{
    std::vector<std::string> strings;
    std::string word = "";
    for(const char c : line)
    {
        if(c==separator)
        {

            if(word.empty() && ignore_empty)
            {
                continue;
            }

            strings.push_back(word);
            word.clear();
        }

        else
        {
            word += c;
        }

    }
    strings.push_back(word);
    return strings;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
