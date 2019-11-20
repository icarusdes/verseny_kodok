#include <iostream>
#include <deque>

using uint = unsigned int; 
using uint64 = unsigned long long int;

bool isPalindrome(uint number, uint base = 10) {
	std::deque<uint> numbers; 
	uint temp = number; 
	while (temp) {
		int remainder = temp % base; 
		numbers.push_back(remainder); 
		temp /= base; 
	}	
	while (numbers.size()) {
		if (numbers.size() == 1) 
			return true; 
		int front = numbers.front();
		int back = numbers.back(); 
		numbers.pop_front();
		numbers.pop_back(); 
		if (front != back)
			return false;
	}
	return true;
}

int main() {
	uint64 allnum = 0; 

	for (int i = 0; i < 1000000; i++) {
		if (isPalindrome(i, 10) && isPalindrome(i, 2)) {
			std::cout << "Palindrome and binary palindrome: " << i << std::endl;
			allnum += i;
		}
	}
	std::cout << "Sum of all num: " << allnum << std::endl; 
}
