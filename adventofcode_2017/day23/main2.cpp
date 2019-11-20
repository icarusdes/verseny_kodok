#include <iostream>
#include <boost/regex.hpp>
#include <fstream>
#include <string> 
#include <map>

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool isPrime(long long int num) {
    if (num % 2 == 0) 
        return true; 
    long long int max = sqrt(num); 
    for (long long int i = 3; i < max; i += 2) {
        if (num % i == 0) 
            return true; 
    }
    return false; 
}

int main() {
    long long int a = 1; 
    long long int b = 0; 
    long long int c = 0; 
    long long int d = 0; 
    long long int e = 0; 
    long long int f = 0; 
    long long int g = 0; 
    long long int h = 0;
    b = 57;
    c = b;

    if (a != 0) {
        b *= 100; // 9300
        b += 100000; // 109300
        c = b; // 109300
        c += 17000; // 126300
    }

    do {
        f = 1;
        d = 2;

        if (isPrime(b) == true)
            f = 0;

        if (f == 0)
            h++;

        g = b;
        if (b != c)
            b += 17;
    } while (g != c);
    std::cout << "Value of register h is " << h << std::endl;

    return 0; 
}