#include <cppformat/format.h>
#include <optionparser_customized.h>
#include <cstdint>
#include <tuple>
#include <vector>
#include <fraction.h>
#include <primes.h>
#include <util.h>

typedef Fraction<uint32_t> fraction_t;

auto fraction_bounds(fraction_t a, fraction_t b, uint32_t max_denominator) {
    std::vector<std::tuple<uint32_t,uint32_t,uint32_t>> fractions;

    auto P = [&](auto upper_bound, auto q) {
        auto x = upper_bound.p()*q-1;
        auto y = upper_bound.q();

        auto p = x/y;

        for(;p && gcd(p,q) != 1;--p);

        return p;
    };

    for(auto q=max_denominator;q>1;--q) {
        auto p_min = P(a, q);
        auto p_max = P(b ,q);

        if(p_min && p_max && p_min < p_max) {
            fractions.push_back(std::make_tuple(p_min,p_max,q));
        }
    }

    return fractions;
}

auto count_fractions(fraction_t a, fraction_t b, uint32_t max_denominator) {
    size_t count = 0;

    auto P = [&](auto upper_bound, auto q) {
        auto x = upper_bound.p()*q-1;
        auto y = upper_bound.q();
        return x/y;
    };

    for(auto q=max_denominator;q>1;--q) {
        auto p_min = P(a, q);
        auto p_max = P(b ,q);

        if(q == a.q() && p_max <= a.p()) {
            --p_max;
        }

//        if(!util::test_mode()) {
//            fmt::print("{}[{}-{}]: ", q,p_max,p_min);
//        }

        for(auto p=p_max;p && p > p_min;--p) {
            if(gcd(p,q) == 1) {
                ++count;
//                if(!util::test_mode()) {
//                    fmt::print("{} ", p);
//                }
            }
        }

//        if(!util::test_mode()) {
//            fmt::print("\n");
//        }
    }

    return count;
}

enum  optionIndex { UNKNOWN, HELP, MAX_DENOMINATOR, LOWER_BOUND, UPPER_BOUND };
const option::Descriptor usage[] =
{
    {UNKNOWN,           0,"" , ""           ,Arg::None,    "USAGE: problem73 [options]\n\n"
                                                           "Options:" },
    {HELP,              0,"" , "help"       ,Arg::None,    "  --help  \tPrint usage and exit." },
    {MAX_DENOMINATOR,   0,"d", "denominator",Arg::Numeric, "  --denominator, -d  \tSet max denominator. Required." },
    {LOWER_BOUND,       0,"a", "lower_bound",Arg::Fraction,"  --upper_bound, -a  \tSet lower bound. Required." },
    {UPPER_BOUND,       0,"b", "upper_bound",Arg::Fraction,"  --lower_bound, -b  \tSet upper bound. Required." },
    {UNKNOWN,           0,"" ,  ""          ,Arg::None,    "\nExamples:\n"
                                                           "  problem73 --denominator 1000 -a 1/3 -b 2/3\n"
                                                           "  problem73 -d 12000 -a 1/3 -b 1/2\n" },
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

    if (argc == 0 || options[HELP] || !options[MAX_DENOMINATOR].count()) {
        option::printUsage(CppFormatWriter(), usage);
        return 0;
    }

    const uint32_t max_denominator = std::stoul(options[MAX_DENOMINATOR].last()->arg);
    const auto a = Fraction<uint32_t>::read(options[LOWER_BOUND].last()->arg);
    const auto b = Fraction<uint32_t>::read(options[UPPER_BOUND].last()->arg);

    if(!util::test_mode()) {
        fmt::print("Max denominator: {}\n", max_denominator);
        fmt::print("Lower bound: {}\n", a);
        fmt::print("Upper bound: {}\n", b);
    }

    auto count = count_fractions(a,b,max_denominator);

    fmt::print("{}\n", count);

    return 0;
}
