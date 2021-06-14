#ifndef LITE_IO
#define LITE_IO
#include "lite_io.h"
#endif



// CONFIG
char compiler[1000] = "";
char input_path[1000] = "";
char input_file[1000] = "";
char output_flag[10] = " -o ";
char output_path[1000] = "";
char output_file[1000] = "";
char object_files[1000] = "";
char library_flag[10] = " -l ";
char library_files[1000] = "";
char run[2] = "";

int main() {
    
    printf("Autopiler v.1.0.0\n");
    printf("Please enter input directory path:\n> ");
    scanf("%s", input_path);
    printf("Please enter input file name:\n> ");
    scanf("%s", input_file);
    printf("Please enter ouput directory path:\n> ");
    scanf("%s", output_path);
    printf("Please enter ouput file name:\n> ");
    scanf("%s", output_file);
    printf("Please enter library files:\n> ");
    scanf("%s", library_files);

    strcat(compiler, "gcc ");
    strcat(input_path, "/");
    strcat(output_path, "/");

    char result[1000] = "";
    strcat(result, compiler);
    strcat(result, input_path);
    strcat(result, input_file);
    strcat(result, output_flag);
    strcat(result, output_path);
    strcat(result, output_file);
    strcat(result, library_flag);
    strcat(result, library_files);

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


