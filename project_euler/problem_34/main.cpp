#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <unordered_set>

using uint = unsigned int; 
using uint64 = unsigned long long int;

std::vector<uint64> factorials;

uint64 factorial(int n)
{
	if ((n < factorials.size()) && (n >= 0)) {
		return factorials[n];
	}
	else {
		if (n <= 1) {
			return 1; 
		}
		else {
			uint64 result = (n * factorial(n - 1));
			factorials.push_back(result); 
			return result;
		}
	}
}

int main() {

	factorials.push_back(1);
	factorials.push_back(1);
	std::cout << "9 factorial is: " << factorial(9) << std::endl;
	std::cout << "7 times 9! is: " << factorial(9)*7 << std::endl; // felső becslésre ez jó - ennél tovább nem is kell számolni: 
	uint64 allnum = 0; 

	for (int i = 3; i < 10000000; i++) {
		int sum = 0; 
		int current = i; 
		while (current != 0) {
			sum += factorial(current % 10); 
			current = current / 10;
		}
		if (sum == i) {
			std::cout << "Current number: " << sum << std::endl; 
			allnum += i; 
		}
	}
	std::cout << "Sum of all num: " << allnum << std::endl; 
}
