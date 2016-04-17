#include <cppformat/format.h>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <primes.h>
#include <util.h>
#include <optionparser_customized.h>

uint32_t totient(uint32_t n, const PrimeNumbers &primes) {
    const auto &factors = factorize(n, primes, true);

    uint32_t t = 1;

    for(const auto &factor: factors) {
        t *= factor.prime - 1;
        for(auto i=factor.count-1;i;--i) {
            t *= factor.prime;
        }
    }

    return t;
}

template<class Container>
auto init_combination(const Container &values, size_t N) {
    std::vector<typename Container::const_iterator> c(N);

    std::iota(c.rbegin(),c.rend(),values.begin());
    if(*c.begin() >= values.end()) {
        c.clear();
    }

    return c;
}

template<class T, class V>
bool next_combination(T begin, T end, V value_end) {
    bool up = true;
    for(auto element=begin;element!=end;++element) {
        if(up) {
            ++*element;
            up = false;
        }

        if(*element == value_end) {
            up = true;
        } else {
            auto value = *element;
            size_t elements_left = value_end - value - 1;
            size_t positions_to_fill = element - begin;
            if(positions_to_fill > elements_left) {
                up = true;
            } else {
                for(auto e = element;e != begin;*--e = ++value);
                return true;
            }
        }
    }
    return false;
}

template<class T, class V, class Checker>
bool next_combination(T begin, T end, V value_end, Checker check) {
    bool up = true;
    for(auto element=begin;element!=end;++element) {
        if(up) {
            ++*element;
            up = false;
        }

        if(*element == value_end) {
            up = true;
        } else {
            auto value = *element;
            size_t elements_left = value_end - value - 1;
            size_t positions_to_fill = element - begin;
            if(positions_to_fill > elements_left) {
                up = true;
            } else {
                for(auto e = element;e != begin;*--e = ++value);

                if(check(begin,end)) {
                    return true;
                } else {
                    up = true;
                }
            }
        }
    }
    return false;
}

uint64_t totient_method(uint64_t limit) {
    const auto &primes = PrimeNumbers(std::sqrt(limit));

    uint64_t sum = 0;

    for(auto i=limit;i>1;--i) {
        sum += totient(i,primes);
    }

    return sum;
}

uint64_t moebius_method(uint64_t limit) {
    const auto &primes = PrimeNumbers(limit);

    uint64_t sum = limit*limit;

    auto check = [&limit](auto begin, auto end) -> bool {
        auto x = std::accumulate(begin,end,(size_t)1,[](auto p, auto v) {
            return p * *v;
        });
        return x <= limit;
    };

    for(size_t count=1;;++count) {
        auto c = init_combination(primes,count);
        if(!c.size()) {
            break;
        }

        if(!check(c.begin(),c.end())) {
            break;
        }

        for(bool ok=true;ok;ok=next_combination(c.begin(),c.end(),primes.end(),check)) {

            auto d = std::accumulate(c.begin(),c.end(),limit,[](auto p, auto x) {
                return p / *x;
            });

            if(count % 2) {
                sum -= d*d;
            } else {
                sum += d*d;
            }

            /*
            fmt::print("[");
            for(auto i=c.rbegin();i!=c.rend();++i) {
                fmt::print("{} ",**i);
            }
            fmt::print("] -> D[{}] -> sum {}= {} -> {}\n",d,count % 2 ? "-" : "+",d*d,sum);
            */
        }
    }

    return (sum+1)/2 - 1;
}

enum  optionIndex { UNKNOWN, HELP, MAX_DENOMINATOR, CHECK };
const option::Descriptor usage[] =
{
    {UNKNOWN,           0,"" , ""           ,Arg::None,    "USAGE: problem72 [options]\n\n"
                                                           "Options:" },
    {HELP,              0,"" , "help"       ,Arg::None,    "  --help  \tPrint usage and exit." },
    {MAX_DENOMINATOR,   0,"d", "denominator",Arg::Numeric, "  --denominator, -l  \tSet max denominator. Required." },
    {CHECK,             0,"c", "check"      ,Arg::None   , "  --check, -c  \tPerform self-check." },
    {UNKNOWN,           0,"" ,  ""          ,Arg::None   , "\nExamples:\n"
                                                           "  problem72 --denominator 1000\n"
                                                           "  problem72 -d 1000000 -c\n" },
    {0,0,0,0,0,0}
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error()) {
        return 1;
    }

    if (options[HELP] || !options[MAX_DENOMINATOR].count() || argc == 0) {
        option::printUsage(CppFormatWriter(), usage);
        return 0;
    }

    const uint64_t limit = std::stoul(options[MAX_DENOMINATOR].last()->arg);

    auto sum = moebius_method(limit);

    if(options[CHECK].count()) {
        auto sum2 = totient_method(limit);
        if(sum == sum2) {
            fmt::print("Check succeeded.\n");
        } else {
            fmt::print("Totient method returned {}\n",sum2);
        }
    }

    fmt::print("{}\n", sum);

    return 0;
}
