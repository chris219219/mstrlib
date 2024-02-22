#include "mstr.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b)            \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a, b)            \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

mstring *mstr(const char *cstr)
{
    if (cstr == NULL) return NULL;

    size_t cstr_size = strlen(cstr) + 1;
    mstring *s = malloc(sizeof(mstring) + cstr_size);
    if (s == NULL) return NULL;

    s->len = cstr_size - 1;
    memcpy(s->cstr, cstr, cstr_size);
    return s;
}

mstring *mstrdup(const mstring *s)
{
    if (s == NULL) return NULL;

    mstring *r = malloc(sizeof(mstring) + s->len + 1);
    if (r == NULL) return NULL;

    r->len = s->len;
    memcpy(r->cstr, s->cstr, s->len + 1);
    return r;
}

mstring *mstradd(const mstring *s1, const mstring *s2)
{
    if (s1 == NULL || s2 == NULL) return NULL;

    mstring *r = malloc(sizeof(mstring) + s1->len + s2->len + 1);
    if (r == NULL) return NULL;

    r->len = s1->len + s2->len;
    memcpy(r->cstr, s1->cstr, s1->len);
    memcpy(r->cstr + s1->len, s2->cstr, s2->len + 1);
    return r;
}

bool mstrcmp(const mstring *s1, const mstring *s2)
{
    if (s1 == NULL || s2 == NULL) return false;

    if (s1->len != s2->len) return false;

    for (size_t i = 0; i < s1->len; ++i)
    {
        if (s1->cstr[i] != s2->cstr[i]) return false;
    }
    return true;
}

size_t mstrcmatch(const mstring *s, char match)
{
    if (s == NULL) return 0;

    size_t matches = 0;
    for (size_t i = 0; i < s->len; ++i)
    {
        if (s->cstr[i] == match)
            ++matches;
    }
    return matches;
}

size_t mstrsmatch(const mstring *s, const mstring *match)
{
    if (s == NULL || match == NULL) return 0;

    size_t matches = 0;
    size_t curr_match = 0;
    for (size_t i = 0; i < s->len; ++i)
    {
        if (s->cstr[i] != match->cstr[curr_match])
        {
            curr_match = 0;
            continue;
        }
        // current character matches
        ++curr_match;
        if (curr_match == match->len)
        {
            ++matches;
            curr_match = 0;
        }
    }
    return matches;
}

mstring *mstrrep(const mstring *s, const mstring *old_s, const mstring *new_s)
{
    if (s == NULL || old_s == NULL || new_s == NULL) return NULL;

    size_t matches = mstrsmatch(s, old_s);
    size_t new_len = s->len + (matches * (new_s->len - old_s->len));
    mstring *r = malloc(sizeof(mstring) + new_len + 1);
    if (r == NULL) return NULL;
    
    r->len = new_len;

    size_t new_i = 0;
    size_t curr_match = 0;
    for (size_t i = 0; i < s->len; ++i)
    {
        if (s->cstr[i] != old_s->cstr[curr_match])
        {
            r->cstr[new_i] = s->cstr[i];
            ++new_i;
            curr_match = 0;
            continue;
        }
        // current character matches
        if (curr_match < new_s->len)
        {
            r->cstr[new_i] = new_s->cstr[curr_match];
            ++new_i;
        }
        ++curr_match;
        if (curr_match == old_s->len)
        {
            while (curr_match < new_s->len)
            {
                r->cstr[new_i] = new_s->cstr[curr_match];
                ++new_i;
                ++curr_match;
            }
            curr_match = 0;
        }
    }
    return r;
}

mstring *mstrnrep(const mstring *s, const mstring *old_s, const mstring *new_s, size_t n)
{
    if (s == NULL || old_s == NULL || new_s == NULL) return NULL;

    size_t matches = min(mstrsmatch(s, old_s), n);
    size_t new_len = s->len + (matches * (new_s->len - old_s->len));
    mstring *r = malloc(sizeof(mstring) + new_len + 1);
    if (r == NULL) return NULL;
    
    r->len = new_len;

    matches = 0;
    size_t new_i = 0;
    size_t curr_match = 0;
    for (size_t i = 0; i < s->len; ++i)
    {
        if (s->cstr[i] != old_s->cstr[curr_match] || matches >= n)
        {
            r->cstr[new_i] = s->cstr[i];
            ++new_i;
            curr_match = 0;
            continue;
        }
        // current character matches
        if (curr_match < new_s->len)
        {
            r->cstr[new_i] = new_s->cstr[curr_match];
            ++new_i;
        }
        ++curr_match;
        if (curr_match == old_s->len)
        {
            while (curr_match < new_s->len)
            {
                r->cstr[new_i] = new_s->cstr[curr_match];
                ++new_i;
                ++curr_match;
            }
            curr_match = 0;
            ++matches;
        }
    }
    return r;
}

mstring *mstrpop(const mstring *s, size_t n)
{
    if (s == NULL) return NULL;

    size_t new_len = s->len - n;
    mstring *r = malloc(sizeof(mstring) + s->len - n + 1);
    if (r == NULL) return NULL;

    r->len = new_len;
    memcpy(r->cstr, s->cstr, new_len);
    r->cstr[new_len] = '\0';
    return r;
}

// helper function
bool char_in_arr(char c, const char *arr, size_t arr_n)
{
    for (size_t i = 0; i < arr_n; ++i)
    {
        if (c != arr[i]) return false;
    }
    return true;
}

/*
mstring **mstrctok(const mstring *s, const char *toks, size_t toks_len)
{
    if (s == NULL || toks == NULL)
        return NULL;

    // WIP
}

mstring **mstrstok(const mstring *s, const mstring **toks, size_t toks_len)
{
    if (s == NULL || toks == NULL)
        return NULL;

    // WIP
}
*/