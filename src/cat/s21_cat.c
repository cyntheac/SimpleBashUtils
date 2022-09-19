#include "s21_cat.h"

char asciiSymbols[][255] = {
    [0] = "^@",      [1] = "^A",     [2] = "^B",     [3] = "^C",
    [4] = "^D",      [5] = "^E",     [6] = "^F",     [7] = "^G",
    [8] = "^H",      [9] = "\t",      [10] = "\n",    [11] = "^K",
    [12] = "^L",     [13] = "^M",    [14] = "^N",    [15] = "^O",
    [16] = "^P",     [17] = "^Q",    [18] = "^R",    [19] = "^S",
    [20] = "^T",     [21] = "^U",    [22] = "^V",    [23] = "^W",
    [24] = "^X",     [25] = "^Y",    [26] = "^Z",    [27] = "^[",
    [28] = "^\\",    [29] = "^]",    [30] = "^^",    [31] = "^_",
    [32] = " ",      [33] = "!",     [34] = "\"",    [35] = "#",
    [36] = "$",      [37] = "%",     [38] = "&",     [39] = "'",
    [40] = "(",      [41] = ")",     [42] = "*",     [43] = "+",
    [44] = ",",      [45] = "-",     [46] = ".",     [47] = "/",
    [48] = "0",      [49] = "1",     [50] = "2",     [51] = "3",
    [52] = "4",      [53] = "5",     [54] = "6",     [55] = "7",
    [56] = "8",      [57] = "9",     [58] = ":",     [59] = ";",
    [60] = "<",      [61] = "=",     [62] = ">",     [63] = "?",
    [64] = "@",      [65] = "A",     [66] = "B",     [67] = "C",
    [68] = "D",      [69] = "E",     [70] = "F",     [71] = "G",
    [72] = "H",      [73] = "I",     [74] = "J",     [75] = "K",
    [76] = "L",      [77] = "M",     [78] = "N",     [79] = "O",
    [80] = "P",      [81] = "Q",     [82] = "R",     [83] = "S",
    [84] = "T",      [85] = "U",     [86] = "V",     [87] = "W",
    [88] = "X",      [89] = "Y",     [90] = "Z",     [91] = "[",
    [92] = "\\",     [93] = "]",     [94] = "^",     [95] = "_",
    [96] = "`",      [97] = "a",     [98] = "b",     [99] = "c",
    [100] = "d",     [101] = "e",    [102] = "f",    [103] = "g",
    [104] = "h",     [105] = "i",    [106] = "j",    [107] = "k",
    [108] = "l",     [109] = "m",    [110] = "n",    [111] = "o",
    [112] = "p",     [113] = "q",    [114] = "r",    [115] = "s",
    [116] = "t",     [117] = "u",    [118] = "v",    [119] = "w",
    [120] = "x",     [121] = "y",    [122] = "z",    [123] = "{",
    [124] = "|",     [125] = "}",    [126] = "~",    [127] = "^?",
    [128] = "M-^@",  [129] = "M-^A", [130] = "M-^B", [131] = "M-^C",
    [132] = "M-^D",  [133] = "M-^E", [134] = "M-^F", [135] = "M-^G",
    [136] = "M-^H",  [137] = "M-^I", [138] = "M-^J", [139] = "M-^K",
    [140] = "M-^L",  [141] = "M-^M", [142] = "M-^N", [143] = "M-^O",
    [144] = "M-^P",  [145] = "M-^Q", [146] = "M-^R", [147] = "M-^S",
    [148] = "M-^T",  [149] = "M-^U", [150] = "M-^V", [151] = "M-^W",
    [152] = "M-^X",  [153] = "M-^Y", [154] = "M-^Z", [155] = "M-^[",
    [156] = "M-^\\", [157] = "M-^]", [158] = "M-^^", [159] = "M-^_",
};

char flagNames[][C_MAX_LINE_SIZE] = { "-n", "-b", "-e", "-t", "-s",
                                    "--number", "--number-nonblank",
                                    "-E", "-T", "--squeeze-blank", "NULL"};

int main(int argc, char * argv[]) {
    if (!argumentsValidation(argc, argv)) {
        argv[1][0] == '-' ? openFile(argc, argv, argv[1][1]) :
        openFile(argc, argv, 0);
    } else {
        printf("usage: cat [-flag] [file ...]\n");
    }
    return 0;
}

int argumentsValidation(int numOfArg, char **arg) {
    if ((numOfArg == 2 && arg[1][0] != '-') ||
        (numOfArg > 2 && !flagsValidation(arg[1]))) {
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
    int firstFilename = flag ? 2 : 1;
    for (int filename = firstFilename; filename < numOfArg; filename++) {
        FILE *file;
        file = fopen(arg[filename], "r");
        file ? flagIdentification(file, arg, flag) :
        printf("cat: %s: No such file or directory\n", arg[filename]);
        fclose(file);
    }
}

void flagIdentification(FILE *file, char **arg, char flag) {
    if (flag) {
        if (!strcmp(arg[1], flagNames[b]) || !strcmp(arg[1], flagNames[gnu_b]) ||
            !strcmp(arg[1], flagNames[n]) || !strcmp(arg[1], flagNames[gnu_n])) {
            catFlagsNB(file, arg[1]);
        } else if (!strcmp(arg[1], flagNames[gnu_e]) || !strcmp(arg[1], flagNames[gnu_t])) {
            catFlagsGnuET(file, arg[1]);
        } else if (!strcmp(arg[1], flagNames[e]) || !strcmp(arg[1], flagNames[t])) {
            catFlagsET(file, arg[1]);
        } else if (!strcmp(arg[1], flagNames[s])) {
            catFlagS(file);
        }
    } else {
        catWithoutFlags(file);
    }
}

void catWithoutFlags(FILE *file) {
    char charInLine;
    while ((charInLine = getc(file)) != EOF) {
        printf("%c", charInLine);
    }
}

void catFlagsNB(FILE *file, char *flag) {
    char lineInFile[MAX_LINE_SIZE];
    int lineCounter = 1;
    int charIndex = 0;
    while ((lineInFile[charIndex] = fgetc(file)) != EOF) {
        if (lineInFile[charIndex] == '\n' &&
            (!strcmp(flag, flagNames[b]) || !strcmp(flag, flagNames[gnu_b]))) {
            lineInFile[charIndex] = '\0';
            charIndex ? printf("%6d\t", lineCounter++) : pass;
            printf("%s\n", lineInFile);
            charIndex = 0;
            continue;
        } else if (lineInFile[charIndex] == '\n') {
            lineInFile[charIndex] = '\0';
            printf("%6d\t%s\n", lineCounter++, lineInFile);
            charIndex = 0;
            continue;
        }
        charIndex++;
    }
    lineInFile[charIndex] = '\0';
    charIndex ? printf("%6d\t", lineCounter++) : pass;
    printf("%s", lineInFile);
}

void catFlagsGnuET(FILE *file, char *flag) {
    char charInLine;
    while ((charInLine = getc(file)) != EOF) {
        if (charInLine == '\n' && !strcmp(flag, flagNames[gnu_e])) {
            printf("$\n");
            continue;
        } else if (charInLine == '\t' && !strcmp(flag, flagNames[gnu_t])) {
            printf("^I");
            continue;
        }
        printf("%c", charInLine);
    }
}

void catFlagsET(FILE *file, char *flag) {
    char charInLine;
    while ((charInLine = getc(file)) != EOF) {
        if (charInLine == '\n' && !strcmp(flag, flagNames[e])) {
            printf("$\n");
            continue;
        } else if (charInLine == '\t' && !strcmp(flag, flagNames[t])) {
            printf("^I");
            continue;
        }
        if ((int)((unsigned char)charInLine) > 159) {
            printf("%c", charInLine);
        } else {
            printf("%s", asciiSymbols[(int)((unsigned char)charInLine)]);
        }
    }
}

void catFlagS(FILE *file) {
    char lineInFile[MAX_LINE_SIZE];
    int charIndex = 0;
    int spaceCounter = 0;
    while ((lineInFile[charIndex] = fgetc(file)) != EOF) {
        if (lineInFile[charIndex] == '\n') {
            lineInFile[charIndex] = '\0';
            charIndex ? pass : spaceCounter++;
            spaceCounter > 1 ? pass : printf("%s\n", lineInFile);
            charIndex = 0;
            continue;
        }
        charIndex++;
        spaceCounter = 0;
    }
    lineInFile[charIndex] = '\0';
    printf("%s", lineInFile);
}
