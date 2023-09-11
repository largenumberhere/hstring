#include <stddef.h>
#define HSTRING_RESULT size_t;

typedef struct{
    size_t capacity;
    size_t length;
    char* contents;
}
HSTRING;

HSTRING hstring_new();

HSTRING hstring_new_with(int capacity);

void hstring_push_char(HSTRING* hstring, char item);

void hstring_push_string(HSTRING* hstring, char* null_terminated_string);

void hstring_push_string_raw(HSTRING* hstring, char* unterminated_string, int string_length_excluding_terminator);

void hstring_read_stdin_char(HSTRING* hstring);

void hstring_read_stdin_line(HSTRING* hstring);

void hstring_clear(HSTRING* hstring);

void hstring_free(HSTRING* hstring);

void hstring_print(HSTRING* hstring);

void hstring_validity_assert(HSTRING* hstring, const char* messagem);