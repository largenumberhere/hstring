#include "hstring.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

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

void get_int_test(){
    HSTRING hstring = hstring_new();

    //Positive numbers
    int value = hstring_get_int(&hstring);
    //printf("hstirg: '%s'\n",hstring.contents);
    assert(value == 12345678); //As defined in testinput.txt, which is piped into this test program
    assert(errno == 0);

    //Non-numbers
    hstring_clear(&hstring);
    int invalid_value = hstring_get_int(&hstring);
    //printf("hstring2: '%s\n'", hstring.contents);
    assert(invalid_value == -1);
    assert(errno = 1);

    //Negative numbers
    errno = 0;
    hstring_clear(&hstring);
    int value2 = hstring_get_int(&hstring);
    //printf("%i\n", value2);
    assert(value2==-200);
    assert(errno==0);

    hstring_clear(&hstring);
    int value3 = hstring_get_int(&hstring);
    assert(value3 ==200);
    assert(errno==0);
    hstring_clear(&hstring);


    hstring_validity_assert(&hstring, "get_int corruped hstring!");
    hstring_free(&hstring);
}



int main(){
    validity_assert_test();
    push_string_raw_test();
    push_char_and_push_string_test();
    //stdin_test();
    clear_test();
    //atoi_e_test();
    get_int_test();
}









