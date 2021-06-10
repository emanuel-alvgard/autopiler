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

#ifndef WINDOWS
#define WINDOWS
#include <windows.h>
#endif

#define RETURN_LOG
//#define LOG_NORMAL

#define INT 0
#define FLO 1
#define STR 2

#ifdef RETURN_LOG
int return_log(int error_code, char *function, int p_type, void *p_pointer) {

    // insert a printf for logging-error??
    
    char error_message[100] = "";
    
     switch (error_code) {
        case 0:
            #ifdef LOG_NORMAL
            strcpy(error_message, "NORMAL"); break;
            #else
            return error_code;
            #endif
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