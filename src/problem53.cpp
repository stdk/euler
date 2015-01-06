#include <iostream>
#include <util.h>

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	const size_t limit = 100;
	const size_t bound = power<10,6>::value;

	Measure measure;

	size_t total_numbers = limit*(limit+1)/2;
	const size_t start = 23;
	total_numbers -= start*(start-1)/2;
	for(size_t i=start;i<=limit;i++) {
		total_numbers -= 1;
		for(size_t n=i,k=1;n<=bound;n=n*(i-k)/(k+1),k++) {
			std::cout << n << " ";
			total_numbers -= 2;
		}
		std::cout << " | " << total_numbers << std::endl;
	}

	auto passed = measure.passed();
	std::cout << "Search for " << total_numbers << " took " << passed << " ms" << std::endl;
	return 0;
}
