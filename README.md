# Hstring

A small heap allocated string library
The HSTRING struct is quite small and very versatile.

```c
typedef struct{
    size_t capacity;
    size_t length;
    char* contents;
}
HSTRING;
```

There are functions, to create, add to, free and more for use with hstring.
It always includes a null terminator and length. Thus it can be like a char array or a string in standard c libraries.

Eg:
```c
#include "hstring.h"
#include <assert.h>
#include <string.h>

HSTRING hstring = hstring_new();

// strcmp always expects a null-terminated string which is true even for a zero length of HSTRING
int result = strcmp(hstring.contents, "");
assert(result == 0)

//hstring has some methods to easily append without worrying about manual reallocation.
hstring_push_char(&hstring, 'a');

//without realocation, it can be reused and for example be refilled by buffers
hstring_clear(&hstring);

//it is super easy to read from standard input
hstring_read_stdin_line(&hstring)

//It is easy to iterate through each element
for(int i = 0; i < hstring.length; i++){
    printf("%c",hstring.contents[i]);
}

//It is trivial to validate HSTRING hasn't been corrupted from any memory errors and make your programs just that little bit memory safer and prevent undefined behaviour
hstring_validity_assert(&hstring, "Something has gone terribly wrong!");
```

# Run
Project was built on linux with "Ubuntu clang version 14.0.0-1ubuntu1.1", and tested with "valgrind-3.18.1".
Install these programs on your machiene for best results.
Run the tests with `make`

# Use it in your project
If you are interested in using this library in your project please express interest and l'll choose a licence for it.