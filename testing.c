#include "hstring.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(){
    HSTRING hstring = hstring_new();
    hstring_push_char(&hstring, '1');
    hstring_push_char(&hstring, '2');
    hstring_push_char(&hstring, '3');
    hstring_push_char(&hstring, '4');
    hstring_push_char(&hstring, '5');
    hstring_push_char(&hstring, '6');
    hstring_push_char(&hstring, '7');
    hstring_push_char(&hstring, '8');
    hstring_push_char(&hstring, '9');
    hstring_push_char(&hstring, '0');
    hstring_push_char(&hstring, '1');
    hstring_push_char(&hstring, '2');
    hstring_push_char(&hstring, '3');
    hstring_push_string(&hstring, "4");
    hstring_push_string(&hstring, "5");
    hstring_push_string(&hstring, "6789012345678");
    printf("string\n");
    char* string = malloc(32);
    assert(string !=NULL);
    for(int i = 0; i< 32; i++){
        string[i] = 'a';
    }

    printf("unsafe printing: ");
    printf("%s\n", string);

    hstring_print(&hstring);
    printf("pushing raw\n");
    hstring_push_string_raw(&hstring, string, 32);
    free(string);
    printf("pushed: ");

    hstring_print(&hstring);

    hstring_free(&hstring);



    hstring_read_stdin_line(&hstring);
}