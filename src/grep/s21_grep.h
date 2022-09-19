#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <stdio.h>
#include <string.h>
#include <regex.h>
#define MAX_LINE_SIZE 4096
#define C_MAX_LINE_SIZE 256
#define pass (void)0

int argumentsValidation(int numOfArg, char **arg);
int flagsValidation(char *flag);
void openFile(int numOfArg, char **arg, char flag);
int printGrep(FILE *file, char *pattern, char *filename, int numOfArg, char flag);
int regexStatus(char *filename, char *lineInFile, char *pattern, int numOfArg,
                int *overlap, int lineCounter, int outro, char flag);
void printGrepWithoutFlags(char *filename, char *lineInFile, int numOfArg, int status);
void printGrepFlagC(char *filename, int numOfArg, int overlap);
void printGrepFlagV(char *filename, char *lineInFile, int numOfArg, int status);
int printGrepFlagL(char *filename, int status);
void printGrepFlagN(char *filename, char *lineInFile, int numOfArg, int lineCounter, int status);
void printGrepFlagsEI(char *filename, char *lineInFile, int numOfArg, int status);

#endif  // SRC_GREP_S21_GREP_H_
