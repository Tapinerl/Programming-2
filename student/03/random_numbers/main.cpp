#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here

    unsigned int seed;
    cout << "Enter a seed value: ";
    cin >> seed;
    cin.get();

    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(lower, upper);


    while (seed > 0){
        cout << "\nYour drawn random number is " << distr(gen) << endl;

        string jatko = "";
        cout << "Press q to quit or any other key to continue: ";
        getline(cin, jatko);

        if (jatko == "q") {
            break;
        }
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
