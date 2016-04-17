#ifndef OPTIONPARSER_CUSTOMIZED
#define OPTIONPARSER_CUSTOMIZED

#include <optionparser.h>
#include <cppformat/format.h>

struct CppFormatWriter {
    static void write(const char *str, size_t len) {
        fmt::printf("%.*s",len,str);
    }
};

std::ostream& operator<<(std::ostream& os, const option::Option& opt) {
    return os << fmt::sprintf("%.*s",opt.namelen,opt.name);
}

struct Arg: public option::Arg
{
    static option::ArgStatus Numeric(const option::Option& option, bool msg)
    {
        std::size_t pos = 0;
        if(option.arg) {
            std::stoul(option.arg,&pos,10);
        }
        if(pos && !option.arg[pos]) {
            return option::ARG_OK;
        }

        if (msg) {
            fmt::print("Option '{}' requires a numeric argument\n",option);
        }
        return option::ARG_ILLEGAL;
    }
};

#endif //OPTIONPARSER_CUSTOMIZED
