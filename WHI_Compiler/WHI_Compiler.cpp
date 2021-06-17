//ParsingAys.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TK_LEN 100

const char kwList[11][10]
{
    "var","skip","read","write","if","then","else","fi","while","do","od"
};
enum TokenKind
{
    kw_var,//0
    kw_skip,//1
    kw_read,//2
    kw_write,//3
    kw_if,//4
    kw_then,//5
    kw_else,//6
    kw_fi,//7
    kw_while,//8
    kw_do,//9
    kw_od,//10
    add,//11
    sub,//12
    multip,//13
    division,//14
    negation,//15
    valuation,//:=16
    less,//<17
    equal,//=18
    comma,//,19
    semicolons,//;20
    left_brkt,//(21
    right_brkt,//)22
    nul,//23. 空格，回车，制表符
    eof,//24 文件结尾符
    identifier,//25. 标识符
    number//26.数字
};

enum LexErr
{
    invalid_chr,//0. 非法字符
    invalid_id,//1.非法标识符
    too_long_token,//2.token 溢出
    too_long_number//3.number溢出,最大65535
};
struct Token
{
    TokenKind type;
    char lexeme[MAX_TK_LEN + 1];
    int row;
    LexErr lex_err;
};

Token tkarray[1000];
int tk_num = 0;

int printErr(enum LexErr err_type, int row)//报错输出
{
    switch (err_type)
    {
    case 0:printf("[Lexical Analysis Error 0] at Line %d: invalid character.\n", row); break;
    case 1:printf("[Lexical Analysis Error 1] at Line %d: invalid identifier.\n", row); break;
    case 2:printf("[Lexical Analysis Error 2] at Line %d: too long token.\n", row); break;
    case 3:printf("[Lexical Analysis Error 3] at Line %d: constant number overflow.\n", row); break;
    default:printf("[Lexical Analysis Error 4] at Line %d: unknown error.\n", row); break;
    }
    return -1;//出错中止
}

int printToken(FILE* f, Token t)
{
    /*tkarray[tk_num].lexeme = t.lexeme;
    tkarray[tk_num].row = t.row;
    tkarray[tk_num].type = t.type;
    tk_num++;*/
    switch (t.type)
    {
    case 0: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 1: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 2: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 3: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 4: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 5: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 6: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 7: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 8: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 9: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 10: printf("[Keyword]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 11: printf("[Arithmetic Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 12: printf("[Arithmetic Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 13: printf("[Arithmetic Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 14: printf("[Arithmetic Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 15: printf("[Arithmetic Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 16: printf("[Assigning Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 17: printf("[logical Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break; break;
    case 18: printf("[logical Operator]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 19: printf("[Comma]\t\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 20: printf("[Semicolons]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 21: printf("[Left Brackets]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 22: printf("[Right Brackets]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
        // case 23:   nul,//23. 空格，回车，制表符
        // case 24:   eof,//24 文件结尾符
    case 25: printf("[Identifier]\t\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    case 26: printf("[Constant Number]\t%d\t%s\t%d\n", t.type, t.lexeme, t.row); fprintf(f, "%d\t%s\t%d\n", t.type, t.lexeme, t.row); break;
    default: printf("[Lexical Analysis Error 4]: unknown error.\n"); return -1;
    }
    return 0;
}

/*
char* getbc(char* curP, char c)//读取文件中的空白字符：空格，换行和制表符
{
    if (c == ' ' || c == '\t' || c == '\n')
    {
        curp++;
        getbc();
    }
    else
    {
        curp++;
        return curp;
    }
}
*/

void concat(char* tk, char c)//将当前字符与token中的字符串连接。
{
    char str[2];
    str[0] = c;
    str[1] = '\0';
    strncat(tk, str, 100 - strlen(tk));
}

int letter(char c)//是否为字母
{
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
        return 1;//true
    else
        return 0;//false
}

int digital(char c)//是否为数字
{
    if (c >= '0' && c <= '9')
        return 1;//true
    else
        return 0;//false
}
/*
int invalid(char c)//是否为非法字符
{
    if (letter(c) || digital(c) || )
    {
        return 1;
    }
    else
    {
        switch (c - '\0')
        {
        case 43:return 1;
        case 45:return 1;
        case 42:return 1;
        case 47:return 1;
        case 126:return 1;
        case 61:return 1;
        case 60:return 1;
        case 58:return 1;
        case 44:return 1;
        case 59:return 1;
        case 40:return 1;
        case 41:return 1;
        default:return 0;
        }
    }

}
*/

Token reverse(Token t)//对token中的字符串检查关键字表，如果是一个关键字，返回它的种别码，否则回送标识符的种别码25
{
    int i = 0;
    for (i = 0; i < 11; i++)
    {
        if (!strcmp(t.lexeme, kwList[i]))
        {
            t.type = (enum TokenKind)i;
            return t;
        }
    }
    t.type = (enum TokenKind)25;
    return t;
}

/*
char* retract(char* curp)
{
    curp--;
    return curp;
}
*/


//文件指针
FILE* Pfpr;
FILE* Pfpw;

//Token
//enum TokenKind
//{
//    kw_var,//0
//    kw_skip,//1
//    kw_read,//2
//    kw_write,//3
//    kw_if,//4
//    kw_then,//5
//    kw_else,//6
//    kw_fi,//7
//    kw_while,//8
//    kw_do,//9
//    kw_od,//10
//    add,//11
//    sub,//12
//    multip,//13
//    division,//14
//    negation,//15
//    valuation,//:=16
//    less,//<17
//    equal,//=18
//    comma,//,19
//    semicolons,//;20
//    left_brkt,//(21
//    right_brkt,//)22
//    nul,//23. 空格，回车，制表符
//    eof,//24 文件结尾符
//    identifier,//25. 标识符
//    number//26.数字
//};
//struct Token
//{
//    TokenKind type;
//    char lexeme[MAX_TK_LEN + 1];
//    int row;
//    LexErr lex_err;
//};

//递归下降函数声明
int ParsV(Token& t);
int ParsN(Token& t);
int ParsD1();
int ParsD();
int ParsF();
int ParsFS();
int ParsT();
int ParsTS();
int ParsE();
int ParsS();
int ParsX();
int ParsL();
int ParsP();
int ParsAys();

//关键字表
//const char kwList[11][10]
//{
//    "var","skip","read","write","if","then","else","fi","while","do","od"
//};



//符号表：the symbol table
struct Symbol
{
    char id[MAX_TK_LEN + 1];
    int addr;
    int value;
};
Symbol SymbolTab[100];
int SymbolNum = 0;
void mallocVar(char* id, int a, int v)
{
    strcpy(SymbolTab[a].id, id);
    SymbolTab[a].addr = a;
    SymbolTab[a].value = v;
    SymbolNum++;
}
int searchST(char* id)
{
    for (int i = 0; i < SymbolNum; i++)
    {
        if (strcmp(SymbolTab[i].id, id) == 0)
        {
            return i;//找到返回地址
        }
    }
    return -1;//找不到
}

enum OpCode
{
    nop,//空指令
    addi,//+ 1
    subi,//- 2
    muli,//* 3
    divi,// / 4
    equ,//==5
    lth,//<6
    lit,//lit a7
    lod,//lod a8
    sto,//sto a9
    inti,//int a分配a个存储空间10
    jmp,//jmp a
    jpc,//jpc a，如果栈顶为0，跳转到a
    red,//red a
    wrt,//输出
    swp//交换栈顶次栈顶
};
const char OpCodeList[16][10]
{
    "nop","add","sub","mul","div","equ","lth","lit","lod","sto","int","jmp","jpc","red","wrt","swp"
};
struct Instruction
{
    OpCode opcode = (OpCode)0;//nop
    int opnum = -1;//-1代表该指令没有操作数
};
int pc = 0;//指向指令地址（数组相对地址）
Instruction instructs[100];
void instApp(OpCode opcode, int num = -1)//生成一条指令
{
    instructs[pc].opcode = opcode;
    instructs[pc].opnum = num;
    pc++;
}
void instOpnum(int addr, int num)//回填指令操作数
{
    instructs[addr].opnum = num;
}
void printInstors()
{
    for (int i = 0; i < pc; i++)
    {
        fprintf(Pfpw, "%s", OpCodeList[instructs[i].opcode]);

        if (instructs[i].opnum == -1)
        {
            fprintf(Pfpw, "\n");
        }
        else
        {
            fprintf(Pfpw, " %d\n", instructs[i].opnum);
        }
    }
}

Token getToken()//读入Token
{
    if (feof(Pfpr))
    {
        puts("File end\nParsing Analysis Programme SUCCESS Finished\n");
        fclose(Pfpr); // 关闭文件
        fclose(Pfpw); // 关闭文件
        exit(0);
    }
    Token t;
    fscanf(Pfpr, "%d\t%s\t%d", &t.type, &t.lexeme, &t.row);
    printf("%d\t%s\t%d\n", t.type, t.lexeme, t.row);
    return t;
}
enum ParsErr//语法分析错误
{
    excepted_identifier,
    excepted_number,
    expected_right_brkt,
    expected_left_brkt,
    expected_equal_less,
    expected_multip_divi,
    expected_add_sub,
    excepted_skip,
    excepted_then,
    excepted_else,
    excepted_fi,
    excepted_do,
    excepted_od,
    excepted_valuation,
    excepted_var,
    expected_semicolons
};
void ParsError(int row, ParsErr err)//语法分析出错处理
{
    switch (err)
    {
    case 0: printf("[Parsing Analysis Error 0] at Line %d: expected an identifier.\n", row); break;
    case 1: printf("[Parsing Analysis Error 1] at Line %d: expected a number.\n", row); break;
    case 2: printf("[Parsing Analysis Error 2] at Line %d: expected a ')'.\n", row); break;
    case 3: printf("[Parsing Analysis Error 3] at Line %d: expected a '(' or a '~'.\n", row); break;
    case 4: printf("[Parsing Analysis Error 4] at Line %d: expected a '=' or a '<'.\n", row); break;
    case 5: printf("[Parsing Analysis Error 5] at Line %d: expected a '*' or a '/'.\n", row); break;
    case 6: printf("[Parsing Analysis Error 6] at Line %d: expected a '+' or a '-'.\n", row); break;
    case 7: printf("[Parsing Analysis Error 7] at Line %d: expected 'skip' or  'read' or 'write' or 'if' or 'while' or an identifier.\n", row); break;
    case 8: printf("[Parsing Analysis Error 8] at Line %d: expected 'then'.\n", row); break;
    case 9: printf("[Parsing Analysis Error 9] at Line %d: expected 'else'.\n", row); break;
    case 10: printf("[Parsing Analysis Error 10] at Line %d: expected 'fi'.\n", row); break;
    case 11: printf("[Parsing Analysis Error 11] at Line %d: expected 'do'.\n", row); break;
    case 12: printf("[Parsing Analysis Error 12] at Line %d: expected 'od'.\n", row); break;
    case 13: printf("[Parsing Analysis Error 13] at Line %d: expected a ':='.\n", row); break;
    case 14: printf("[Parsing Analysis Error 14] at Line %d: expected 'var'.\n", row); break;
    case 15: printf("[Parsing Analysis Error 15] at Line %d: expected ';'.\n", row); break;
    default: printf("[Parsing Analysis Error n] at Line %d: unknown error.\n", row);
    }
}
enum SemtErr
{
    undefined_var,//未定义的标识符
    redifined_var//标识符重定义
};
void SemanticError(int row, SemtErr err)
{
    switch (err)
    {
    case 0:printf("[Semantic Analysis Error 0] at Line %d: undefined identifier.\n", row); break;
    case 1:printf("[Semantic Analysis Error 1] at Line %d: redefined identifier.\n", row); break;
    default: printf("[Semantic Analysis Error n] at Line %d: unknown error.\n", row);
    }
}
//递归下降子过程
int ParsV(Token& t)//V ::= C{C|G}识别是否为标识符
{
    t = getToken();
    if (t.type == identifier)//是标识符
    {
        /*在这里写生成代码*/
        return 1;
    }
    else
    {
        //ParsError(t.row, excepted_identifier);
        return 0;
    }
}
int ParsN(Token& t)//N ::= G{G}识别是否为数字
{
    t = getToken();
    if (t.type == number)//是标识符
    {
        /*在这里写生成代码*/
        return 1;
    }
    else
    {
        //ParsError(t.row, excepted_number);
        return 0;
    }
}
int ParsD()//D ::= N|V|(E)|~E
{
    char str[100];
    fgets(str, 100, Pfpr);
    int n = strlen(str);
    if (n == 1)
    {
        fgets(str, 100, Pfpr);
        n = strlen(str);
    }
    fseek(Pfpr, 0 - n - 1, SEEK_CUR);
    Token var;
    if (ParsV(var))
    {
        /*在这里写生成代码*/
        int varaddr = searchST(var.lexeme);
        instApp(lod, varaddr);
        return 1;
    }
    else
    {
        fseek(Pfpr, 0 - n + 1, SEEK_CUR);
        Token num;
        if (ParsN(num))
        {
            /*在这里写生成代码:lit c*/
            instApp(lit, atoi(num.lexeme));//生成判断是否相等代码:equ
            return 1;
        }
        else
        {
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            Token t = getToken();
            if (t.type == left_brkt)
            {
                if (ParsE())
                {
                    Token t1 = getToken();
                    if (t1.type == right_brkt)
                    {
                        /*在这里写生成代码*/
                        return 1;
                    }
                    else
                    {
                        ParsError(t1.row, expected_right_brkt);
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }

            }
            else if (t.type == negation)
            {
                if (ParsE())
                {
                    //生成代码lit 0,equ
                    instApp(lit, 0);
                    instApp(equ);
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                ParsError(t.row, expected_left_brkt);
                return 0;
            }
        }
    }

}
int ParsD1()//D1 ::= '='D|'<'D
{
    Token t = getToken();
    if (t.type == equal)//D1 ::= '='D
    {
        if (ParsD())
        {
            instApp(equ);//生成判断是否相等代码:equ
            return 1;
        }
        else
            return 0;
    }
    else if (t.type == less)//D1 ::= '<'D
    {
        if (ParsD())
        {
            instApp(lth);//生成判断是否小于代码:lth
            return 1;
        }
        else
            return 0;
    }
    else
    {
        ParsError(t.row, expected_equal_less);//expected = or <
        return 0;
    }
}
int ParsF()//F ::= D[D1]
{
    if (ParsD())
    {
        char str[100];
        fgets(str, 100, Pfpr);
        int n = strlen(str);
        if (n == 1)
        {
            fgets(str, 100, Pfpr);
            n = strlen(str);
        }
        fseek(Pfpr, 0 - n - 1, SEEK_CUR);
        Token tk = getToken();
        if (tk.type == equal || tk.type == less)
        {
            //fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            ParsD1();
        }
        else
        {
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
int ParsFS()//FS ::= '*'F[FS]|'/'F[FS]
{
    char str[100];
    fgets(str, 100, Pfpr);
    int n = strlen(str);
    if (n == 1)
    {
        fgets(str, 100, Pfpr);
        n = strlen(str);
    }
    fseek(Pfpr, 0 - n - 1, SEEK_CUR);

    Token tk = getToken();
    if (tk.type == multip)
    {
        if (ParsF())
        {
            instApp(muli);
            char str[100];
            fgets(str, 100, Pfpr);
            int n = strlen(str);
            if (n == 1)
            {
                fgets(str, 100, Pfpr);
                n = strlen(str);
            }
            fseek(Pfpr, 0 - n - 1, SEEK_CUR);
            Token tk = getToken();
            if (tk.type == multip || tk.type == division)
            {
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);
                if (ParsFS())
                    return 1;
                else
                    return 0;
            }
            else
            {
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    else if (tk.type == division)
    {
        if (ParsF())
        {
            instApp(divi);
            char str[100];
            fgets(str, 100, Pfpr);
            int n = strlen(str);
            if (n == 1)
            {
                fgets(str, 100, Pfpr);
                n = strlen(str);
            }
            fseek(Pfpr, 0 - n - 1, SEEK_CUR);
            Token tk = getToken();
            if (tk.type == multip || tk.type == division)
            {
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);
                if (ParsFS())
                    return 1;
                else
                    return 0;
            }
            else
            {
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        ParsError(tk.row, expected_multip_divi);
        return 0;
    }
}
int ParsT()//T ::= F[FS]
{
    if (ParsF())
    {
        char str[100];
        fgets(str, 100, Pfpr);
        int n = strlen(str);
        if (n == 1)
        {
            fgets(str, 100, Pfpr);
            n = strlen(str);
        }
        fseek(Pfpr, 0 - n - 1, SEEK_CUR);
        Token tk = getToken();
        if (tk.type == multip)
        {
            //instApp(muli);//生成乘法指令
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            if (ParsFS())
            {
                return 1;
            }
            else
                return 0;
        }
        else if (tk.type == division)
        {
            //instApp(divi);//生成除法指令
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            if (ParsFS())
            {
                return 1;
            }
            else
                return 0;
        }
        else
        {
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
int ParsTS()
{
    Token tk = getToken();
    if (tk.type == add)
    {
        if (ParsT())
        {
            instApp(addi);//生成加法代码
            char str[100];
            fgets(str, 100, Pfpr);
            int n = strlen(str);
            if (n == 1)
            {
                fgets(str, 100, Pfpr);
                n = strlen(str);
            }
            fseek(Pfpr, 0 - n - 1, SEEK_CUR);
            Token tk = getToken();
            if (tk.type == add || tk.type == sub)
            {
                if (ParsTS())
                {
                    fseek(Pfpr, 0 - n + 1, SEEK_CUR);
                    return 1;
                }
                else
                    return 0;
            }
            else
            {
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (tk.type == sub)
    {
        if (ParsT())
        {
            instApp(subi);//生成减法代码
            char str[100];
            fgets(str, 100, Pfpr);
            int n = strlen(str);
            if (n == 1)
            {
                fgets(str, 100, Pfpr);
                n = strlen(str);
            }
            fseek(Pfpr, 0 - n - 1, SEEK_CUR);
            Token tk = getToken();
            if (tk.type == add || tk.type == sub)
            {
                if (ParsTS())
                    return 1;
                else
                    return 0;
            }
            else
            {
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        ParsError(tk.row, expected_add_sub);
        return 0;
    }
}
int ParsE()
{
    if (ParsT())
    {
        char str[100];
        fgets(str, 100, Pfpr);
        int n = strlen(str);
        if (n == 1)
        {
            fgets(str, 100, Pfpr);
            n = strlen(str);
        }
        fseek(Pfpr, 0 - n - 1, SEEK_CUR);
        Token tk = getToken();
        if (tk.type == add || tk.type == sub)
        {
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            if (ParsTS())
            {
                return 1;
            }
            else
                return 0;
        }
        else
        {
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
int ParsS()
{
    char str[100];
    fgets(str, 100, Pfpr);
    int n = strlen(str);
    if (n == 1)
    {
        fgets(str, 100, Pfpr);
        n = strlen(str);
    }
    fseek(Pfpr, 0 - n - 1, SEEK_CUR);
    Token t = getToken();
    if (t.type == kw_skip)
    {
        instApp(nop);//skip生成代码nop空指令
        return 1;
    }
    else if (t.type == kw_read)
    {
        Token t1 = getToken();
        Token var;
        if (t1.type == left_brkt)
        {
            if (ParsV(var))
            {
                int adr = searchST(var.lexeme);
                if (adr != -1)//变量是否存在符号表中（是否定义）
                {
                    //生成代码red 变量地址
                    instApp(red, adr);
                    Token t2 = getToken();
                    if (t2.type == right_brkt)
                    {
                        return 1;
                    }
                    else
                    {
                        ParsError(t2.row, expected_right_brkt);
                        return 0;
                    }
                }
                else
                {
                    SemanticError(t1.row, undefined_var);
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            ParsError(t1.row, expected_left_brkt);
            return 0;
        }
    }
    else if (t.type == kw_write)
    {
        Token t1 = getToken();
        if (t1.type == left_brkt)
        {
            if (ParsE())
            {
                Token t2 = getToken();
                if (t2.type == right_brkt)
                {
                    instApp(wrt);//生成代码wrt，机器应该输出E的结果
                    return 1;
                }
                else
                {
                    ParsError(t2.row, expected_right_brkt);
                    return 0;
                }
            }
            else
            {

                return 0;
            }
        }
        else
        {
            ParsError(t1.row, expected_left_brkt);
            return 0;
        }
    }
    else if (t.type == kw_if)
    {
        if (ParsE())
        {
            //生成代码jpc条件跳转
            int jpcaddr = pc;//记录当前jpc地址
            instApp(jpc);//需要在else处回填跳转地址
            Token t1 = getToken();
            if (t1.type == kw_then)
            {
                if (ParsL())
                {
                    //if判断成功后，if执行完毕后，跳转到fi
                    int jmpaddr = pc;//记录当前jmp地址
                    instApp(jmp);//需要在fi处回填跳转地址
                    Token t2 = getToken();
                    if (t2.type == kw_else)
                    {
                        instOpnum(jpcaddr, pc);//if判断失败后jpc跳转到else
                        if (ParsL())
                        {
                            Token t3 = getToken();
                            if (t3.type == kw_fi)
                            {
                                instOpnum(jmpaddr, pc);//if执行完毕后jmp跳转到fi
                                return 1;
                            }
                            else
                            {
                                ParsError(t3.row, excepted_fi);
                                return 0;
                            }
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        ParsError(t2.row, excepted_else);
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                ParsError(t1.row, excepted_then);
                return 0;
            }
        }
    }
    else if (t.type == kw_while)
    {
        int whileaddr = pc;//记录循环开始时的地址
        if (ParsE())
        {
            //生成条件跳转指令jpc，如果不满足条件跳转到od
            int jpcaddr = pc;//记录当前jpc地址
            instApp(jpc);//需要在od处回填跳转地址

            Token t1 = getToken();
            if (t1.type == kw_do)
            {
                if (ParsL())
                {
                    //生成无条件跳转指令jmp，回到循环判断处
                    instApp(jmp, whileaddr);

                    Token t2 = getToken();
                    if (t2.type == kw_od)
                    {
                        instOpnum(jpcaddr, pc);//条件判断失败后jpc跳转到od
                        return 1;
                    }
                    else
                    {
                        ParsError(t2.row, excepted_od);
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                ParsError(t1.row, excepted_do);
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
        Token var;
        if (ParsV(var))
        {
            int adr = searchST(var.lexeme);
            if (adr != -1)//变量是否存在符号表中（是否定义）
            {//存在
                Token t1 = getToken();
                if (t1.type == valuation)
                {
                    if (ParsE())
                    {
                        //instApp(lit);//lit里的操作数是E的计算结果
                        instApp(sto, adr);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    ParsError(t1.row, excepted_valuation);
                }
            }
            else//不存在
            {
                SemanticError(var.row, undefined_var);
                return 0;
            }

        }
        else
        {
            ParsError(t.row, excepted_skip);
            return 0;
        }
    }
}
int ParsL()
{
    if (ParsS())
    {
        char str[100];
        fgets(str, 100, Pfpr);
        int n = strlen(str);//计算下一个此Token的长度
        if (n == 1)
        {
            fgets(str, 100, Pfpr);
            n = strlen(str);
        }
        fseek(Pfpr, 0 - n - 1, SEEK_CUR);
        Token tk = getToken();//向前看一个Token
        if (tk.type == semicolons)
        {
            int r = ParsL();
            if (r)
                return 1;
            else
                return 0;
        }
        else
        {
            fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
            return 1;
        }
    }
    else
    {
        return 1;
    }
}
int ParsX()
{
    Token t = getToken();
    if (t.type == kw_var)
    {
        int varnum = 0;//这一条语句定义的变量数
        int intaddr = pc;//int a这一条语句的地址
        instApp(inti);//生成一条指令，int a,但是int的操作数a需要循环完毕才能回填varnum
        Token var;
        if (ParsV(var))
        {
            mallocVar(var.lexeme, varnum, 0);
            instApp(lit, 0);
            instApp(sto, varnum);
            varnum++;
            char str[100];
            fgets(str, 100, Pfpr);
            int n = strlen(str);
            if (n == 1)
            {
                fgets(str, 100, Pfpr);
                n = strlen(str);
            }
            fseek(Pfpr, 0 - n - 1, SEEK_CUR);
        flag: Token tk = getToken();
            if (tk.type == comma)
            {
                if (ParsV(var))
                {
                    mallocVar(var.lexeme, varnum, 0);
                    instApp(lit, 0);
                    instApp(sto, varnum);
                    varnum++;
                    //return 1;
                    goto flag;
                }
                else
                {
                    ParsError(tk.row, excepted_identifier);
                    return 0;
                }
            }
            else
            {
                instOpnum(intaddr, varnum);//回填int a指令的操作数数a = varnum
                fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        ParsError(t.row, excepted_var);
        return 0;
    }
}
int ParsP()
{

    char str[100];
    fgets(str, 100, Pfpr);
    int n = strlen(str);
    if (n == 1)
    {
        fgets(str, 100, Pfpr);
        n = strlen(str);
    }
    fseek(Pfpr, 0 - n - 1, SEEK_CUR);
    Token tk = getToken();
    if (tk.type == kw_var)
    {
        //rewind(Pfpr);
        fseek(Pfpr, 0 - n + 1, SEEK_CUR);
        if (ParsX())
        {
            //fseek(Pfpr, 0 - n + 1, SEEK_CUR);
            Token t1 = getToken();
            if (t1.type == semicolons)
            {
                if (ParsL())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                ParsError(t1.row, expected_semicolons);
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        fseek(Pfpr, 0 - n + 1, SEEK_CUR);//回退到上一行
        if (ParsL())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
int ParsAys()
{
    if (ParsP())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int LexAys(FILE* fpr, FILE* fpw)
{
    char c;//当前从文件读入的字符
    char tk[MAX_TK_LEN + 1];//存放当前单词符号
    int row = 1;//记录当前行数,从第一行开始
    while (1)
    {
        c = fgetc(fpr);
        if (feof(fpr))
        {
            break;
        }
        else if (c == ' ' || c == '\t' || c == '\n')
        {
            if (c == '\n')
            {
                row++;
            }
            continue;
        }
        else
        {
            if (letter(c))//identifier or keyword
            {
                int i = 0;
                tk[0] = c;
                tk[1] = '\0';
                while (1)
                {
                    i++;
                    if (i > MAX_TK_LEN)//too long token error
                    {
                        int type = 2;
                        printErr((enum LexErr)type, row);
                        return -1;
                    }
                    char ch = fgetc(fpr);
                    if (letter(ch) || digital(ch))
                    {
                        concat(tk, ch);
                    }
                    else if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',' || ch == ';' || ch == ':' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '(' || ch == ')')//end of identifier
                    {
                        Token t;
                        strcpy(t.lexeme, tk);
                        t.type = (enum TokenKind)25;
                        t = reverse(t);
                        t.row = row;
                        printToken(fpw, t);
                        ungetc(ch, fpr);
                        break;
                    }
                    else//invalid identifier error
                    {
                        int type = 1;
                        printErr((enum LexErr)type, row);
                        return -1;
                    }
                }
            }
            else if (digital(c))//number
            {

                int i = 1;
                tk[0] = c;
                tk[1] = '\0';
                while (1)
                {
                    char ch;
                    ch = fgetc(fpr);
                    if (digital(ch))
                    {
                        concat(tk, ch);
                        continue;
                    }
                    else if (letter(ch))//invalid identifier error
                    {
                        int type = 1;
                        printErr((enum LexErr)type, row);
                        return -1;
                    }
                    else if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',' || ch == ';' || ch == ':' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '(' || ch == ')')
                    {
                        long int n = atol(tk);
                        if (n > 65535)//too long number error
                        {
                            int type = 3;
                            printErr((enum LexErr)type, row);
                            return -1;
                        }
                        else
                        {
                            Token t;
                            strcpy(t.lexeme, tk);
                            t.type = (enum TokenKind)26;
                            t.row = row;
                            printToken(fpw, t);
                            ungetc(ch, fpr);
                            break;
                        }
                    }
                    else//invalid character error
                    {
                        int type = 0;
                        printErr((enum LexErr)type, row);
                        return -1;
                    }
                }
            }
            else if (c == ':')//:=
            {
                tk[0] = c;
                tk[1] = '\0';
                c = fgetc(fpr);
                if (c == '=')
                {
                    concat(tk, c);
                    Token t;
                    strcpy(t.lexeme, ":=");
                    t.type = (enum TokenKind)16;
                    t.row = row;
                    printToken(fpw, t);
                }
                else//invalid character error
                {
                    int type = 0;
                    printErr((enum LexErr)type, row);
                    return -1;
                }
            }
            else if (c == '+')//+
            {
                Token t;
                strcpy(t.lexeme, "+");
                t.type = (enum TokenKind)11;
                t.row = row;
                printToken(fpw, t);

            }
            else if (c == '-')//-
            {
                Token t;
                strcpy(t.lexeme, "-");
                t.type = (enum TokenKind)12;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == '*')//*
            {
                Token t;
                strcpy(t.lexeme, "*");
                t.type = (enum TokenKind)13;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == '/')//'/'
            {
                Token t;
                strcpy(t.lexeme, "/");
                t.type = (enum TokenKind)14;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == '~')//~
            {
                Token t;
                strcpy(t.lexeme, "~");
                t.type = (enum TokenKind)15;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == '=')//<
            {
                Token t;
                strcpy(t.lexeme, "=");
                t.type = (enum TokenKind)18;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == '<')//<
            {
                Token t;
                strcpy(t.lexeme, "<");
                t.type = (enum TokenKind)17;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == ',')//,
            {
                Token t;
                strcpy(t.lexeme, ",");
                t.type = (enum TokenKind)19;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == ';')//;
            {
                Token t;
                strcpy(t.lexeme, ";");
                t.type = (enum TokenKind)20;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == '(')//(
            {
                Token t;
                strcpy(t.lexeme, "(");
                t.type = (enum TokenKind)21;
                t.row = row;
                printToken(fpw, t);
            }
            else if (c == ')')//)
            {
                Token t;
                strcpy(t.lexeme, ")");
                t.type = (enum TokenKind)22;
                t.row = row;
                printToken(fpw, t);
            }
            else//invalid character error
            {
                int type = 0;
                printErr((enum LexErr)type, row);
                return -1;
            }
        }
    }
    return 0;
}

int main()
{
    char filename[101];
    char fin[100];
    char fout[100];
    // char path[50] = "F:\\Compiler\\";
    char pathr[50] = "F:\\Compiler\\Programme\\";
    char pathw[50] = "F:\\Compiler\\LexicalResult\\";
    strcpy(fin, pathr);
    strcpy(fout, pathw);
    char fnamein[50];
    printf("Please input programme filename: \n");
    scanf("%s", fnamein);
    strcat(fin, fnamein);
    strcat(fin, ".txt");
    strcat(fout, fnamein);
    strcat(fout, "_LexResult.txt");
    int state = 0;//表示词法分析器的结束状态
    printf("Lexical Analysising...\n");
    //printf("Please input file path\n");
    //gets_s(filename);//gets已从C11中删除，使用gets_s代替，只接受字符数组指针
    //filename[100] = '\0';
    FILE* fpr = fopen(fin, "r");
    rewind(fpr);
    if (fpr == NULL) //若打开文件失败，fopen会返回NULL
    {
        puts("Fail to open programme file!\n");
        puts("Lexical Analysis Programme ABORTED\n");
        //exit(1);
    }

    FILE* fpw = fopen(fout, "w");
    if (fpr == NULL) //若打开文件失败，fopen会返回NULL
    {
        puts("Fail to open result file!\n");
        puts("Lexical Analysis Programme ABORTED\n");
        exit(1);
    }

    state = LexAys(fpr, fpw);
    if (state == -1)
    {
        puts("Lexical Analysis Programme EXIT with ERROR\n");
    }
    else
    {
        puts("Lexical Analysis Programme SUCCESS Finished\n");
    }

    fclose(fpr); // 关闭文件
    fclose(fpw); // 关闭文件

    char Pfout[100];
    char Ppathw[50] = "F:\\Compiler\\FinalResult\\";
    strcpy(Pfout, Ppathw);
    strcat(Pfout, fnamein);
    strcat(Pfout, "_FinalResult.txt");
    int state_parsing = 0;//语法分析器的结束状态
    printf("Parsing Analysising...\n");
    Pfpr = fopen(fout, "r");
    rewind(Pfpr);
    if (Pfpr == NULL) //若打开文件失败，fopen会返回NULL
    {
        puts("Fail to open programme file!\n");
        puts("Lexical Analysis Programme ABORTED\n");
        //exit(1);
    }
    Pfpw = fopen(Pfout, "w");
    if (Pfpr == NULL) //若打开文件失败，fopen会返回NULL
    {
        puts("Fail to open result file!\n");
        puts("Lexical Analysis Programme ABORTED\n");
        exit(1);
    }
    state_parsing = ParsAys();
    if (state_parsing == 0)
    {
        puts("Parsing Analysis Programme EXIT with ERROR\n");
    }
    else
    {
        puts("Parsing Analysis Programme SUCCESS Finished\n");
    }
    printInstors();
    fclose(Pfpr); // 关闭文件
    fclose(Pfpw); // 关闭文件

    return 0;
}
