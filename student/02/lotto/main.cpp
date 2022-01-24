#include <iostream>
using namespace std;

unsigned int fact(int n)
    {
    if(n==0)
        return 1;
    if (n>0)
        return n*fact(n-1);
    }

int NCR(int n, int r)
{
    if (r == 0) return 1;

    if (r > n / 2) return NCR(n, n - r);

    long res = 1;

    for (int k = 1; k <= r; ++k)
    {
        res *= n - k + 1;
        res /= k;
    }

    return res;
}
int main(){
    int n;
    cout<<"Enter the total number of lottery balls: ";
    cin>>n;
    int r;
    cout<<"Enter the number of drawn balls: ";
    cin>>r;

    if (n <= 0 or r <= 0)
    {
        cout << "The number of balls must be a positive number" <<endl;
        return 0;
    }
    int result=NCR(n,r);
    cout<<"The probability of guessing all "<< r << " balls correctly is 1/" <<result<<endl;
    return 0;

}
