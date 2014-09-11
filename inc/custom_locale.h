#ifndef CUSTOM_LOCALE
#define CUSTOM_LOCALE

#include <locale>
#include <vector>

struct csv_locale: std::ctype<char> {
    csv_locale(): std::ctype<char>(get_table()) {

    }

    static ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> rc(table_size, ctype_base::mask());

        rc[' '] = ctype_base::space;
        rc[','] = ctype_base::space;
        rc['/'] = ctype_base::space;
        rc['"'] = ctype_base::space;
        rc['\t'] = ctype_base::space;
        rc['\r'] = ctype_base::space;
        rc['\n'] = ctype_base::space;
        return &rc[0];
    }
};

#endif