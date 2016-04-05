#include <string>
#include <cppformat/format.h>
#include <gmpxx.h>
#include <util.h>
#include <continued_fractions.h>

size_t D_search(uint32_t limit) {
	mpz_class max_x = 0;
	uint32_t max_x_D = 0;

	for(uint32_t D=2;D<=limit;++D) {
		auto perfect = perfect_square_root(D);
		if(perfect != -1) {
			continue;
		}

		auto A = approximation_iterator<mpz_class>(sqrt_terms_iterator(D));
		for(size_t i=0;;i++) {
			mpz_class value = A->p()*A->p() - A->q()*A->q()*D;
			if(value == 1) {
				if(A->p() > max_x) {
					std::tie(max_x,max_x_D) = std::make_tuple(A->p(),D);
				}
				break;
			}
			++A;
		}
	}

	return max_x_D;
}

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);

	if(argc != 2) {
		fmt::print("Usage: {} <limit>\n", argv[0]);
		return 1;
	}

	Measure measure;

	size_t D = D_search(std::stoi(argv[1]));

	auto passed = measure.passed();

	if(!util::test_mode()) {
		fmt::print("Processing toook {} ms\n", passed);
		fmt::print("D with the largest x in minimal solutions: ");
	}
	fmt::print("{}\n",D);

	return 0;
}
