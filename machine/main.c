#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "machine.h"

const int max_code = 1000;

int run_code(FILE*);

int main(int argc, const char * argv[]) {

    printf("START\n");

    //const char* infile_name = argv[1];
    char infile_name[200] = "F:\\Compiler\\FinalResult\\";
    char filname[50];
    printf("Please input filename:\n");
    scanf("%s", filname);
    strcat(infile_name, filname);
    strcat(infile_name, ".txt");
    FILE* fp = fopen(infile_name, "r");
    run_code(fp);
    fclose(fp);

    printf("END\n");

    return 0;
}

int run_code(FILE* fp) {

    char c;
    int param;
    Instruction code[1000];

    int p = 0;

    while ((c = fgetc(fp)) != EOF) {

        while (isspace(c))
            c = fgetc(fp);
        if (c == EOF)
            break;

        // read the opcode
        char op_str[4];
        op_str[0] = c;
        op_str[1] = fgetc(fp);
        op_str[2] = fgetc(fp);
        op_str[3] = '\0';

        int op_code;
        if (strncmp(op_str, "nop", 3) == 0) {
            op_code = NOP;
        } else if (strncmp(op_str, "add", 3) == 0) {
            op_code = ADD;
        } else if (strncmp(op_str, "sub", 3) == 0) {
            op_code = SUB;
        } else if (strncmp(op_str, "mul", 3) == 0) {
            op_code = MUL;
        } else if (strncmp(op_str, "div", 3) == 0) {
            op_code = DIV;
        } else if (strncmp(op_str, "equ", 3) == 0) {
            op_code = EQU;
        } else if (strncmp(op_str, "lth", 3) == 0) {
            op_code = LTH;
        } else if (strncmp(op_str, "lit", 3) == 0) {
            op_code = LIT;
        } else if (strncmp(op_str, "lod", 3) == 0) {
            op_code = LOD;
        } else if (strncmp(op_str, "sto", 3) == 0) {
            op_code = STO;
        } else if (strncmp(op_str, "int", 3) == 0) {
            op_code = INT;
        } else if (strncmp(op_str, "jmp", 3) == 0) {
            op_code = JMP;
        } else if (strncmp(op_str, "jpc", 3) == 0) {
            op_code = JPC;
        } else if (strncmp(op_str, "red", 3) == 0) {
            op_code = RED;
        } else if (strncmp(op_str, "wrt", 3) == 0) {
            op_code = WRT;
        } else if (strncmp(op_str, "swp", 3) == 0) {
            op_code = SWP;
        } else {
            printf("Error: Unsupported opcode: %s\n", op_str);
            return 1;
        }

        if (!isspace(c = fgetc(fp))) {
            printf("Error: Unsupported opcode: %s\n", op_str);
            return 1;
        }

        if (LIT == op_code || LOD == op_code || STO == op_code ||
            INT == op_code || JMP == op_code || JPC == op_code ||
            RED == op_code)
        {
            fscanf(fp, "%d", &param);
        }

        code[p].func_code = op_code;
        code[p].a = param;
        p++;
    }

    interpret(code, p);

    return 0;

}
