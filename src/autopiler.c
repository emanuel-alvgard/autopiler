#ifndef LITE_IO
#define LITE_IO
#include "lite_io.h"
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

    long input_file_size = 0;
    file_size(scan_path, &input_file_size);
    
    char *current = calloc(input_file_size, 1);
    file_read(scan_path, current);
    
    while (1) {

        long new_size = 0;
        file_size(scan_path, &new_size);
        
        char *new = calloc(new_size, 1);
        file_read(scan_path, new);
        
        if (strcmp(current, new) != 0) { 
            free(current);
            current = new;
            system(result);
            printf("%s compiled to %s.exe\n", input_file, output_file);
            Sleep(100);
            continue;
        }
        free(new);
        Sleep(100);         
    }
    return 0;
}


