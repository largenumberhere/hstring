#include "hstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

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

void hstring_debug(HSTRING* hstring){
    printf("HSTRING\n");
    printf("\tactual capacity: %zu\n", hstring->capacity+1);
    printf("\tactuallength: %zu\n", hstring->length+1);
    printf("\tactualcontents: \"");
    printf("%s", hstring->contents);
    printf("\"\n");
}


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

void hstring_push_char(HSTRING* hstring, char item){
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



void hstring_push_string(HSTRING* hstring, char* null_terminated_string){

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



void hstring_push_string_raw(HSTRING* hstring, char* unterminated_string, int string_length_excluding_terinator){

    int actual_string_length = string_length_excluding_terinator+1;

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
    //strcpy(copy_start, null_terminated_string);
    for(int i = 0; i< string_length_excluding_terinator; i++){
        copy_start[i] = unterminated_string[i];
    }

    copy_start[actual_string_length-1] = '\0';
    hstring->length = hstring->length + (actual_string_length -1);

}

void hstring_read_stdin_char(HSTRING* hstring){
    char c = getc(stdin);
    hstring_push_char(hstring, c);
}

const size_t BUFFSIZE = 2;
void hstring_read_stdin_line(HSTRING* hstring){
    //buffer is a char*
    char buff[BUFFSIZE];
    size_t buff_index = 0;
    while(true){
        //buffer is at max size
        if(!(buff_index <BUFFSIZE)) {
            //copy to string
            printf("emptying buff\n");
            hstring_push_string_raw(hstring, buff, buff_index-1);
            buff_index = 0;
        }

        buff[buff_index] = getc(stdin);

        if(buff[buff_index] == '\n'){
            break;
        }

        buff_index++;
    }


    //copy remaining buffer
    printf("buffer filling has ended. Moving in contents\n");
    hstring_push_string_raw(hstring, buff, buff_index);

}

void hstring_clear(HSTRING* hstring){
    printf("TODO\n");
    exit(-1);
}

void hstring_free(HSTRING* hstring){
    assert(hstring->contents != NULL);
    free(hstring->contents);
    hstring->contents = NULL;
    hstring->length = 0;
    hstring->capacity = 0;
}