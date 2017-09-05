#ifndef _PREDECL_H_
#define _PREDECL_H_

//词法分析部分
void errorSym(int errx);
void getChar();
int isSpace();
int isNull();
int isLetter();
int isDigit();
int isComma();
int isSemicolon();
int isSquote();
int isDquote();
int isAssign();
int isAscii();
int isBang();
int isPlus();
int isMinus();
int isTimes();
int isDivi();
int isLparen();
int isRparen();
int isLbrack();
int isRbrack();
int isLbrace();
int isNewline();
int isRbrace();
int isGtr();
int isLss();
int isColon();
void clearToken();
void catToken();
int reserver();
void Symbol();

//语法分析部分
void errorGram(int errx);
void initNext();
void newNext();
void transStr(int num, char str[]);
int transNum(char strnum[]);
void constDef();
void constDecl();
void varDef();
void varDecl();
void Parameter();
void Compound();
int preStat();
void Statlist(int lab);
int Condition(int lab, int nextlab);
int Constant();
int Factor();
int Term();
int Expression();
int preCase(int lab, int nextlab);
int singleCase(int labx, int nextlab, int tabx);
int Case(int lab, int nextlab, int tabx);
void Default(int labx, int nextlab);
int Statement(int lab, int nextlab);
int noParam(int tabx);
int fewParams(int ftabx, int exprtabx);
int valParam(int tabx);
int callFunct(int lab);
void callProc(int lab);
void valFunct();
void novalFunct();
void mainFunct();
void Program();

//语义分析及代码生成部分
void errorMean(int errx);
void enterTab(char name[], int kind, int type, int value, int dim);
int getType(int tabx);
int getTabtop();
int genStrlabx();
int genNewlab();
void genVarlab(char name[]);
void genQuat(int op, int operand_1, int operand_2, int result, int labx);
int locTab(char name[]);
int newKind(int tabx1, int tabx2);
int newType();
void printHead();
void printQuat(int index);
void finishBuild();
void genAsm(int qx);

//主函数部分
void init();

#endif
