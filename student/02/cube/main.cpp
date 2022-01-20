#include <iostream>



int main()
{
    std::cout << "Enter a number: ";
    int number;
    std::cin >> number;

    int cube = number*number*number;
    if (number==0){
        std::cout <<"The cube of " << number << " is " << cube <<"."<< std::endl;
    }
    if (cube/number/number == number){
        std::cout <<"The cube of " << number << " is " << cube <<"."<< std::endl;
    }
    if (cube/number/number != number) {
        std::cout << "Error! The cube of " << number << " is not " << cube << "."<<std::endl;
    }
    return 0;
}
