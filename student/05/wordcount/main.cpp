#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

using DATA_STRUCT = std::map<std::string, std::set<int>>;

int read_input_file(DATA_STRUCT &rows_data, std::string filename);

void conver_to_output(DATA_STRUCT::const_iterator iter);

void print_out_data(DATA_STRUCT const &rows_data);

int main()
{
    DATA_STRUCT rows_data = {};

    std::cout << "Input file: ";
    std::string filename = "";
    std::getline(std::cin, filename);

    int status = read_input_file(rows_data, filename);
    print_out_data(rows_data);

    return status;
}

int read_input_file(DATA_STRUCT &rows_data, std::string filename){
    std::ifstream file(filename);
    if(!file){
        std::cout << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    std::string line = "";
    std::string word = "";
    int row_counter = 1;
    while(std::getline(file, line)){
        std::istringstream words(line);
        while(words >> word){
            if(rows_data.find(word) == rows_data.end()){
                rows_data.insert({word, {}});
            }
            rows_data.at(word).insert(row_counter);
        }
        row_counter++;
    }
    file.close();
    return EXIT_SUCCESS;
}

void conver_to_output(DATA_STRUCT::const_iterator iter){
    std::string key = iter ->first;
    std::set<int> row_numbers = iter ->second;

    std:: cout << key << " " << row_numbers.size() << ": ";
    for(std::set<int>::iterator iter = row_numbers.begin(); iter != row_numbers.end();iter++){
        std::cout << *iter;
        if((++iter) != row_numbers.end()){
            std::cout << ", ";
        }
        else {
            std::cout << std::endl;
        }
        iter--;
    }
}

void print_out_data(DATA_STRUCT const &rows_data){
    for(DATA_STRUCT::const_iterator iter = rows_data.begin(); iter != rows_data.end();iter++){
        conver_to_output(iter);
    }
}
