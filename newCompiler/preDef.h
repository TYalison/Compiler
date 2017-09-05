#ifndef _PREDEF_H_
#define _PREDEF_H_

//布尔常量
#define TRUE		1
#define FALSE		0

//最大值约束
#define LEVELMAX	1//分程序最大嵌套层次
#define BITMAX		5//标号最大值位数
#define INTMAXB		10//int最大值位数
#define IDMAX		64//标识符最大长度
#define ARRAYMAX	100
#define TABMAX		500//符号表最大长度
#define LABELMAX	500//标号最大值
#define STRMAX		500	//字符串表最大值
#define QUATMAX		500//四元式表最大值

//类别符
enum SYMBOL
{
	null,
	COLON, COMMA, SEMICOLON,
	CONSTSY, INTSY, CHARSY, VOIDSY, IFSY, ELSESY, SWITCHSY, CASESY, DEFAULTSY, WHILESY, RETURNSY, SCANFSY, PRINTFSY,/*保留字*/
	ASSIGN, PLUS, MINUS, TIMES, DIVI,/*算术运算符*/
	LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE,/*括号*/
	IDENT, MAIN, INTNUM, SCHAR, STRING,
	EQL, NEQ, GTR, GEQ, LSS, LEQ,/*逻辑运算符*/
	NEG, CMP, JMP, RFUNC, NFUNC, LDPAR, LDARY, NOP, SCANF, PRINTFS, LOCARRAY, LOCVAR, PRINTFE, RET, PROC, END, MPROC, MEND,/*四元式*/
	UNDEFSYM
};

//标识符种类
enum KIND
{
	CONSVAR, VAR, PROCE, FUNC, PARAM, ARRAY, TMPVAR
};

//错误
enum ERROR
{
	other,
	LONGID, KEYSAME, ZEROBEG, LONGINT, CHARCONS, SQLACK, ILSTR, LONGSTR,/*词法错误*/
	CASELACK, IDLACK, INTLACK, ASGLACK, CHARLACK, ILTYPE, ARRAYIDX, SEMILACK, PARENLACK, BRACKLACK, BRACELACK, COLONLACK, DFTLACK, ILPRINT, MAINLACK, PROGEND, ILFACTOR, ILRETYPE, ILSTAT,/*语法错误*/
	PARACONT, UNDEF, CONSASG, REDEF, RETVAL, SCANFPAR, PRINTFPAR/*语义错误*/
};
int errnum;

//结构定义
struct TOKEN
{
	enum SYMBOL sym;
	char value[STRMAX + 1];
};

//编译外部量
int line;
int GLOBAL;//全局标志
int retflag;
int DEBUG;
int paranum;
int paragot;

//词法分析相关
char CHAR;
struct TOKEN token;
int TOKEN_index;
int varlabx;

//语法分析相关
struct TOKEN next[3];//向前多扫描2个单词
int NEXT_index;
int FIRSTCASE;

//四元式
struct QUAT
{
	enum SYMBOL op;
	int result;
	int operand_1;
	int operand_2;
	int labx;//四元式在标号表中的下标
} quat[QUATMAX];
int QUAT_index;

//符号表
struct TAB
{
	char name[IDMAX + 1];
	enum KIND kind;
	enum SYMBOL type;
	int value;
	int arrdim;
} tab[TABMAX];
int TAB_index;

//数组表
int ATAB_index;

//分程序索引表
int btabx[LEVELMAX];
int BTABX_index;

//标号表
char labtab[LABELMAX][IDMAX + 1];
int LABTAB_index;

//字符串表
char stab[STRMAX][STRMAX + 1];
char strlab[STRMAX][IDMAX + 1];
int STAB_index;

//文件
FILE *in, *out, *data, *code, *quats;
char* FILEIN;

#endif
