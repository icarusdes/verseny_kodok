#include <iostream>
#include <vector>
#include <cmath>

using uint = unsigned int; 
using uint64 = unsigned long long int;

std::vector<uint> primes; 

bool isPrime(uint num ) {
	if (num == 1) 
		return false; 
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

bool isTruncatablePrime(uint num) {
	if (!isPrime(num))
		return false;
	else 
		primes.push_back(num);
	if (num < 20 )
		return false; 
	uint digits = ceil(log10(num)); 		
	for (uint i = 1; i <= digits; i++) {
		uint currentDivider = pow(10, i);
		uint num1 = num / currentDivider; 
		uint num2 = num % currentDivider; 
		if (!isPrime(num1) || !isPrime(num2)) 
			return false; 
	}
	return true; 	
}

int main() {
	uint truncatablePrimeCount = 0; 
	uint num = 3;
	uint truncatablePrimeSum = 0;

	primes.push_back(2);
	primes.push_back(3);
	while (truncatablePrimeCount < 11) {
		if (isTruncatablePrime(num)) {
			truncatablePrimeSum += num; 
			truncatablePrimeCount++; 
			std::cout << num << std::endl; 
		}
		num += 2; 
	}  

	std::cout << "Sum of numbers: " << truncatablePrimeSum << std::endl;
}
