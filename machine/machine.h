
//  pl0.h
//  Definitions for the abstract machine
//

#ifndef pl0_h
#define pl0_h

typedef struct {
    enum {
        NOP,
        ADD, SUB, MUL, DIV,
        EQU, LTH,
        LIT, LOD, STO,
        INT,
        JMP, JPC,
        RED, WRT,
        SWP
    } func_code;
    int a;
} Instruction;

void interpret(Instruction[], int);

#endif /* pl0_h */
