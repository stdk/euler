#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <util.h>

class __attribute__((packed)) Card {
    static const std::map<char,uint8_t> rank2value;
    static const char *ranks;
    static const char *suits;

    uint8_t value: 4;
    uint8_t suit: 2;
public:
    std::ostream& write(std::ostream &os) const {
        os << ranks[value] << suits[suit];
        return os;
    }

    std::istream& read(std::istream &is) {
        std::string s;
        is >> s;
        value = rank2value.find(s[0])->second;
        suit = strchr(suits,s[1]) - suits;
        return is;
    }

    inline bool operator<(const Card &other) const {
        if(value == other.value) return suit < other.suit;
        return value < other.value;
    }

    inline bool operator==(const Card &other) const {
        return value == other.value;
    }

    inline bool operator!=(const Card &other) const {
        return value != other.value;
    }

    inline uint32_t operator-(const Card &other) const {
        if(value < other.value) return rank2value.size() + value - other.value;
        return value - other.value;
    }

    inline bool same_suit(const Card &other) const {
        return suit == other.suit;
    }

    inline char rank() const {
        return ranks[value];
    }
};

const std::map<char,uint8_t> Card::rank2value = {
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'J', 11},
        {'Q', 12},
        {'K', 13},
        {'A', 14},
};

const char * Card::ranks = "\0\0" "23456789TJQKA";
const char * Card::suits = "HDSC"; // Hearts Diamonds Spades Clubs; order is insignificant

inline std::ostream& operator<<(std::ostream &os, const Card &card) {
    return card.write(os);
}

inline std::istream& operator>>(std::istream &is, Card &card) {
    return card.read(is);
}

enum class Combo {
    None,
    Pair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};

const char* combo_str[] = {
    "",
    "Pair",
    "Two Pairs",
    "Three of a Kind",
    "Straight",
    "Flush",
    "Full House",
    "Four of a Kind",
    "Straight Flush",
    "Royal Flush"
};

std::ostream& operator<<(std::ostream &os,Combo combo) {
    return os << combo_str[(unsigned)combo];
}

class AutoEndl {
    std::ostream &os;
public:
    AutoEndl(std::ostream &o = std::cout):os(o) {

    }
    ~AutoEndl() {
        os << std::endl;
    }
};

class Hand {
    Card cards[5];
    Combo combo = Combo::None;
    uint32_t relevant = 0;

    void detect_combo() {
        const size_t size = sizeof(cards)/sizeof(cards[0]);
        auto end = cards+size;
        std::sort(cards,end);

        bool same_suit = true;
        uint32_t diff = 0;
        for(auto i=cards;i!=end-1;++i) {
            diff |= (*(i+1) - *(i)) << (4*(i-cards));
            if(!i->same_suit(*(i+1))) same_suit = false;
        }
        diff |= (*cards - *(end-1)) << (4*(size-1));
        //std::cout << std::setfill('0') << std::setw(6) << std::hex << diff << std::dec << " | " << same_suit << std::endl;

        combo = Combo::None;
        relevant = 0;

        bool straight = (diff&0x0FFFF) == 0x01111 ||
                        (diff&0xFFFF0) == 0x11110 ||
                        (diff&0xFFF0F) == 0x11101 ||
                        (diff&0xFF0FF) == 0x11011 ||
                        (diff&0xF0FFF) == 0x10111;
        if(same_suit) {
            if(straight) {
                if(cards->rank() == 'T') {
                    combo = Combo::RoyalFlush;
                    relevant = 0;
                } else {
                    combo = Combo::StraightFlush;
                    relevant = 0b10000;
                }
            } else {
                combo = Combo::Flush;
                relevant = 0b10000;
            }
        } else {
            if(!(diff & 0xFFF0) || !(diff & 0x0FFF)) {
                combo = Combo::FourOfAKind;
                relevant = 0b00100;
            } else if(!(diff & 0xF0FF)) {
                combo = Combo::FullHouse;
                relevant = 0b00001 + (0b10000 << size);
            } else if(!(diff & 0xFF0F)) {
                combo = Combo::FullHouse;
                relevant = 0b10000 + (0b00001 << size);
            } else if(straight) {
                combo = Combo::Straight;
            } else if(!(diff & 0xFF00) || !(diff & 0x0FF0) || !(diff & 0x00FF)) {
                combo = Combo::ThreeOfAKind;
                relevant = 0b00100;
            } else if(!(diff & 0xF0F0) || !(diff & 0xF00F) || !(diff & 0x0F0F)) {
                combo = Combo::TwoPairs;
                relevant = 0b01010;
            } else if(!(diff & 0xF000) || !(diff & 0x0F00)) {
                combo = Combo::Pair;
                relevant = 0b01000;
            } else if(!(diff & 0x00F0) || !(diff & 0x000F)) {
                combo = Combo::Pair;
                relevant = 0b00010;
            }
        }
    }
public:
    std::ostream& write(std::ostream &os) const {
        const size_t size = sizeof(cards)/sizeof(cards[0]);
        auto end = cards+size;
        for(auto i=cards;i!=end;++i) {
            os << *i << (i == end ? "" : " ");
        }
        os << " (" << combo << ")";
        return os;
    }

    std::istream& read(std::istream &is) {
        const size_t size = sizeof(cards)/sizeof(cards[0]);
        auto end = cards+size;
        for(auto i=cards;i!=end;++i) {
            is >> *i;
        }
        detect_combo();
        return is;
    }

    bool operator<(const Hand &other) const {
        if(combo == other.combo) {
            //AutoEndl auto_endl;
            const size_t size = sizeof(cards)/sizeof(cards[0]);
            uint32_t ra = relevant;
            uint32_t rb = other.relevant;
            while(ra && rb) {
                size_t ka = (__builtin_ffs(ra) - 1) % size;
                size_t kb = (__builtin_ffs(rb) - 1) % size;

                //std::cout << "[" << cards[ka] << "<->" << other.cards[kb] << "]";
                if(cards[ka] != other.cards[kb]) {
                    return cards[ka] < other.cards[kb];
                }

                ra &= ~(1 << kb);
                rb &= ~(1 << kb);
            }
            for(ssize_t i=size-1;i>=0;i--) {
                //std::cout << "[" << cards[i] << "<->" << other.cards[i] << "]";
                if(cards[i] != other.cards[i]) {
                    return cards[i] < other.cards[i];
                }
            }
            //std::cout << "[Error]";
            return true;
        } else {
            return combo < other.combo;
        }
    }
};

inline std::ostream& operator<<(std::ostream &os, const Hand &hand) {
    return hand.write(os);
}

inline std::istream& operator>>(std::istream &is, Hand &hand) {
    return hand.read(is);
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    if(argc < 2) {
        std::cout << "Please specify input filename." << std::endl;
        return 1;
    }

    Measure measure;
    std::fstream in(argv[1]);

    size_t a_wins = 0;
    Hand a,b;
    while(in >> a >> b) {
        bool b_wins = a < b;
        a_wins += (b_wins ? 0 : 1);

        if(!util::test_mode()) {
            std::cout << a << (b_wins ? " < " : " > ") << b << std::endl;
        }
    }

    auto passed = measure.passed();

    if(!util::test_mode()) {
        std::cout << "Processing took " << passed << " ms" << std::endl;
        std::cout << "Player 1 wins: ";
    }
    std::cout << a_wins << std::endl;

    return 0;
}
