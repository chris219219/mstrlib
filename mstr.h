#ifndef MSTR_H
#define MSTR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct mstring mstring;
struct mstring
{
    size_t len;
    char cstr[];
};

// Creates a new mstring from a C style string.
mstring *mstr(const char *cstr);

// Compares two mstrings.
bool mstrcmp(const mstring *s1, const mstring *s2);

// Duplicates an mstring.
mstring *mstrdup(const mstring *s);

// Adds two mstrings.
mstring *mstradd(const mstring *s1, const mstring *s2);

// Gets the number of characters in s that match a specified character.
size_t mstrcmatch(const mstring *s, char match);

// Gets the number of substrings in s that match a specified string.
size_t mstrsmatch(const mstring *s, const mstring *match);

// Replaces occurences of old_s with new_s in s.
mstring *mstrrep(const mstring *s, const mstring *old_s, const mstring *new_s);

// Replaces the first n occurences of old_s with new_s in s.
mstring *mstrnrep(const mstring *s, const mstring *old_s, const mstring *new_s, size_t n);

// Removes n characters from s.
mstring *mstrpop(const mstring *s, size_t n);

//mstring **mstrctok(const mstring *s, const char *toks, size_t tok_n);
//mstring **mstrstok(const mstring *s, const mstring **toks, size_t tok_n);

#endif