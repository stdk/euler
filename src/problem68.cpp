#include <cppformat/format.h>
#include <cstdint>
#include <array>
#include <bitset>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <util.h>
#include <set>

template<class Container, class X = decltype(std::declval<Container>().begin())>
auto operator<<(std::ostream &os, const Container &c)
-> typename std::enable_if<!std::is_same<Container,std::string>::value,std::ostream&>::type {
    for(auto i=c.begin();i!=c.end();++i) {
        os << fmt::format("{}{}",*i,i==c.end()-1 ? "" : " ");
    }
    return os;
}

template<class,class>
struct extract_helper {

};

template<class SrcType, size_t SrcSize, class IdxType,size_t IdxSize>
struct extract_helper<std::array<SrcType,SrcSize>,std::array<IdxType,IdxSize>> {
    typedef std::array<SrcType,IdxSize> Result;
    typedef std::array<IdxType,IdxSize> Index;
    typedef std::array<SrcType,SrcSize> Source;

    const Index &idx;

    extract_helper(Index _idx):idx(_idx) {

    }

    Result operator()(const Source &src) {
        Result result;
        auto *j = result.begin();
        for(auto i:idx) {
            *j++ = src[i];
        }
        return result;
    }
};

template<class Source, class Index>
auto extract(const Source &src, const Index &idx) -> typename extract_helper<Source,Index>::Result {
    extract_helper<Source,Index> extractor(idx);
    return extractor(src);
}

struct state {
    typedef std::array<uint32_t,3> Group;

    static constexpr std::array<Group,5> idx_groups = {{
            {{1,0,2}},
            {{3,2,4}},
            {{5,4,6}},
            {{7,6,8}},
            {{9,8,0}},
    }};

    static constexpr std::array<uint32_t,5> inner = {{0,2,4,6,8}};
    static constexpr std::array<uint32_t,5> outer = {{1,3,5,7,9}};

    friend std::ostream& operator<<(std::ostream& os, const state &s);

    bool valid = true;
    uint32_t target;
    std::array<uint32_t,10> n;
    std::bitset<11> used;

    explicit state(uint32_t t):target(t) {
        n.fill(0);
        use(9,10);
        used[0] = true;
    }

    bool solve_complete_groups() {
        bool changed;

        do {
            changed = false;

            for(const auto &idx: state::idx_groups) {
                auto x = extract(n,idx);
                if(std::count(x.begin(),x.end(),0) == 1) {
                    auto zero_idx = idx[std::find(x.begin(),x.end(),0) - x.begin()];
                    uint32_t candidate = target - std::accumulate(x.begin(),x.end(),(uint32_t)0);
                    if(!used[candidate]) {
                        used[candidate] = true;
                        n[zero_idx] = candidate;
                        changed = true;
                    } else {
                        valid = false;
                        return false;
                    }
                }
            }
        } while(changed);

        return true;
    }

    bool final() const {
        return used.all();
    }

    bool invalidate() {
        if(!solve_complete_groups()) {
            return false;
        }

        for(auto idx: state::idx_groups) {
            auto x = extract(n,idx);
            if(std::count(x.begin(),x.end(),0) == 0) {
                if(std::accumulate(x.begin(),x.end(),(uint32_t)0) != target) {
                    valid = false;
                    return false;
                }
            }
        }

        return true;
    }

    bool use(uint32_t idx, uint32_t number) {
        if(!number || number >= used.size() || idx >= n.size()) {
            fmt::print("use({},{}): incorrect input\n",idx,number);
            return false;
        }
        if(used[number]) {
            fmt::print("use({},{}): {} is already used\n",idx,number,number);
            return false;
        }

        if(n[idx]) {
            fmt::print("use({},{}): {} position is already taken by {}\n",idx,number,idx,n[idx]);
            return false;
        }

        used[number] = true;
        n[idx] = number;
        return invalidate();
    }

    std::vector<uint32_t> get_partially_complete_group_idxs() const {
        std::vector<uint32_t> group_idxs;

        for(auto i=state::idx_groups.begin();i!=state::idx_groups.end();++i) {
            auto x = extract(n,*i);
            if(std::count(x.begin(),x.end(),0) == x.size()-1) {
                group_idxs.push_back(i-state::idx_groups.begin());
            }
        }

        return group_idxs;
    }

    std::vector<state> next() const {
        std::vector<state> result;

        auto partially_completed = get_partially_complete_group_idxs();

        for(auto group_idx: partially_completed) {
            const auto &idx = state::idx_groups[group_idx];
            auto x = extract(n,idx);
            auto candidate_idx = idx[std::find(x.begin(),x.end(),0) - x.begin()];
            uint32_t sum = std::accumulate(x.begin(),x.end(),(uint32_t)0);
            uint32_t upper_limit = std::min(target-sum,(uint32_t)used.size());
            for(uint32_t candidate=1;candidate<upper_limit;++candidate) {
                if(used[candidate]) {
                    continue;
                }
                state new_state = *this;
                if(new_state.use(candidate_idx,candidate)) {
                    result.push_back(new_state);
                }
            }
        }

        return result;
    }

    explicit operator bool() const {
        return valid;
    }

    explicit operator std::string() const {
        std::vector<Group> parts;
        parts.reserve(state::idx_groups.size());
        for(const auto &idx: state::idx_groups) {
            auto x = extract(n,idx);
            parts.push_back(x);
        }

        auto min_part = std::min_element(parts.begin(),parts.end());
        std::rotate(parts.begin(),min_part,parts.end());

        std::vector<std::string> s;
        for(const auto &i: parts) {
            s.push_back(join("",i.begin(),i.end()));
        }

        return join("",s.begin(),s.end());
    }
};
constexpr std::array<std::array<uint32_t,3>,5> state::idx_groups;

std::ostream& operator<<(std::ostream& os, const state &s) {
#define FMT "({: >2})"
    os << fmt::format("[{}]\n",static_cast<std::string>(s));
    os << fmt::format("{}   " FMT "\n",s.valid ? "+" : "-",s.n[1]);
    os << fmt::format("        " FMT "   " FMT "\n",s.n[0],s.n[3]);
    os << fmt::format("    " FMT "    " FMT "\n",s.n[8],s.n[2]);
    os << fmt::format(FMT " " FMT " " FMT " " FMT "\n",s.n[9],s.n[6],s.n[4],s.n[5]);
    os << fmt::format("      " FMT "\n",s.n[7]);
#undef FMT
    return os;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string max;

    Measure measure;

    for(uint32_t target=13;target <= 25; ++target) {
        std::vector<state> gen = {state(target)};
        gen.reserve(1000);
        std::vector<state> next_gen;
        next_gen.reserve(1000);

        while(gen.size()) {
            next_gen.clear();
            for(const auto &state: gen) {
                if(state.final()) {
                    const std::string &s = static_cast<std::string>(state);
                    if(s > max) {
                        max = s;
                    }
                    if(!util::test_mode()) fmt::print("{}\n",state);
                    continue;
                }
                auto next = state.next();
                next_gen.insert(next_gen.end(),next.begin(),next.end());
            }
            std::swap(gen,next_gen);
        }
    }

    auto passed = measure.passed();

    if(!util::test_mode()) {
        fmt::print("Processing took {} ms\n", passed);
        fmt::print("Max: ");
    }
    fmt::print("{}\n",max);

    return 0;
}
