#include "filehandler.h"
#include <string.h>
void freadhm(char *path, HashMap *hm) {
    FILE *fp = fopen(path, "r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    char *data = (char*) malloc(sizeof(char)*size);
    rewind(fp);
    fread(data, sizeof(char), size, fp);
    fclose(fp);
    printf("%s\n", data);
}