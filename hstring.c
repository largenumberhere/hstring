#include "hstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

extern int errno;

void hstring_validity_assert(HSTRING* hstring, const char* message);
int atoi_e(char* string, size_t string_length);

//Print the struct with its contents
void hstring_print(HSTRING* hstring){
    printf("HSTRING\n");
    printf("\tcapacity: %zu\n", hstring->capacity);
    printf("\tlength: %zu\n", hstring->length );
    printf("\tcontents: \"");
    for(int i = 0; i<hstring->length; i++){
        printf("%c", hstring->contents[i]);
    }
    printf("\"\n");
}

//Print the struct's technical information
void hstring_debug(HSTRING* hstring){
    printf("HSTRING\n");
    printf("\tactual capacity: %zu\n", hstring->capacity+1);
    printf("\tactuallength: %zu\n", hstring->length+1);
    printf("\tactualcontents: \"");
    printf("%s", hstring->contents);
    printf("\"\n");
}

//Create a null terminated hstring
HSTRING hstring_new() {
    HSTRING hstring;

    hstring.capacity = 0;
    hstring.contents = malloc(1);
    if(hstring.contents == NULL){
        printf("malloc(1) failed!\n");
        exit(-1);
    }
    hstring.contents[0] = '\0';
    hstring.length = 0;

    return hstring;
};

void hstring_realloc(HSTRING* hstring){
    //hstring_validity_assert(hstring);
    int acutal_capacity = ((hstring->capacity)+1);
    int required_bytes;
    if(acutal_capacity == 1){
        //let's just jump to 8 to save on expensive doublings from 1 to 2, 2 to 4 and 4 to 8. If the user has added 1 item, they are probably going to add more.
        required_bytes = 8;
    }
    else{
        required_bytes = acutal_capacity*2;
    }



    //enough size for double the characters and a null terminator
    char* new_contents = realloc((hstring)->contents , required_bytes);
        if(new_contents == NULL){
        printf("realloc of hstring failed!\n");
        printf("new size requested: %d\n", required_bytes);
        exit(-1);
    }

    (hstring)->contents = new_contents;

    //do not include null terminator in capacity
    (hstring)->capacity = (required_bytes)-1;
    //printf("HSTRING realloc'd\n");
    //print_hstring(hstring);
    //printf("new size requested: %d\n", required_bytes);
}

/**
 * Add a single character to the heapstring, extending its length and moving the null terminator. Extends the capacity if neccesary
 * Prefer using hstring_push_string or hstring_push_string_raw to minimize reallocations
**/
void hstring_push_char(HSTRING* hstring, char item){
    //hstring_validity_assert(hstring);
    //printf("char '%c'\n", item);

    if (hstring->length+2>hstring->capacity){
        hstring_realloc(hstring);
    }

    int char_pos = hstring->length;
    int null_pos = char_pos+1;
    //printf("char_pos: %d, null_pos: %d\n", char_pos, null_pos);
    //print_hstring(hstring);

    hstring->contents [char_pos] = item;
    hstring->contents [null_pos] = '\0';
    hstring->length+=1;
}

int nearest_power_of_2(int number){
    int a = 1;
    while(a<number){
        a*=2;
    }

    return a;
}

/**
 * Push a null terminated string. Use hstring_push_string_raw if your string may not be null terminated!
*/
void hstring_push_string(HSTRING* hstring, char* null_terminated_string){
    //hstring_validity_assert(hstring);
    //printf("bofore\n");
    //hstring_debug(hstring);

    int actual_string_length = strlen(null_terminated_string)+1;

    int acutal_capacity = ((hstring->capacity)+1);
    int actual_length = (hstring->length +1);

    int actual_room_left = (acutal_capacity - actual_length);
    //printf("%d\n", actual_room_left);
    //printf("actual_string_length %d\n", actual_string_length);
    if(actual_room_left < actual_string_length){
        //Reallocate in adnaced
        int required0 = actual_length + actual_string_length;
        int required = nearest_power_of_2(required0);
        char* contents = realloc(hstring->contents, required);
        if(contents == NULL){
            printf("Failed to reallocate for hstring_push_string\n");
            exit(-1);
        }
        hstring->contents = contents;
        hstring->capacity = required;

        //printf("realloc\n");

    }


    char* copy_start = &hstring->contents[hstring->length];
    strcpy(copy_start, null_terminated_string);
    copy_start[actual_string_length] = '\0';


    hstring->length = hstring->length + (actual_string_length -1);

    //printf("afer\n:");
    //hstring_debug(hstring);
}

/*
 * Add the non-null terimated string (or char array) to the string.
 * Updates hstring's length and moves null terminator to the end of it. If neccesary reallocates to the full size immediately
 * Copies every element into the hstring from 0 to (not including) unterminated_length.
*/
void hstring_push_string_raw(HSTRING* hstring, char* unterminated_string, int unterminated_length){
    //hstring_validity_assert(hstring);
    if(unterminated_length == 0){
        return;
    }

    int acutal_capacity = ((hstring->capacity)+1);
    int actual_length = (hstring->length +1);

    int actual_room_left = (acutal_capacity - actual_length);
    //printf("%d\n", actual_room_left);
    //printf("unterminated_length %d\n", unterminated_length);
    if(actual_room_left < unterminated_length+1){
        //Reallocate in adnaced
        int required0 = actual_length + unterminated_length+1;
        int capacity_required = nearest_power_of_2(required0);
        char* contents = realloc(hstring->contents, capacity_required);
        if(contents == NULL){
            printf("Failed to reallocate for hstring_push_string\n");
            exit(-1);
        }
        hstring->contents = contents;
        hstring->capacity = capacity_required;
        //printf("realloc\n");
    }


    char* contents = hstring->contents;
    int offset = hstring->length;
    //printf("offset: %i \n", offset);
    char* copy_start = contents + offset;
    //printf("copy_start '%s'\n",copy_start);

    //char* copy_start = &hstring->contents[hstring->length-2];
    // printf("starting_character to replace: '%c'",*copy_start);
    // if(copy_start == NULL){
    //     printf("is null pointer! and ");
    // }
    // if(*copy_start == '\0'){
    //     printf("is null");
    // }
    // else{
    //     printf("is not null");
    // }
    // printf("\n");

    //strcpy(copy_start, null_terminated_string);
    for(int i = 0; i < unterminated_length; i++){
        copy_start[i] = unterminated_string[i];
    }

    copy_start[unterminated_length] = '\0';
    hstring->length = hstring->length + (unterminated_length);
}

/*
 * Does what it says on the tin...
*/
void hstring_read_stdin_char(HSTRING* hstring){
    char c = getc(stdin);
    hstring_push_char(hstring, c);
}


const size_t BUFFSIZE = 128;

/*
 * read a single line from stdin into a hstring. in up to BUFFSIZE bytes at a time (to avoid excessive re-allocation)
*/
void hstring_read_stdin_line(HSTRING* hstring){
    //hstring_validity_assert(hstring);
    //buffer is a char*
    char buff[BUFFSIZE];
    size_t buff_index = 0;
    while(true){
        //buffer is at max size
        if(buff_index > BUFFSIZE -1) {
            //copy to string
            //printf("emptying buff\n");

            hstring_push_string_raw(hstring, buff, buff_index);
            buff_index = 0;
        }

        buff[buff_index] = getc(stdin);

        //printf("reading %zu\n", buff_index);
        if(buff[buff_index] == '\n'){
            break;
        }

        buff_index++;
    }


    //copy remaining buffer
    // printf("buffer filling has ended. Moving in contents\n");
    // printf("buff contents:\n");
    // printf("\t'");
    // for(int i = 0; i < buff_index;i++){
    //     printf("%c",buff[i]);
    // }
    // printf("'");
    // printf("\n");
    //printf("%zu", buff_index);
    hstring_push_string_raw(hstring, buff, buff_index);
}

//Read stdin, using this hstring as a buffer and convert it to an integer.
//If the conversion fails, output is set to -1 or -2 and errno is set to 1 or 2
//Does NOT clear the buffer for you. Its contents will be the line from stdin
int hstring_get_int(HSTRING* hstring){
    hstring_read_stdin_line(hstring);
    int value = atoi_e(hstring->contents, hstring->length);
    return value;
}

/*
 * Does not deallocate the hstring, only sets the pointer and length to defaults
*/
void hstring_clear(HSTRING* hstring){
    hstring->length =0;
    hstring->contents[0] = '\0';
    return;
}

/*
 * Free the hstring and set to defaults
*/
void hstring_free(HSTRING* hstring){
    assert(hstring->contents != NULL);
    free(hstring->contents);
    hstring->contents = NULL;
    hstring->length = 0;
    hstring->capacity = 0;
}

void exit_with_stacktrace(){
    // void* callstack[128];
    // int i;
    // int frames = backtrace(callstack, 128);
    // char** strs = backtrace_symbols(callstack, frames);
    // for (i = 0; i < frames; ++i) {
    //     printf("%s\n", strs[i]);
    // }
    // free(strs);
    exit(-1);
}

/**
 *  Check the struct for any flaws and exit if any are found to prevent memory corruption. Very useful for debugging!
 */
void hstring_validity_assert(HSTRING* hstring, const char* failure_message){
    if(hstring->contents == NULL){
        printf("hstring is null!\n");
        exit_with_stacktrace();
    }

    if(hstring->length > hstring->capacity){
        printf("hstring is larger than its capacity!\n");
        exit_with_stacktrace();
    }

    // int pos = 0;
    // for(; pos < hstring->length;pos++){}

    if(hstring->contents[hstring->length] !='\0'){
        printf("Null terminator went missing!\n");
        exit(-1);
    }

    for(int i = 0; i < hstring->length; i++){
        if(hstring->contents[i] == '\0'){
            printf("Null character found before end of string at index %i!\n", i);
            printf("hstring length: %zu\n", hstring->length);
            printf("hstring capacity: %zu\n", hstring->capacity);
            printf("%s\n", failure_message);
            exit_with_stacktrace();
        }
    }

    return;
}

// Atoi that reports an error when it fails
int atoi_e(char* string, size_t string_length){
    if(string_length == 0){
        errno = 2;
        return -2;
    }
    int i = 0;
    int mul = 1;
    if(string[0] == '-'){
        mul = -1;
        i++;
    }


    int v = 0;
    for(; i < string_length; i++){
        char c = string[i];
        if (c == '\0'){
            v*=10;
            continue;
        }

        if(c < '0' || c>  '9'){
            //printf("'%c' is out of range\n", c);
            errno = 1;
            return -1;
        }

        v = v*10;
        v += c - '0';
    }

    if (mul == -1){
        v*=-1;
    }

    return v;
}

void atoi_e_test(){
    assert(errno == 0);
    int f = atoi_e("f",1);
    assert(f == -1);
    assert(errno == 1);
    errno = 0;

    assert(errno == 0);
    char* string = "1234";
    int string_len = strlen(string);
    int num = atoi_e(string, string_len);
    assert(num == 1234);
    assert(errno == 0);

    assert(errno==0);
    //For some reason, c doesn't handle null characters at position 0 in a `char* string = ""` definiton
    char string2a[3];
    string2a[0] = '\0';
    string2a[1] = '\0';
    string2a[2] = '2';
    char*string2 = string2a;
    int string2_len = 3;
    int num2 = atoi_e(string2, string2_len);
    assert(num2 == 2);
    assert(errno == 0);
}