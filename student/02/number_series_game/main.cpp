#include <iostream>
using namespace std;

int main()
{
    int number;
    cout << "How many numbers would you like to have? ";
    cin >> number;

    for (int i=1; i<=number;i++)
    {
        if (i % 3 == 0)
        {
            cout <<"zip"<< "\n";
        }
        else {
            cout << i << "\n";
        }

    }


    return 0;
}
