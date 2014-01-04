#ifndef IOS_STATE
#define IOS_STATE

#include <iostream>
#include <ios>
#include <vector>

class ios_state {
    std::ios_base &ios;
    std::ios_base::fmtflags flags;
    std::streamsize precision;
public:
    explicit ios_state(std::ios_base &_ios):ios(_ios),flags(ios.flags()),precision(ios.precision()) {
           
    }
    
    ~ios_state() {
        ios.flags(flags);
        ios.precision(precision);
    }
};

#endif
