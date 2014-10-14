#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <util.h>

std::vector<size_t> preprocess(size_t limit) {
	size_t max_power = log2(limit);
	std::vector<size_t> result;
	result.reserve(max_power);

	//std::cerr << "Need " << max_power*limit << " bits" << std::endl;
	std::vector<bool> presence(max_power*limit+1);

	size_t count = 0;
	for(size_t p=1;p<=max_power;p++) {
		for(size_t i=2;i<=limit;i++) {
			if(!presence[p*i]) {
				count++;
				presence[p*i] = true;
			}
		}
		result.push_back(count);
	}

	return result;
}

std::vector<size_t> generate_powers(size_t limit) {
	std::vector<size_t> powers_size;
	std::vector<bool> checked(limit+1);
	size_t barrier = sqrt(limit) + 1;
	for(size_t i=2;i<=barrier;i++) {
		if(!checked[i]) {
			size_t k = i;
			size_t size = 0;
			while(k <= limit) {
				checked[k] = true;
				k *= i;
				size++;
			}
			if(size > 1) powers_size.push_back(size);
		}
	}
	return powers_size;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		std::cerr << "Usage: problem29 <upper limit>" << std::endl;
		return 1;
	}

	const size_t limit = strtoul(argv[1],0,0);
	size_t unique_count = (limit - 2 + 1)*(limit - 2 + 1);

	auto elapsed = measure([&]() {
		auto powers = generate_powers(limit);
		auto pre = preprocess(limit);

		for(auto size: powers) {
			unique_count -= size * (limit - 2 + 1) - pre[size-1];
		}
	});

	std::cout << "Time elapsed: " << elapsed.count() << std::endl;
	std::cout << unique_count << std::endl;
	return 0;
}
