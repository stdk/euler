#include <cppformat/format.h>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
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
    const auto &primes = PrimeNumbers(std::sqrt(limit)+1);

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

            if(util::debug_mode()) {
                auto i = std::accumulate(c.begin(),c.end(),(size_t)1,[](auto a, auto b) {
                    return a**b;
                });

                fmt::print("n[{:10}] D[{:10}] -> sum {}= {:10}\n",i,d,count % 2 ? "-" : "+",d*d);
            }

//            fmt::print("[");
//            for(auto i=c.rbegin();i!=c.rend();++i) {
//                fmt::print("{} ",**i);
//            }
//            fmt::print("] -> D[{}] -> sum {}= {} -> {}\n",d,count % 2 ? "-" : "+",d*d,sum);
        }
    }

    return (sum+1)/2 - 1;
}

uint64_t sieving_totient_method(uint64_t limit) {
    std::vector<uint32_t> t(limit/2+2);

    const uint32_t iteration_limit = limit / 2 + limit % 2;

    for(size_t i=1;i<=iteration_limit;++i) {
        t[i] = 2*i+1;
    }

    uint64_t sum = 0;
    for(uint32_t x=2;x<=limit;x*=2) {
        sum += x/2;
    }

    for(uint32_t i=1;i<iteration_limit;++i) {
        const uint32_t n = 2*i+1;
        if(t[i] == n) {
            t[i] = n - 1;
            for(uint32_t k=i+n;k<iteration_limit;k+=n) {
                t[k] /= n;
                t[k] *= (n - 1);
            }
        }
        sum += t[i];
        for(uint32_t x=n*2,d=1;x<=limit;x*=2,d*=2) {
            sum += d*t[i];
        }
    }

    if(util::debug_mode()) {
        for(uint32_t i=0;i<iteration_limit;++i) {
            fmt::print("{:2} ",i);
        }
        fmt::print("\n");

        for(uint32_t i=0;i<iteration_limit;++i) {
            fmt::print("{:2} ",2*i+1);
        }
        fmt::print("\n");

        for(uint32_t i=0;i<iteration_limit;++i) {
            fmt::print("{:2} ",t[i]);
        }
        fmt::print("\n");
    }

    return sum;
}

uint64_t sieving_moebius_method(uint64_t limit) {
    const uint64_t iteration_limit = limit/2 + limit % 2;

    std::vector<bool> prime(iteration_limit,true);
    std::vector<bool> odd(iteration_limit,false);
    std::vector<bool> squared(iteration_limit,false);

    uint64_t sum = limit*limit;

    uint64_t x2 = limit/2;
    sum -= x2*x2;
    if(util::debug_mode()) {
        fmt::print("n[{:10}] D[{:10}] -> sum {}= {:10}\n",2,x2,"-",x2*x2);
    }

    for(uint64_t i=1;i<iteration_limit;++i) {
        uint64_t n = 2*i + 1;
        if(prime[i]) {
            odd[i] = true;
            for(uint64_t k=i+n;k<iteration_limit;k+=n) {
                odd[k] = odd[k] ^ true;
                prime[k] = false;
            }

            uint64_t s = n*n;
            for(uint64_t k=(s-1)/2;k<iteration_limit;k+=s) {
                squared[k] = true;
            }
        }

        if(!squared[i]) {
            uint64_t x = limit/n;
            if(odd[i]) {
                sum -= x*x;
            } else {
                sum += x*x;
            }

            if(util::debug_mode()) {
                fmt::print("n[{:10}] D[{:10}] -> sum {}= {:10}\n",n,x,odd[i] ? "-" : "+",x*x);
            }

            if(2*n <= limit) {
                //inverse logic due to an additional factor of 2
                uint64_t x = limit/(2*n);
                if(!odd[i]) {
                    sum -= x*x;
                } else {
                    sum += x*x;
                }

                if(util::debug_mode()) {
                    fmt::print("n[{:10}] D[{:10}] -> sum {}= {:10}\n",2*n,x,!odd[i] ? "-" : "+",x*x);
                }
            }

        }
    }

    if(util::debug_mode()) {
        const char * format = "{:2} ";

        for(uint32_t i=1;i<iteration_limit;++i) {
            fmt::print(format,i);
        }
        fmt::print("\n");

        for(uint32_t i=1;i<iteration_limit;++i) {
            fmt::print(format,2*i+1);
        }
        fmt::print("\n");

        for(uint32_t i=1;i<iteration_limit;++i) {
            fmt::print(format,prime[i]);
        }
        fmt::print("\n");

        for(uint32_t i=1;i<iteration_limit;++i) {
            fmt::print(format,odd[i]);
        }
        fmt::print("\n");

        for(uint32_t i=1;i<iteration_limit;++i) {
            fmt::print(format,squared[i]);
        }
        fmt::print("\n");
    }

    return (sum+1)/2 - 1;
}

enum  optionIndex { UNKNOWN, HELP, MAX_DENOMINATOR, METHOD, REPEAT };
const option::Descriptor usage[] =
{
    {UNKNOWN,           0,"" , ""           ,Arg::None,    "USAGE: problem72 [options]\n\n"
                                                           "Options:" },
    {HELP,              0,"" , "help"       ,Arg::None,    "  --help  \tPrint usage and exit." },
    {MAX_DENOMINATOR,   0,"d", "denominator",Arg::Unsigned,"  --denominator, -l  \tSet max denominator. Required." },
    {METHOD,            0,"m", "method"     ,Arg::Unsigned,"  --method, -m  \tSelect method:\n"
                                                           "    0 - totient\n"
                                                           "    1 - moebius\n"
                                                           "    2 - sieving totient\n"
                                                           "    3 - sieving moebius\n"
                                                           "    At least one method must be selected.\n"
                                                           "    Multiple occurrences allowed."},
    {REPEAT,            0,"r", "repeat"     ,Arg::Unsigned,"  --repeat, -r  \tPerform calculation given number of times."
                                                           "    Defaults to 1. Setting another value suppresses program output." },
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

    if (argc == 0 || options[HELP]) {
        option::printUsage(CppFormatWriter(), usage);
        return 0;
    }

    if(!options[MAX_DENOMINATOR].count()) {
        fmt::print("Denominator option is required.\n");
        return 2;
    }

    if(!options[METHOD].count()) {
        fmt::print("At least one method must be selected.\n");
        return 2;
    }

    for (option::Option* opt = options[UNKNOWN]; opt; opt = opt->next()) {
        fmt::print("Unknown option: {}\n", opt->name);
    }

    const uint64_t limit = std::stoul(options[MAX_DENOMINATOR].last()->arg);
    const uint32_t repeat = (options[REPEAT].count() ? std::stoul(options[REPEAT].last()->arg) : 1);

    std::function<uint64_t(uint64_t)> methods[] = {
            totient_method,
            moebius_method,
            sieving_totient_method,
            sieving_moebius_method,
    };

    for (option::Option* opt = options[METHOD]; opt; opt = opt->next()) {
        const uint32_t method_index = std::stoul(opt->arg);
        if(method_index < sizeof(methods)/sizeof(*methods)) {
            if(repeat == 1) {
                auto result = methods[method_index](limit);
                if(!util::test_mode()) {
                    fmt::print("Method[{}] -> {}\n", method_index, result);
                } else {
                    fmt::print("{}\n",result);
                }
            } else {
                auto method = methods[method_index];
                uint64_t total = 0;
                for(uint32_t i=0;i<repeat;i++) {
                    total += method(limit);
                }
            }
        } else {
            fmt::print("There is no method with index {}\n", method_index);
        }
    }

    return 0;
}
