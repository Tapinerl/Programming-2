#include <iostream>

using namespace std;

int main()
{   int temp = 0;
    cout << "Enter a temperature: ";
    cin >> temp;

    float fahre = temp * 1.8 +32;
    float cels = (temp - 32) /1.8;

    cout << temp << " degrees Celsius is " << fahre << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << cels << " degrees Celsius" << endl;
    // Write your code her

    return 0;
}
