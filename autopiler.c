#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif

#include <windows.h>

// make into lite_type.h??
struct String_1 { char string[32]; } typedef s1;
struct String_4 { char string[32]; } typedef s4;
struct String_8 { char string[32]; } typedef s8;
struct String_16 { char string[32]; } typedef s16;
struct String_32 { char string[32]; } typedef s32;
struct String_64 { char string[64]; } typedef s64;
struct String_128 { char string[128]; } typedef s128;
struct String_256 { char string[256]; } typedef s256;

struct String_1_KB { char string[256]; } typedef s1_KB;


#define directory_read_return_type s64


// FILE
char *file_read(char *path) { // must be freed by the caller

    FILE *file;
    file = fopen(path, "r");

    if (file == NULL) {
        printf("%s not found!\n", path);

        return "";
    }
    else {
        fseek(file, 0, SEEK_END);
        long length = ftell(file);
        fseek(file, 0, SEEK_SET);
        char *result = calloc(length, sizeof(char));
        fread(result, sizeof(char), length, file);
        fclose(file);

        return result;
    }
}



void file_create(char *data, char *path) {

    FILE *file;
    file = fopen(path, "w");

    fwrite(data, 1, strlen(data), file);
    fclose(file);

    return;
}



void file_append(char *data, char *path) {

    FILE *file;
    file = fopen(path, "a");
    
    if (file == NULL) {
        printf("%s not found!\n", path);
    }
    else {
        fwrite(data, 1, strlen(data), file);
        fclose(file);
    }
    return;
}



void file_delete() {}



// DIRECTORY
directory_read_return_type *directory_read(char *path) { // must be freed by the caller

    WIN32_FIND_DATAA file; 
    HANDLE first = FindFirstFileA(path, &file);

    int file_count = 0;
    
    while (1) {
        WINBOOL found = FindNextFileA(first, &file);
        if (found != 0) { file_count += 1; }
        else { break; }
    }

    FindClose(&file);
    directory_read_return_type *result = calloc(file_count, sizeof(directory_read_return_type));
 
    first = FindFirstFileA(path, &file);
    file_count = 0;
    
    while (1) {
        WINBOOL found = FindNextFileA(first, &file);
        if (found != 0) {
            file_count += 1;
            strcpy(result[file_count].string, file.cFileName);
        }
        else { break; }
    }

    FindClose(&file);
    return result;
}

void directory_create(char *directory, char *path) {

}
void directory_delete(char *path) {}





char input[100] = "";

void start() {
    printf("Autopiler v.1.0 is running.\n");
}

int help() { 
    return 0;
}

int compile() {
    return 0;
}

int stop() {
    if (strcmp(input, "stop") == 0) { return 1;}
    else { return 0; }
}

void unknown() {
    printf("Unknown command\n");
}


#define directory_read_return_type string_64
int main() {
    
    start();

    string_64 *dir_files = directory_read("c:/Users/emal/Desktop/distr/*");
    printf("%s", dir_files[5].string);
    free(dir_files);

/*
    while (1) {

        strcpy(input, "");
        printf("> ");
        scanf("%s", input);

        if (compile() == 1) { continue; }
        if (stop() == 1) { break; }
        else { unknown(); }
    }
*/       
    return 1;
}

