#pragma once

enum options
{
    BUFF_ONLY = 1,
    STRS_ONLY = 2, //Хотим мы записать буфер, строки или и то, и другое
    BOTH = 3
};

int fileRead(char *fileName, char** text ,char ***strPointer, int *sizeOfFile, int *numberOfStrings, int option);