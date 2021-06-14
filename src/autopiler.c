#ifndef LITE_IO
#define LITE_IO
#include "lite_io.h"
#endif

// CONFIG
char compiler[1000] = "";
char linking[100] = "";
char input_path[1000] = "";
char input_file[1000] = "";
char output_flag[10] = " -o ";
char output_path[1000] = "";
char output_file[1000] = "";
char object_files[1000] = "";
char library_flag[10] = " -l ";
char library_files[1000] = "";
char run[2] = "";



void config_value(int index, char *content) {

    char index_string[5] = "";
    switch (index) {
        case 0: strcpy(index_string, "A0: "); break;
        case 1: strcpy(index_string, "A1: "); break;
        case 2: strcpy(index_string, "A2: "); break;
        case 3: strcpy(index_string, "A3: "); break;
        case 4: strcpy(index_string, "A4: "); break;
        case 5: strcpy(index_string, "A5: "); break;
        case 6: strcpy(index_string, "A6: "); break;
    }
    
    int i0 = 0;
    while (1) {
        if (content[i0] == index_string[0]
        && content[i0 + 1] == index_string[1]
        && content[i0 + 2] == index_string[2]
        && content[i0 + 3] == index_string[3]) { i0 += 4; break; }
        i0 += 1;  
    }

    int i1 = 0;
    while (1) {
        if (content[i0] == '\n' || content[i0] == '\0') { return; }
        switch (index) {
            case 0: compiler[i1] = content[i0]; break;
            case 1: linking[i1] = content[i0]; break;
            case 2: input_file[i1] = content[i0]; break;
            case 3: output_path[i1] = content[i0]; break;
            case 4: output_file[i1] = content[i0]; break;
            case 5: object_files[i1] = content[i0]; break;
            case 6: library_files[i1] = content[i0]; break;
        }
        i0 += 1;
        i1 += 1;
    }
}



int config_file() {
    
    char _config_file[100] = "";
    int count = 0;
    
    while (1) {
        int error = directory_index(count, input_path, _config_file);
        count += 1;
        
        if (strcmp(_config_file, "autopiler.txt") == 0) { break; }
        if (error == 1) { return 1;}    
    }

    char user_input[10] = "";
    printf("Use configuration file? (y/n):\n> ");
    scanf("%s", user_input);
    
    while (1) {
        if (strcmp(user_input, "n") == 0) { return 1; }
        if (strcmp(user_input, "y") == 0) { break; }

        printf("Invalid input. Please enter 'y' or 'n':\n>");
        scanf("%s", user_input);
    }

    strcpy(_config_file, "/autopiler.txt");
    char config_file_path[1000] = "";
    strcat(config_file_path, input_path);
    strcat(config_file_path, _config_file);
    
    long config_file_size = 0;
    file_size(config_file_path, &config_file_size);
    
    char *content = calloc(config_file_size, 1);
    file_read(config_file_path, content);

    config_value(0, content); // compiler
    config_value(1, content); // linking
    config_value(2, content); // input file
    config_value(3, content); // output path
    config_value(4, content); // output file
    config_value(5, content); // object files
    config_value(6, content); // library files

    printf("\nConfiguration: \n");
    printf("[Compiler]: %s\n", compiler);
    printf("[Linking]: %s\n", linking);
    printf("[Input file]: %s\n", input_file);
    printf("[Output path]: %s\n", output_path);
    printf("[Output file]: %s\n", output_file);
    printf("[Object files]: %s\n", object_files);
    printf("[Library files]: %s\n", library_files);

    return 0;
}



int main() {
    
    printf("Autopiler v.1.0.0\n");
    printf("Please enter input directory path:\n> ");
    scanf("%s", input_path);

    // look for autopiler.txt config file
    if (config_file() != 0) {

        printf("Please enter which compiler to use:\n> ");
        scanf("%s", compiler);
        printf("Please enter linking type:\n> ");
        scanf("%s", linking);
        printf("Please enter input file name:\n> ");
        scanf("%s", input_file);
        printf("Please enter ouput directory path:\n> ");
        scanf("%s", output_path);
        printf("Please enter ouput file name:\n> ");
        scanf("%s", output_file);
        printf("Please enter library files:\n> ");
        scanf("%s", library_files);
    }

    strcat(compiler, " ");
    strcat(linking, " ");
    strcat(input_path, "/");
    strcat(output_path, "/");

    char result[1000] = "";
    strcat(result, compiler);
    strcat(result, linking);
    strcat(result, input_path);
    strcat(result, input_file);
    if (output_path != "" || output_file != "") {
        strcat(result, output_flag);
        strcat(result, output_path);
        strcat(result, output_file);
        strcat(result, object_files);
    }
    if (library_files != "") {
        strcat(result, library_flag);
        strcat(result, library_files);
    }

    printf("\nScanning %s...\n", input_file);
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


