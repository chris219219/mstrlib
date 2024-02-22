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

    long cstr_size = strlen(cstr) + 1;
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

bool mstrcmp(const mstring *s1, const mstring *s2)
{
    if (s1 == NULL && s2 == NULL) return true;
    else if ((s1 == NULL) ^ (s2 == NULL)) return false;

    if (s1->len != s2->len) return false;

    for (long i = 0; i < s1->len; ++i)
    {
        if (s1->cstr[i] != s2->cstr[i]) return false;
    }
    return true;
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

long mstrcmatch(const mstring *s, char match)
{
    if (s == NULL) return 0;

    long matches = 0;
    for (long i = 0; i < s->len; ++i)
    {
        if (s->cstr[i] == match)
            ++matches;
    }
    return matches;
}

long mstrsmatch(const mstring *s, const mstring *match)
{
    if (s == NULL || match == NULL) return 0;

    long matches = 0;
    long curr_match = 0;
    for (long i = 0; i < s->len; ++i)
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

    long matches = mstrsmatch(s, old_s);
    long new_len = s->len + (matches *(new_s->len - old_s->len));
    mstring *r = malloc(sizeof(mstring) + new_len + 1);
    if (r == NULL) return NULL;

    r->len = new_len;

    long new_i = 0;
    long curr_match = 0;
    for (long i = 0; i < s->len; ++i)
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

mstring *mstrnrep(const mstring *s, const mstring *old_s, const mstring *new_s, long n)
{
    if (s == NULL || old_s == NULL || new_s == NULL) return NULL;

    long matches = min(mstrsmatch(s, old_s), n);
    long new_len = s->len + (matches * (new_s->len - old_s->len));
    mstring *r = malloc(sizeof(mstring) + new_len + 1);
    if (r == NULL) return NULL;
    
    r->len = new_len;

    matches = 0;
    long new_i = 0;
    long curr_match = 0;
    for (long i = 0; i < s->len; ++i)
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

mstring *mstrpop(const mstring *s, long n)
{
    if (s == NULL || n < 0) return NULL;

    long new_len = s->len - n;
    mstring *r = malloc(sizeof(mstring) + s->len - n + 1);
    if (r == NULL) return NULL;

    r->len = new_len;
    memcpy(r->cstr, s->cstr, new_len);
    r->cstr[new_len] = '\0';
    return r;
}

mstring *mstrslice(const mstring *s, long start, long end)
{
    if (s == NULL || end <= start) return NULL;

    long new_len = end - start;
    mstring *r = malloc(sizeof(mstring) + new_len + 1);
    if (r == NULL) return NULL;

    r->len = new_len;
    memcpy(r->cstr, s->cstr + start, new_len);
    r->cstr[new_len] = '\0';
    return r;
}

// helper function
bool char_in_arr(char c, const char *arr, long arr_n)
{
    for (long i = 0; i < arr_n; ++i)
    {
        if (c == arr[i]) return true;
    }
    return false;
}

// helper function
long ctokcount(const mstring *s, const char *seps, long seps_n)
{
    if (s == NULL || seps == NULL)
        return 0;

    long tok_count = 0;
    long curr_tok_len = 0;
    for (long i = 0; i < s->len; ++i)
    {
        if (!char_in_arr(s->cstr[i], seps, seps_n))
        {
            ++curr_tok_len;
            continue;
        }
        // found separator
        if (curr_tok_len != 0)
        {
            ++tok_count;
            curr_tok_len = 0;
        }
    }
    // last token
    if (curr_tok_len != 0)
    {
        ++tok_count;
    }
    return tok_count;
}

mstringtoks mstrctok(const mstring *s, const char *seps, long seps_n)
{
    if (s == NULL || seps == NULL)
        return (mstringtoks) { 0, NULL };

    long tok_count = ctokcount(s, seps, seps_n);
    mstring **toks = malloc(sizeof(mstring*) * tok_count);
    if (toks == NULL) return (mstringtoks) { 0, NULL };

    tok_count = 0;
    long curr_tok_start = 0;
    long curr_tok_len = 0;
    for (long i = 0; i < s->len; ++i)
    {
        if (!char_in_arr(s->cstr[i], seps, seps_n))
        {
            ++curr_tok_len;
            continue;
        }
        // found separator
        if (curr_tok_len != 0)
        {
            mstring *tok = mstrslice(s, curr_tok_start, curr_tok_start + curr_tok_len);
            toks[tok_count] = tok;
            ++tok_count;
            curr_tok_len = 0;
            curr_tok_start = i + 1;
        }
        // if current token length is 0
        else
        {
            curr_tok_start = i + 1;
        }
    }
    // last token
    if (curr_tok_len != 0)
    {
        mstring *tok = mstrslice(s, curr_tok_start, curr_tok_start + curr_tok_len);
        toks[tok_count] = tok;
        ++tok_count;
    }

    return (mstringtoks) { tok_count, toks };
}

mstringtoks mstrstok(const mstring *s, const mstring **seps, long seps_n)
{
    if (s == NULL || seps == NULL)
        return (mstringtoks) { 0, NULL };

    return (mstringtoks) { 0, NULL };
}

void mstrfreetoks(mstringtoks toks)
{
    for (long i = 0; i < toks.tok_count; ++i)
    {
        free(toks.toks[i]);
    }
    free(toks.toks);
}