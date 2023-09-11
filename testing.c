#include "hstring.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>



void push_char_and_push_string_test(){
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
    assert(strcmp("1234567890123456789012345678", hstring.contents) == 0);

    hstring_free(&hstring);
}

void stdin_test(){
    HSTRING  hstring_src = hstring_new();
    HSTRING* hstring = &hstring_src;
    //hstring_print(hstring);
    hstring_read_stdin_line(hstring);
    //hstring_print(hstring);
    //hstring_print(hstring);
    //printf("contents: ");
    // for(int i = 0; i< hstring->length; i++){
    //     printf("%c",hstring->contents[i]);
    // }
    //printf("\n");
    hstring_free(hstring);

}

void push_string_raw_test(){
    HSTRING hstring = hstring_new();
    hstring_push_char(&hstring,'a');

    hstring_push_string_raw(&hstring, "123", 3);
    hstring_validity_assert(&hstring, "push_string_raw() 0");
    // printf("unsafe printing: ");
    // printf("%s\n", string);

    //hstring_print(&hstring);
    //printf("pushing raw\n");

    char* string = malloc(32);
    assert(string !=NULL);
    for(int i = 0; i< 32; i++){
        string[i] = 'a';
    }

    for(int i = 0; i < 32; i++){
        hstring_push_string_raw(&hstring, string, i);
        char buff[128];
        buff[127] = '\0';
        sprintf(&buff[0], "%i", i);
        hstring_validity_assert(&hstring, &buff[0]);
    }

    free(string);
    hstring_free(&hstring);
}

void validity_assert_test(){
    char* message = "validity_assert_test()";

    HSTRING hstring_src = hstring_new();
    HSTRING* hstring = &hstring_src;
    hstring_validity_assert(hstring, message);
    hstring_push_char(hstring, 'a');
    hstring_validity_assert(hstring, message);
    hstring_push_char(hstring, 'b');
    hstring_validity_assert(hstring, message);
    hstring_push_char(hstring, 'c');
    hstring_validity_assert(hstring, message);
    hstring_push_char(hstring, 'd');
    hstring_validity_assert(hstring, message);

    hstring_push_string(hstring, message);
    hstring_validity_assert(hstring, message);
    hstring_push_string(hstring, message);
    hstring_validity_assert(hstring, message);
    hstring_push_string(hstring, message);
    hstring_validity_assert(hstring, message);
    hstring_push_string(hstring, message);
    hstring_validity_assert(hstring, message);

    hstring_free(hstring);
}

void clear_test()   {
    HSTRING hstring = hstring_new();
    hstring_push_string(&hstring,"hello world");
    hstring_push_char(&hstring,'1');
    hstring_clear(&hstring);
    assert(strcmp(hstring.contents, "") == 0);
    hstring_validity_assert(&hstring, "chear_test()");
    hstring_free(&hstring);
}

int main(){
    validity_assert_test();
    push_string_raw_test();
    push_char_and_push_string_test();
    //stdin_test();
    clear_test();
}



