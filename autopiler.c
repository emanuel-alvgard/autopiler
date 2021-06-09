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

#ifndef STDARG
#define STDARG
#include <stdarg.h>
#endif

#ifndef WINDOWS
#define WINDOWS
#include <windows.h>
#endif



#define RETURN_LOG

#define INT 0
#define FLO 1
#define STR 2

#ifdef RETURN_LOG
int return_log(int error_code, char *function, int p_type, void *p_pointer) {

    // insert a printf for logging-error
    
    char error_message[100] = "";
    
     switch (error_code) {
        case 0:
            strcpy(error_message, "NORMAL"); break;
        case 1:
            strcpy(error_message, "INDEX OUT OF RANGE"); break;
        case 2:
            strcpy(error_message, "FILE NOT FOUND"); break;
        case 3:
            strcpy(error_message, "INVALID PATH"); break;
        case 4:
            strcpy(error_message, "FILE ALREADY EXIST"); break;
    }  
    
    if (p_type == 0) {
        int *int_pointer = (int *) p_pointer;
        printf("[return]: %s - %s(%i)\n", error_message, function, *int_pointer);
        return error_code;
    }
    if (p_type == 1) {
        float *float_pointer = (float *) p_pointer;
        printf("[return]: %s - %s(%f)\n", error_message, function, *float_pointer);
        return error_code;
    }
    if (p_type == 2) {
        char *char_pointer = (char *) p_pointer;
        printf("[return]: %s - %s(%s)\n", error_message, function, char_pointer);
        return error_code;
    }     
}

#define retlog(error_code, function, p_type, p_pointer) return_log(error_code, function, p_type, p_pointer)
#else
int return_error_code(int error_code) {
    return error_code;
}

#define retlog(error_code, function, p_type, p_pointer) return_error_code(error_code); 
#endif



int allocate() {
    // with help from global atomic variables this function keeps track of allocated
    // and logs all allocations and freeing of memory 
    return 0;
}



// FILE
// WRONG!!!
int file_read(char *path, char *result) {

    FILE *file;
    file = fopen(path, "r");

    if (file == NULL) {
        return retlog(2, "file_read", STR, path);
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    result = calloc(length + 1, sizeof(char));
    fread(result, sizeof(char), length, file); 
    //strcpy(result, buffer);
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
#ifdef WINDOWS

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

        if (found != 0) {}
        else {
            return retlog(1, "directory_index", INT, &index);
        }
        if (count == index + 2) { break; }
        else {}           
    }
    strcpy(result, file.cFileName);
    return retlog(0, "directory_index", INT, &index);
}

void directory_create(char *directory, char *path) {}

void directory_delete(char *path) {}

#endif

#ifdef POSIXS
#endif




/*
int configuration() {
    
    printf("Autopiler v.1.0.0\n");
    printf("Please enter configuration (enter '> config' for options):\n");

    while (1) {
        strcpy(, "");
        printf("> ");
        scanf("%s", user_configuration);
        
        
        // try to find file by input path
    } 
    return 0;
}
*/

/*
int compile() {

    if (strcmp(input, "compile") == 0) {}
    else { return 1; }

    char result[64];
    
    int count = 0;
    while (1) {
        directory_index(count, "c:/Users/emal/Desktop/distr", result);
        count += 1;
    }

    system("gcc ")

    return 0;
}

*/


// DEFAULT CONFIGURATION
char compiler[1000] = "";
char compiler_flags[1000] = "";
char input_path[1000] = "";
char input_file[1000] = "";
char output_path[1000] = "";
char output_file[1000] = "";
char object_files[1000] = "";
char run[2] = "";



int main() {
    
    printf("Autopiler v.1.0.0\n");
    // compiler
    strcat(compiler, "gcc ");
    
    // input path
    strcat(input_path, "c:/Users/emal/Desktop/autopiler");
    strcat(input_path, "/");

    // input file
    strcat(input_file, "autopiler.c");

    // output path
    strcat(output_path, " -o ");
    strcat(output_path, "c:/Users/emal/Desktop");
    strcat(output_path, "/");

    // output file
    strcat(output_file, "Autopiler");

    char result[1000] = "";
    strcat(result, compiler);
    strcat(result, input_path);
    strcat(result, input_file);
    strcat(result, output_path);
    strcat(result, output_file);

    char scan_path[1000] = "";
    strcat(scan_path, input_path);
    strcat(scan_path, input_file);

    //char current[10000] = "";
    char *current;
    file_read(scan_path, current);
    printf(current);
    //free(current);

    int i = 0;
    while (i < 10) {
        /*
        char *new = "";
        file_read(scan_path, new);
        
        if (strcmp(current, new) != 0) { 
            free(current);
            strcpy(current, new);
            system(result);
            printf("%s compiled to %s.exe\n", input_file, output_file);
        }        
        free(new);
        */
        printf("test"); 
        Sleep(500);
        i ++;
    }
    return 0;
}

//
