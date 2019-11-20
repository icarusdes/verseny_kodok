#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <unordered_set>

using uint = unsigned int; 
using uint64 = unsigned long long int;

int main() {

	std::unordered_set<uint> products;

	auto print = [](const uint & number) { std::cout << number << " "; };		
	std::vector<uint> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
	uint64 sum = 0; 
	std::sort(numbers.begin(), numbers.end());
	do {

		int number1 = numbers[0] * 10 + numbers[1]; 
		int number2 = numbers[2] * 100 + numbers[3] * 10 + numbers[4];
		int number3 = numbers[5] * 1000 + numbers[6] * 100 + numbers[7] * 10 + numbers[8];
		if ((number1 * number2 == number3) && products.insert(number3).second)   {
			std::cout << "type 1: ";			
			std::for_each(numbers.begin(), numbers.end(), print);
			std::cout << std::endl;
			sum += number3; 
		}		
		number1 = numbers[0]; 
		number2 = numbers[1] * 1000 + numbers[2] * 100 + numbers[3] * 10 + numbers[4];
		number3 = numbers[5] * 1000 + numbers[6] * 100 + numbers[7] * 10 + numbers[8];
		if ((number1 * number2 == number3) && products.insert(number3).second) {
			std::cout << "type 2: ";
			std::for_each(numbers.begin(), numbers.end(), print);
			std::cout << std::endl;
			sum += number3; 
		}
	} while(std::next_permutation(numbers.begin(), numbers.end()));
	std::cout << "Sum is: " << sum << std::endl; 
}
