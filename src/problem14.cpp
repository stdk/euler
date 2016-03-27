#include <iostream>
#include <numeric>
#include <tuple>
#include <algorithm>

std::ostream& operator<<(std::ostream& output, const std::tuple<size_t, size_t> &state) {
    output << std::get<0>(state) << ": " << std::get<1>(state);
    return output;
}

class sequence_generator
{
    std::tuple<size_t, size_t> state; // (sequence_begin, sequence_length)
    
    size_t sequence_length(size_t n) {
        size_t len = 0;
        while((n = next_n(n)) != 1) len++;
        return len;
    }

    inline size_t next_n(size_t n) {
        if(n % 2 == 0) {
            return n / 2;   
        } else {
            return 3 * n + 1;   
        }
    }
    
    void next() {
        std::get<0>(state) += 1;
        std::get<1>(state) = sequence_length(std::get<0>(state));
    }
    
    void next(size_t n) {
        std::get<0>(state) = n;
        std::get<1>(state) = sequence_length(n);
    }
public:
    explicit sequence_generator(size_t v) noexcept {
        next(v);
    }    
    
    inline sequence_generator& operator=(const sequence_generator &other) noexcept {
        state = other.state;
        return *this;
    }
    
    inline bool operator==(const sequence_generator &other) noexcept {
        return state == other.state;
    }
    
    inline bool operator!=(const sequence_generator &other) noexcept {
        return state != other.state;
    }
    
    inline sequence_generator& operator++() noexcept {
        next();
        return *this;
    }
    
    inline sequence_generator operator++(int) noexcept {
    	sequence_generator tmp(*this);
        next();
        return tmp;
    }
    
    inline auto operator*() noexcept -> decltype(std::get<1>(state))  {
        return std::get<1>(state);
    }
    
    friend std::ostream& operator<<(std::ostream& output, const sequence_generator &g);
};

std::ostream& operator<<(std::ostream& output, const sequence_generator &g) {
    output << std::get<0>(g.state);
    return output;
}


int main() {
    auto longest_sequence = std::max_element(sequence_generator(1), sequence_generator(1000000));
    std::cout << longest_sequence << std::endl;
    
    return 0;
}
