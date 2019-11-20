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
	uint64 nominator = 1; 
	uint64 denominator = 1; 
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 9; k++) {
				int smaller = j * 10 + i; 
				int bigger = i * 10 + k; 
				if ( (bigger / (float) smaller > 1) && ( (float) bigger / smaller == (float) k / j) ) {
					// maradék nélkül osztható: 
					std::cout << smaller << "/" << bigger << std::endl; 
					nominator *= smaller; 
					denominator *= bigger;
				}
			}
		}
	}
	std::cout << nominator << "/" << denominator << std::endl;
	std::cout << 1 << "/" << denominator / nominator << std::endl;
}
