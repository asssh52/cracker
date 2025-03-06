#include "../hpp/hack.hpp"
#include <sys/stat.h>

#define FILE_SIZE 464

enum exits{

    OK              = 0,
    FILE_NOT_FOUND  = 1,
    WRONG_FILE      = 2

};

int     crackProgramm       (const char* filename);
size_t  getFileSize         (const char* filename);


int crackProgramm(const char* filename){

    printf("got %s\n", filename);

    FILE* filePtr = fopen(filename, "r");
    if (!filePtr) return FILE_NOT_FOUND;

    size_t size = getFileSize(filename);
    if (size != FILE_SIZE) return WRONG_FILE;

    char* buffer = (char*)calloc(size, sizeof(char));

    fread(buffer, sizeof(char), size, filePtr);

    printf("pos 33: %x\n", buffer[33]);
    buffer[33] = 0xe9;                      // code of JMP
    buffer[34] = 0x32;                      // JMP addr
    buffer[35] = 0x00;                      // JMP addr
    printf("pos 33':%x\n", buffer[33]);

    FILE* fileOutPtr = fopen("hacked_file.com", "w");
    fwrite(buffer, sizeof(char), size, fileOutPtr);

    free(buffer);
    fclose(filePtr);
    fclose(fileOutPtr);

    return OK;
}

size_t getFileSize (const char* filename){

    size_t size = 0;

    struct stat st;
    stat(filename, &st);
    size = st.st_size;

    return size;
}

