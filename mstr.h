#ifndef MSTR_H
#define MSTR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct mstring mstring;
struct mstring
{
    long len;
    char cstr[];
};

typedef struct mstringtoks mstringtoks;
struct mstringtoks
{
    long tok_count;
    mstring **toks;
};

// Creates a new mstring from a C style string.
mstring *mstr(const char *cstr);

// Duplicates an mstring.
mstring *mstrdup(const mstring *s);

// Compares two mstrings.
bool mstrcmp(const mstring *s1, const mstring *s2);

// Adds two mstrings.
mstring *mstradd(const mstring *s1, const mstring *s2);

// Gets the number of characters in s that match a specified character.
long mstrcmatch(const mstring *s, char match);

// Gets the number of substrings in s that match a specified string.
long mstrsmatch(const mstring *s, const mstring *match);

// Replaces occurences of old_s with new_s in s.
mstring *mstrrep(const mstring *s, const mstring *old_s, const mstring *new_s);

// Replaces the first n occurences of old_s with new_s in s.
mstring *mstrnrep(const mstring *s, const mstring *old_s, const mstring *new_s, long n);

// Removes n characters from s.
mstring *mstrpop(const mstring *s, long n);

// Slices an mstring from start to end indexes, inclusive.
mstring *mstrslice(const mstring *s, long start, long end);

// Tokenizes s with a list of character separators.
mstringtoks mstrctok(const mstring *s, const char *seps, long seps_n);

// Tokenizes s with a list of mstring separators.
//mstringtoks mstrstok(const mstring *s, const mstring **seps, long seps_n);

// Frees an mstringtoks structure.
void mstrfreetoks(mstringtoks toks);

#endif