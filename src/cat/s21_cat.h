#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <stdio.h>
#include <string.h>
#define MAX_LINE_SIZE 4096
#define C_MAX_LINE_SIZE 256
#define pass (void)0

enum flagPosition { n, b, e, t, s, gnu_n, gnu_b, gnu_e, gnu_t, gnu_s };
int argumentsValidation(int numOfArg, char **arg);
int flagsValidation(char *flag);
void openFile(int numOfArg, char **arg, char flag);
void flagIdentification(FILE *file, char **arg, char flag);
void catWithoutFlags(FILE *file);
void catFlagsNB(FILE *file, char *flag);
void catFlagsGnuET(FILE *file, char *flag);
void catFlagsET(FILE *file, char *flag);
void catFlagS(FILE *file);

#endif  // SRC_CAT_S21_CAT_H_
