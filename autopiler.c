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
struct String_1 { char value[32]; } typedef s1;
struct String_4 { char value[32]; } typedef s4;
struct String_8 { char value[32]; } typedef s8;
struct String_16 { char value[32]; } typedef s16;
struct String_32 { char value[32]; } typedef s32;
struct String_64 { char value[64]; } typedef s64;
struct String_128 { char value[128]; } typedef s128;
struct String_256 { char value[256]; } typedef s256;

struct String_1_KB { char value[256]; } typedef s1_KB;

#ifndef DIRECTORY_READ
#define DIRECTORY_READ s64
#endif

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
DIRECTORY_READ *directory_read(char *path, int count) { // must be freed by the caller

    DIRECTORY_READ *result = calloc(count, sizeof(DIRECTORY_READ));

    WIN32_FIND_DATAA file; 
    HANDLE first = FindFirstFileA(path, &file);

    int file_count = 0;
    while (1) {
        WINBOOL found = FindNextFileA(first, &file);
        if (found != 0) {
            file_count += 1;
            strcpy(result[file_count].value, file.cFileName);
        }
        else { break; }
    }

    FindClose(&first);
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



int main() {
    
    start();

    DIRECTORY_READ *dir_files = directory_read("c:/Users/emal/Desktop/distr/*", 10);
    printf("%s", dir_files[5].value);
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

