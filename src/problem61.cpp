#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <tuple>
#include <cstdint>
#include <util.h>

typedef uint32_t (*figurate)(uint32_t);

uint32_t triangle(uint32_t n) {
	return n*(n+1)/2;
}

uint32_t square(uint32_t n) {
	return n*n;
}

uint32_t pentagonal(uint32_t n) {
	return n*(3*n-1)/2;
}

uint32_t hexagonal(uint32_t n) {
	return n*(2*n-1);
}

uint32_t heptagonal(uint32_t n) {
	return n*(5*n-3)/2;
}

uint32_t octagonal(uint32_t n) {
	return n*(3*n-2);
}

figurate figurates[] = {
	triangle,
	square,
	pentagonal,
	hexagonal,
	heptagonal,
	octagonal
};
const size_t figurates_size = sizeof(figurates)/sizeof(figurates[0]);

struct element {
	uint32_t value;
	uint32_t index;
};

class Sequence
{
	size_t m_size = 0;
	uint32_t data[figurates_size];
	uint32_t use = 0;
public:
	inline bool used(uint32_t index) {
		return use & (1 << index);
	}

	inline uint32_t usage() const {
		return use;
	}

	inline void push_back(element e) {
		data[m_size++] = e.value;
		use |= (1 << e.index);
	}

	inline Sequence operator+(element e) {
		Sequence new_sequence = *this;
		new_sequence.push_back(e);
		return new_sequence;
	}

	inline size_t size() const {
		return m_size;
	}

	inline size_t capacity() const {
		return figurates_size;
	}

	inline uint32_t* begin() {
		return data;
	}

	inline uint32_t* end() {
		return &data[m_size];
	}

	inline uint32_t* rbegin() {
		return &data[m_size-1];
	}

	inline uint32_t* rend() {
		return &data[-1];
	}
};

using FigurateTable = std::vector<std::vector<uint32_t>>;

FigurateTable generate_figurates(const uint32_t lower_bound, const uint32_t upper_bound) {
	std::vector<std::vector<uint32_t>> f(figurates_size);

	uint32_t numbers[figurates_size];
	for(uint32_t n=1,stop=0;!stop;n++) {
		stop = 1;
		for(uint32_t i=0;i<figurates_size;i++) {
			numbers[i] = figurates[i](n);
			if(numbers[i] < upper_bound) {
				stop = 0;
				if(numbers[i] > lower_bound) {
					f[i].push_back(numbers[i]);
				}
			}
		}
	}

	return f;
}

std::tuple<bool,Sequence> sequence_lookup(const FigurateTable &f,Sequence sequence) {
	if(sequence.size() == sequence.capacity()) {
		bool ok = *sequence.begin() / 100 == *sequence.rbegin() % 100;
		return std::make_tuple(ok,sequence);
	}

	uint32_t x = *sequence.rbegin();
	uint32_t base = (x % 100)*100;
	if(base < 10) return std::make_tuple(false,Sequence{});

	for(uint32_t i=0;i<sequence.capacity();i++) {
		if(!sequence.used(i)) {
			auto lower = std::lower_bound(f[i].begin(),f[i].end(),base);
			auto upper = std::lower_bound(f[i].begin(),f[i].end(),base+100);

			for(auto k=lower;k!=upper;k++) {
				auto result = sequence_lookup(f,sequence + element{*k,i});
				if(std::get<0>(result)) {
					return result;
				}
			}
		}
	}

	return std::make_tuple(false,Sequence{});
}

Sequence sequence_lookup(const FigurateTable &f) {
	bool ok;
	Sequence sequence;

	const auto &rarest = *f.rbegin();
	for(auto i=rarest.cbegin();i!=rarest.cend();i++) {
		std::tie(ok,sequence) = sequence_lookup(f,sequence + element{*i,static_cast<uint32_t>(f.size()-1)});

		if(ok) {
			return sequence;
		}
	}

	return sequence;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	Measure measure;

	const auto &f = generate_figurates(999,10000);

	auto passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Generation took " << passed << " ms" << std::endl;
	}

	measure.reset();

	auto sequence = sequence_lookup(f);

	if(!util::test_mode()) {
		for(auto x: sequence) {
			std::cout << x << " ";
		}
	}

	std::cout << std::accumulate(sequence.begin(),sequence.end(),0) << std::endl;

	passed = measure.passed();
	if(!util::test_mode()) {
		std::cout << "Lookup took " << passed << " ms" << std::endl;
	}

	return 0;
}
