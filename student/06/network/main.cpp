#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

using NET = std::map<std::string, std::vector<std::string>>;

void store(std::string key, std::string value, NET &network){
    if(network.find(key) == network.end()){
        network.insert({key, {}});
    }
    network.at(key).push_back(value);
}

void print(std::string key, NET const &network, std::string identation = ""){
    if(network.find(key) == network.end() or network.at(key).empty()){
        std::cout <<identation <<  key << std::endl;
    }
    else {
        std::cout << identation << key << std::endl;
        std::vector<std::string>::const_iterator iter = network.at(key).begin();
        for(; iter != network.at(key).end(); iter++){
            print(*iter, network, identation + "..");
        }

    }
}

int depth(std::string key, NET const &network){
    int max_depth = 0;
    if(network.find(key) != network.end()){
        for(std::string id : network.at(key)){
            if(depth(id, network) > max_depth){
                max_depth = depth(id, network);
            }
        }
    }
    return max_depth + 1;
}

int count(std::string key, NET const &network){
    if(network.find(key) == network.end() or network.at(key).empty()){
        return 0;
    }
    else {
        std::vector<std::string>::const_iterator iter = network.at(key).begin();
        int size_at_level = network.at(key).size();
        for(; iter != network.at(key).end(); iter++){
            size_at_level += count(*iter, network);
        }
        return size_at_level;
    }
}

int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> network = {};


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            store(id1, id2, network);


        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(id, network);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(id, network) << std::endl;


        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << depth(id, network) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
