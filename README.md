## mstrlib

mstrlib stands for "modern string library". It helps C developers write higher
level software without having to worry about too many of the intracacies of
strings in C.

## How to Build

mstrlib currently only supports Linux!

```
make
```

to only build the object file:

```
make objects
```

to clean up the project:
```
make clean
```

## How to Use

Copy the `mstr.h` header into your project and link `libmstr.a`.

```
#include <stdio.h>
#include <stdlib.h>
#include "mstr.h"

int main()
{
    mstring *s1 = mstr("This is a C string. ");
    mstring *s2 = mstr("mstring is great!");
    mstring *s3 = mstradd(s1, s2);
    printf("%s\n", s3->cstr);

    free(s1);
    free(s2);
    free(s3);
}
```