#include "s21_grep.h"

char flagNames[][C_MAX_LINE_SIZE] = { "-e", "-i", "-v", "-c", "-l", "-n", "NULL"};

int main(int argc, char * argv[]) {
    if (!argumentsValidation(argc, argv)) {
        argv[1][0] == '-' ? openFile(argc, argv, argv[1][1]) :
        openFile(argc, argv, 0);
    } else {
        printf("usage: grep [-flag] [pattern] [file ...]\n");
    }
    return 0;
}

int argumentsValidation(int numOfArg, char **arg) {
    if ((numOfArg == 3 && arg[1][0] != '-') ||
        (numOfArg > 3 && !flagsValidation(arg[1]))) {
        return 0;
    }
    return 1;
}

int flagsValidation(char *flag) {
    int result = flag[0] == '-' ? 1 : 0;
    if (flag[0] == '-') {
        for (int flagName = 0; strcmp("NULL", flagNames[flagName]); flagName++) {
            if (!strcmp(flag, flagNames[flagName])) {
                return 0;
            }
        }
    }
    return result;
}

void openFile(int numOfArg, char **arg, char flag) {
    int firstFilename = flag ? 3 : 2;
    for (int filename = firstFilename; filename < numOfArg; filename++) {
        FILE *file;
        file = fopen(arg[filename], "r");
        file ? printGrep(file, arg[firstFilename - 1], arg[filename], numOfArg, flag) :
        printf("grep: %s: No such file or directory\n", arg[filename]);
        fclose(file);
    }
}

int printGrep(FILE *file, char *pattern, char *filename, int numOfArg, char flag) {
    char lineInFile[MAX_LINE_SIZE];
    int charIndex = 0;
    int lineCounter = 1;
    int overlap = 0;
    while ((lineInFile[charIndex] = fgetc(file)) != EOF) {
        if (lineInFile[charIndex] == '\n') {
            lineInFile[charIndex] = '\0';
            if (!regexStatus(filename, lineInFile, pattern, numOfArg, &overlap, lineCounter, 0, flag)) {
                return 0;
            }
            lineCounter++;
            charIndex = 0;
            continue;
        }
        charIndex++;
    }
    lineInFile[charIndex] = '\0';
    regexStatus(filename, lineInFile, pattern, numOfArg, &overlap, lineCounter, 1, flag);
    return 0;
}

int regexStatus(char *filename, char *lineInFile, char *pattern, int numOfArg,
                int *overlap, int lineCounter, int outro, char flag) {
    regex_t expr;
    int status;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    flag == 'i' ? regcomp(&expr, pattern, REG_ICASE) : regcomp(&expr, pattern, 0);
    status = regexec(&expr, lineInFile, nmatch, pmatch, 0);
    switch (flag) {
        case 'e':
        case 'i':
            printGrepFlagsEI(filename, lineInFile, numOfArg, status); break;
        case 'v': printGrepFlagV(filename, lineInFile, numOfArg, status); break;
        case 'c':
            *overlap += !status ? 1 : 0;
            outro ? printGrepFlagC(filename, numOfArg, *overlap) : pass;
            break;
        case 'l':
            if (!printGrepFlagL(filename, status)) {
                return 0;
            }
            break;
        case 'n': printGrepFlagN(filename, lineInFile, numOfArg, lineCounter, status); break;
        default: printGrepWithoutFlags(filename, lineInFile, numOfArg, status);
    }
    regfree(&expr);
    return 1;
}

void printGrepFlagC(char *filename, int numOfArg, int overlap) {
    numOfArg > 4 ? printf("%s:%d\n", filename, overlap) :
    printf("%d\n", overlap);
}

void printGrepFlagV(char *filename, char *lineInFile, int numOfArg, int status) {
    if (status && numOfArg == 4) {
        printf("%s\n", lineInFile);
    } else if (status && numOfArg > 4) {
        printf("%s:%s\n", filename, lineInFile);
    }
}

int printGrepFlagL(char *filename, int status) {
    if (!status) {
        printf("%s\n", filename);
        return 0;
    }
    return 1;
}

void printGrepFlagN(char *filename, char *lineInFile, int numOfArg, int lineCounter, int status) {
    if (!status && numOfArg == 4) {
        printf("%d:%s\n", lineCounter, lineInFile);
    } else if (!status && numOfArg > 4) {
        printf("%s:%d:%s\n", filename, lineCounter, lineInFile);
    }
}

void printGrepFlagsEI(char *filename, char *lineInFile, int numOfArg, int status) {
    if (!status && numOfArg == 4) {
        printf("%s\n", lineInFile);
    } else if (!status && numOfArg > 4) {
        printf("%s:%s\n", filename, lineInFile);
    }
}

void printGrepWithoutFlags(char *filename, char *lineInFile, int numOfArg, int status) {
    if (!status && numOfArg == 3) {
        printf("%s\n", lineInFile);
    } else if (!status && numOfArg > 3) {
        printf("%s:%s\n", filename, lineInFile);
    }
}
