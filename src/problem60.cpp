#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstdint>
#include <primes.h>
#include <util.h>

using Group = std::set<prime_t>;
using UGroup = std::unordered_set<prime_t>;

struct affix_t {
    affix_t(prime_t v):value(v) {}

    prime_t value;
};

struct prefix_t : affix_t {
    using affix_t::affix_t;
};

struct suffix_t : affix_t {
    using affix_t::affix_t;
};

struct prime_stats_t {
    Group prefixes;
    Group suffixes;

    bool valid() const {
        return prefixes.size() >= 4 && suffixes.size() >= 4;
    }

    prime_stats_t& operator+=(prefix_t a) {
        prefixes.insert(a.value);
        return *this;
    }

    prime_stats_t& operator+=(suffix_t a) {
        suffixes.insert(a.value);
        return *this;
    }

    std::ostream& write(std::ostream &os) const {
        return os << "[" << prefixes.size() << "," << suffixes.size() << "]";
    }
};

std::ostream& operator<<(std::ostream &os, const prime_stats_t &o) {
    return o.write(os);
}


template<class Stats, class T>
void update_entry(prime_t key, T value, Stats &stats) {
    auto i = stats.find(key);
    if(i == stats.end()) {
        stats[key] += value;
    } else {
        i->second += value;
    }
}

template<class Primes,class Stats>
void split(prime_t prime,const Primes &primes,Stats &stats, const prime_t limit) {
    for(prime_t order = 10;order<prime;order*=10) {
        prime_t prefix = prime/order;
        prime_t suffix = prime%order;
        if(prefix < limit &&
           suffix < limit &&
           primes[prefix] && primes[suffix] &&
           num_order(suffix) == order &&
           primes[suffix*num_order(prefix) + prefix]) {
            update_entry(prefix,suffix_t(suffix),stats);
            update_entry(suffix,prefix_t(prefix),stats);
        }
    }
}

template<class Vector>
void erase_from_sorted_vector(Vector &vector,const typename Vector::value_type &value) {
    auto i = std::lower_bound(vector.begin(),vector.end(),value);
    if(i != vector.end() && *i == value) {
        vector.erase(i);
    }
}

template<class Candidates, class Primes>
void next_front(const std::set<Group> &curr_front,
                      std::set<Group> &next_front,
                      const Candidates &candidates,
                      const Primes &primes) {
    next_front.clear();
    for(auto group: curr_front) {
        for(auto p: group) {
            auto c = candidates.find(p);
            //if(c == candidates.end()) continue;

            for(auto k: c->second) {
                if(group.find(k) != group.end()) continue;

                bool satisfies = true;
                for(auto i=group.begin();i!=group.end();++i) {
                    if(*i == p) continue;
                    prime_t a = k*num_order(*i) + *i;
                    prime_t b = *i*num_order(k) + k;
                    if(!primes[a] || !primes[b]) {
                        satisfies = false;
                    }
                }
                if(satisfies) {
                    std::set<prime_t> new_group = group;
                    new_group.insert(k);
                    next_front.insert(std::move(new_group));
                }
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const std::vector<prime_t> &v) {
    if(!v.size()) return os << "[]";

    os << "[" << *v.begin();
    for(auto c = v.begin()+1;c!=v.end();++c) {
        os << "," << *c;
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<prime_t> &v) {
    if(!v.size()) return os << "[]";
    os << "[" << *v.begin();
    for(auto c = ++v.begin();c!=v.end();++c) {
        os << "," << *c;
    }
    os << "]";
    return os;
}



template<class Primes>
bool simple_check(prime_t first, const std::vector<prime_t> &group, const Primes &primes) {
    const uint32_t mask = (1 << group.size()) - 1;

    const size_t n = 4;
    prime_t g[4] = { first };

    for(uint32_t bits = (1 << n) - 1,ok=1;ok;ok=next_combination(bits,mask)) {
        prime_t *pg = g;
        uint32_t x = bits;
        while(uint32_t k = __builtin_ffs(x)) {
            *pg++ = group[k-1];
            x &= ~(1 << (k-1));
        }
        bool satisfies = true;
        for(size_t i=0;i<n;i++) {
            for(size_t j=i+1;j<n;j++) {
                prime_t a = g[i]*num_order(g[j]) + g[j];
                prime_t b = g[j]*num_order(g[i]) + g[i];
                if(!primes[a] || !primes[b]) {
                    satisfies = false;
                }
            }
        }
        if(satisfies) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    const size_t order = 8;
    const prime_t limit = power<10,order>::value;

    Measure measure;

    const auto &primes = PrimeNumbers(limit);

    auto passed = measure.passed();
    if(!util::test_mode()) {
        std::cout << "Prime generation took " << passed << " ms" << std::endl;
    }

    measure.reset();

    std::unordered_map<prime_t,prime_stats_t> stats;
    std::unordered_map<prime_t,std::vector<prime_t>> candidates;

    for(auto i=primes.begin();i!=primes.end();++i) {
        split(*i,primes,stats,power<10,order/2>::value);
    }
    //13,5197,5701,6733,8389
    std::vector<prime_t> erased;
    for(auto i=stats.begin();i!=stats.end();) {
        if(i->second.valid()) {
            auto &entry = i->second;

            std::vector<prime_t> intersection(std::min(entry.prefixes.size(),entry.suffixes.size()));
            auto end = std::set_intersection(entry.prefixes.begin(),entry.prefixes.end(),
                                             entry.suffixes.begin(),entry.suffixes.end(),
                                             intersection.begin());
            intersection.resize(end - intersection.begin());
            if(intersection.size() >= 4) {
                if(intersection.size() > 0) {
                    candidates[i->first] = std::move(intersection);
                    ++i;
                } else {
                    bool ok = simple_check(i->first,intersection,primes);
                    if(ok) {
                        std::cout << "OK !!!" << std::endl;
                        exit(0);
                    } else {
                        erased.push_back(i->first);
                        i = stats.erase(i);
                    }
                }
            } else {
                erased.push_back(i->first);
                i = stats.erase(i);
            }
        } else {
            erased.push_back(i->first);
            i = stats.erase(i);
        }
    }
    //std::cout << "Candidates: " << candidates.size() << std::endl;

    while(erased.size()) {
        for(auto p: erased) {
            for(auto &i: candidates) {
                erase_from_sorted_vector(i.second,p);
            }
        }

        erased.clear();
        for(auto i=candidates.begin();i!=candidates.end();) {
            if(i->second.size() >= 4) {
                ++i;
            } else {
                erased.push_back(i->first);
                i = candidates.erase(i);
            }
        }
        //std::cout << "Candidates: " << candidates.size() << std::endl;
    }

    std::set<Group> front_a;
    std::set<Group> front_b;
    for(auto i=candidates.begin();i!=candidates.end();i++) {
        front_a.clear();

        front_a.insert(Group({i->first}));
        for(size_t n=0;front_a.size() && n<4;n++) {
            next_front(front_a,front_b,candidates,primes);
            std::swap(front_a,front_b);
        }
        if(front_a.size()) {
            for(auto chain: front_a) {
                uint32_t sum = std::accumulate(chain.begin(),chain.end(),0);
                if(!util::test_mode()) {
                    std::cout << i->first << chain << " => " << sum << std::endl;
                }
                std::cout << sum << std::endl;
            }
            break;
        }
    }

    passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Search took " << passed << " ms" << std::endl;
    }

    return 0;
}
