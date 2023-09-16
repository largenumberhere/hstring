#include <stddef.h>
#define HSTRING_RESULT size_t;

/*
 * Single threaded only.
 *
 * The HSTRING or heap string type.
 * It is always null terminated and length always refers to the length of characters stored excluding the null character
 *
 * capacity is the max length of contents, not including null terminator. Once this is reached, contents will be realloc'd.
 * length is the current length of characters stored, not including null terminator.
 * contents points to malloc'd heap space which is always null terminated.
*/
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

int hstring_get_int(HSTRING* hstring);