#ifndef LITE_UTILITY
#define LITE_UTILITY
#include "lite_utility.h"
#endif

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



// FILE
int file_size(char *path, long *result) {
    
    FILE *file;
    file = fopen(path, "r");

    if (file == NULL) {
        return retlog(2, "file_size", STR, path);
    }

    fseek(file, 0, 0);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    memcpy(result, &size, sizeof(long)); 
    
    fseek(file, 0, 0);
    fclose(file);

    return retlog(0, "file_size", STR, path);
}



int file_read(char *path, char *result) {

    FILE *file;
    file = fopen(path, "r");

    if (file == NULL) {
        return retlog(2, "file_read", STR, path);
    }
    
    fseek(file, 0, 0);
    fseek(file, 0, SEEK_END);
    long count = ftell(file);
    
    fseek(file, 0, 0);
    char *allocation = (char *) calloc(count, 1);
    fread(allocation, 1, count, file);
    strcpy(result, allocation);   

    free(allocation);
    fclose(file);

    return retlog(0, "file_read", STR, path);
}



int file_create(char *data, char *path) {

    FILE *file;
    file = fopen(path, "r");

    if (file != NULL) {
        return retlog(4, "file_create", STR, path);
    }

    fclose(file);
    file = fopen(path, "w");

    if (file == NULL) {
        return retlog(3, "file_create", STR, path);
    }

    fwrite(data, 1, strlen(data), file);
    fclose(file);

    return retlog(0, "file_create", STR, path);
}



int file_append(char *data, char *path) {

    FILE *file;
    file = fopen(path, "r");
    
    if (file == NULL) {
        return retlog(2, "file_append", STR, path);
    }
    
    fclose(file);
    file = fopen(path, "a");
    fwrite(data, 1, strlen(data), file);
    fclose(file);

    return retlog(0, "file_append", STR, path);
}

int file_rename() { return 0; }

int file_delete() { return 0; }



// DIRECTORY
#ifdef LITE_WINDOWS

int directory_index(int index, char *path, char *result) {

    char _path[1000] = "";
    strcpy(_path, path);
    strcat(_path, "/*");    
    WIN32_FIND_DATAA file; 
    HANDLE first = FindFirstFileA(_path, &file);

    if (first == INVALID_HANDLE_VALUE) {
        return retlog(3, "directory_index", STR, path);
    }

    int count = 0;
    while (1) {

        WINBOOL found = FindNextFileA(first, &file);
        count += 1;

        if (found == 0) { 
            return retlog(1, "directory_index", INT, &index); 
        }
        if (count == index + 2) { break; }          
    }
    strcpy(result, file.cFileName);
    return retlog(0, "directory_index", INT, &index);
}

void directory_create(char *directory, char *path) {}

void directory_delete(char *path) {}

#endif

#ifdef LITE_POSIXS
#endif