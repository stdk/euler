#include <cstddef>
#include <cmath>

using std::size_t;

void reverse(char *s, size_t len) {
    char *begin = s - 1;
    char *end = s + len;
    while(++begin < --end) {
        char tmp = *begin;
        *begin = *end;
        *end = tmp;
    }
}

template<class T, size_t N>
char *itoa(T num, char (&buffer)[N], size_t radix=10) {
    char *out = buffer + N;
    bool minus = std::signbit(num);
    num = std::abs(num);
    *--out = 0;
    if(num) {
        for(; out != buffer && num; num/=radix) {
            *--out = "0123456789ABCDEFGHIJKLMNOPQRSTYVWXYZabcdefghijklmnopqrstyvwxyz"[num % radix];
        }
    } else {
        *--out='0';        
    }
    if(out != buffer && minus) *--out='-';
    return out;
}
    

bool isPalindrome(size_t number) {
    char buffer[32];
    
    char *s = itoa(number, buffer); 
    
    char *begin = s;
    char *end = buffer + sizeof(buffer) - 2;
    while(begin < end) {
        if(*begin++ != *end--) return false;        
    }
    
    return true;
}
