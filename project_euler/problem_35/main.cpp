#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <unordered_set>

using uint = unsigned int; 
using uint64 = unsigned long long int;

std::vector<uint> primes; 

bool isPrime(uint num ) {
	float stop = num; 
	uint current = primes[0];
	uint primesNumber = primes.size(); 
	for (uint i = 0; i < primesNumber && current < stop; i++) {
		current = primes[i]; 
		if (num % current == 0) 
			return false; 
		stop = num / (float) current; 
	}
	return true;
}

int main() {
	uint circularPrimeCounter = 0; 
	primes.push_back(2);
	primes.push_back(3);

	auto print = [](uint & num ) { std::cout << num << " ";};
	
	for (uint i = 5; i < 1000000; i += 2) {
		if (isPrime(i)) { 
			primes.push_back(i); 
			// ekkor kell legenerálni az összes alternatívát
			int temp = i; 
			bool prime = true; 
			std::deque<uint> numbers; 
			while (temp) {
				int remainder = temp % 10; 
				if (remainder)
					numbers.push_back(remainder); 
				else {
					prime = false;
					break;
				}
				temp /= 10; 
			}
			if (!prime)
				continue; 			
			for (int k = 0; k < numbers.size(); k++) {
				int firstNum = numbers.front(); 
				numbers.pop_front(); 
				numbers.push_back(firstNum);
				int num = 0; 
				for (int j = (numbers.size() - 1); j >= 0; j--) {
					num = num * 10 + numbers[j]; 
				}
				if (!isPrime(num)) {
					prime = false;
					break;					
				}
			}
			if (!prime)
				continue; 
			std::cout << "Circular prime: " << i << std::endl;
			circularPrimeCounter++; 
		}
	}
	std::cout << "Numbers of circular primes below 1000 000: " << circularPrimeCounter << std::endl;
}
