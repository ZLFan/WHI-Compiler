
//
//  pl0.c
//  PL0Machine
//

#include <stdio.h>

#include "machine.h"

void interpret(Instruction code[], int end) {

    const int stack_sz = 500;
    int s[500];
    int t = -1;

    Instruction inst;
    int tmp;

    int p = 0;

    while (p < end) {

        inst = code[p];
        p++;

        switch (inst.func_code)
        {
            case NOP:
                break;
            case ADD:
                t--;
                s[t] = s[t] + s[t + 1];
                break;
            case SUB:
                t--;
                s[t] = s[t] - s[t + 1];
                break;
            case MUL:
                t--;
                s[t] = s[t] * s[t + 1];
                break;
            case DIV:
                t--;
                s[t] = s[t] / s[t + 1];
                break;
            case EQU:
                t--;
                s[t] = (s[t] == s[t + 1]);
                break;
            case LTH:
                t--;
                s[t] = (s[t] < s[t + 1]);
                break;
            case LIT:
                t++;
                s[t] = inst.a;
                break;
            case LOD:
                t++;
                s[t] = s[inst.a];
                break;
            case STO:
                s[inst.a] = s[t];
                t--;
                break;
            case INT:
                t += inst.a;
                break;
            case JMP:
                p = inst.a;
                break;
            case JPC:
                if (s[t] == 0) {
                    p = inst.a;
                }
                t--;
                break;
            case RED:
                scanf("%d", s + inst.a);
                break;
            case WRT:
                printf("%d\n", s[t]);
                t--;
                break;
            case SWP:
                tmp = s[t];
                s[t] = s[t - 1];
                s[t - 1] = tmp;
                break;
            default:    // should be unreachable
                printf("Error: Unsupported opcode: %d\n", inst.func_code);
                return;
        }

    }

}

