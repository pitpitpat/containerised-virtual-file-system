#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "utility.h"
#include "superData.h"
#include "metaData.h"


void cfsWorkwith(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1){
        perror("open");
        printf("\n");
        return;
    }

    // MetaData MD;
    // MD.nodeid = 2;
    // strcpy(MD.filename, "Helloooo");
    // MD.size = 10;

    // printf("WRITE MD.nodeid: %d MD.filename: %s MD.size: %d\n", MD.nodeid, MD.filename, MD.size);
    // write(fd, &MD, sizeof(MetaData));

    SuperData SD;

    read(fd, &SD, sizeof(SuperData));
    printf("SuperData: SD.blockSize: %d SD.filenameSixe: %d SD.maxFileSize: %d SD.maxDirectoryFileNumber: %d\n", SD.blockSize, SD.filenameSixe, SD.maxFileSize, SD.maxDirectoryFileNumber);

    printf("Closing file %s\n", filename);
    close(fd);
}


void cfsCreateGetArguments(char **arguments) {
    char *previousToken = NULL, *token = strtok(NULL, " \t");

    while(token != NULL) {
        printf("%s\n", token);

        previousToken = token;
        token = strtok(NULL, " \t");

        if (!strcmp(previousToken, "-bs")) {
            arguments[0] = token;
        } else if (!strcmp(previousToken, "-fns")) {
            arguments[1] = token;
        } else if (!strcmp(previousToken, "-cfs")) {
            arguments[2] = token;
        } else if (!strcmp(previousToken, "-mdfn")) {
            arguments[3] = token;
        }
    }

    arguments[4] = previousToken;
}


void writeSuperData(SuperData SD, char *filename) {
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd = open(filename, O_CREAT | O_WRONLY, mode);
    if (fd == -1){
        perror("open");
        return;
    }

    printf("SuperData: SD.blockSize: %d SD.filenameSixe: %d SD.maxFileSize: %d SD.maxDirectoryFileNumber: %d\n", SD.blockSize, SD.filenameSixe, SD.maxFileSize, SD.maxDirectoryFileNumber);
    write(fd, &SD, sizeof(SuperData));

    close(fd);
}


void cfsCreateFillEmptyWithDefaultValues(char **arguments) {
    if (arguments[0] == NULL) arguments[0] = "512";
    if (arguments[1] == NULL) arguments[1] = "50";
    if (arguments[2] == NULL) arguments[2] = "5120";
    if (arguments[3] == NULL) arguments[3] = "6";
}


void cfsCreate() {
    char *arguments[5] = {NULL, NULL, NULL, NULL, NULL};
    char *filename = NULL;
    SuperData SD;

    cfsCreateGetArguments(arguments);
    cfsCreateFillEmptyWithDefaultValues(arguments);

    SD.blockSize = atoi(arguments[0]);
    SD.filenameSixe = atoi(arguments[1]);
    SD.maxFileSize = atoi(arguments[2]);
    SD.maxDirectoryFileNumber = atoi(arguments[3]);
    filename = arguments[4];

    if (filename == NULL) {
        printf("Error: No filename provided.\n");
        return;
    }

    writeSuperData(SD, filename);
}


void listenForCommands(){
    size_t len = 0;
    ssize_t nread;
    char *line = NULL;
    char *token = NULL;

    while(1){
        printf(">>> ");

        nread = getline(&line, &len, stdin);
        if (line[nread - 1] == '\n') line[nread - 1] = '\0';

        if(strcmp(line, "exit") == 0) break;

        token = strtok(line, " \t");

        if(token == NULL) continue;

        if(strcmp(token, "cfs_workwith") == 0) {
            token = strtok(NULL, " \t");
            cfsWorkwith(token);
        }
        else if(strcmp(token, "cfs_create") == 0) {
            cfsCreate();
        }
        else if(strcmp(token, "cfs_rm") == 0) {
            token = strtok(NULL, " \t");
            printf("cfs_rm %s\n", token);
        }
        else {
            printf("Command not recognized\n");
        }

        printf("\n");
    }

    free(line);
}


int main() {
    listenForCommands();
    return 0;
}
