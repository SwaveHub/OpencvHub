#include <iostream>
#include <windows.h>
using namespace std;

int main(void)
{
    long long a, b, gcd, lcm;
    long long num1, num2;

    cin >> a >> b;
    long s = GetTickCount64();
    num1 = a;
    num2 = b;

    if (num1 == 0) num1 = num2;
    else if (num2 == 0) num2 = num1;

    while (num1 != num2) {
        if (num1 > num2)
            num1 -= num2;
        else
            num2 -= num1;
    }
    gcd = num1;

    if (gcd != 0) lcm = a * b / gcd;
    else lcm = 0;

    cout << gcd << ' ' << lcm << endl;
    long end = GetTickCount64();
    printf("time:%ld", end - s);
}