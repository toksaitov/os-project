#include "kctypes.h"

char k_toupper(char c)
{
    if (c >= 'a' && c <= 'z') { c -= ('a' - 'A'); }

    return c;
}

char k_tolower(char c)
{
    if (c >= 'A' && c <= 'Z') { c += ('a' - 'A'); } 

    return c;
}
