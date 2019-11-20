#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/* 
Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product 
of 192 and (1,2,3)
The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 
918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an 
integer with (1,2, ... , n) where n > 1?

*/ 

using uint = unsigned int; 
using uint64 = unsigned long long int;

std::vector<uint> primes; 

int main() {
	auto print = [] (uint & n ) { std::cout << n << " ";}; 
	uint64 pandigitalnumbersum = 0;
	uint64 concat = 0;
	std::vector<uint> numbers; 
	for (uint i = 1; i <= 9999; i++) {		
		numbers.clear(); 
		concat = 0; 
		for (uint j = 1;;j++) {
			uint num = i * j; 			
			uint digits = ceil(log10(num)); 		
			uint currentMultiplier = pow(10, digits);
			concat = concat * currentMultiplier + num; 
			while (num > 0) {
				numbers.push_back(num % 10); 
				num /= 10; 
			}
			if (numbers.size() >= 9)
				break;
		}
		if (numbers.size() > 9)
			continue; 
		std::sort(numbers.begin(), numbers.end());
		if (numbers[0] == 0)
			continue; 
		auto last = std::unique(numbers.begin(), numbers.end()); 
    	numbers.erase(last, numbers.end()); 
		if (numbers.size() != 9)
			continue; 
		pandigitalnumbersum += i;
		std::cout << i << "\t"; 
		std::for_each(numbers.begin(), numbers.end(), print);
		std::cout << "\t" << concat << std::endl;
	}

	std::cout << "Sum of numbers: " << pandigitalnumbersum << std::endl;
}
