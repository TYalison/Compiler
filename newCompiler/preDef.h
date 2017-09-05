#ifndef _PREDEF_H_
#define _PREDEF_H_

//��������
#define TRUE		1
#define FALSE		0

//���ֵԼ��
#define LEVELMAX	1//�ֳ������Ƕ�ײ��
#define BITMAX		5//������ֵλ��
#define INTMAXB		10//int���ֵλ��
#define IDMAX		64//��ʶ����󳤶�
#define ARRAYMAX	100
#define TABMAX		500//���ű���󳤶�
#define LABELMAX	500//������ֵ
#define STRMAX		500	//�ַ��������ֵ
#define QUATMAX		500//��Ԫʽ�����ֵ

//����
enum SYMBOL
{
	null,
	COLON, COMMA, SEMICOLON,
	CONSTSY, INTSY, CHARSY, VOIDSY, IFSY, ELSESY, SWITCHSY, CASESY, DEFAULTSY, WHILESY, RETURNSY, SCANFSY, PRINTFSY,/*������*/
	ASSIGN, PLUS, MINUS, TIMES, DIVI,/*���������*/
	LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE,/*����*/
	IDENT, MAIN, INTNUM, SCHAR, STRING,
	EQL, NEQ, GTR, GEQ, LSS, LEQ,/*�߼������*/
	NEG, CMP, JMP, RFUNC, NFUNC, LDPAR, LDARY, NOP, SCANF, PRINTFS, LOCARRAY, LOCVAR, PRINTFE, RET, PROC, END, MPROC, MEND,/*��Ԫʽ*/
	UNDEFSYM
};

//��ʶ������
enum KIND
{
	CONSVAR, VAR, PROCE, FUNC, PARAM, ARRAY, TMPVAR
};

//����
enum ERROR
{
	other,
	LONGID, KEYSAME, ZEROBEG, LONGINT, CHARCONS, SQLACK, ILSTR, LONGSTR,/*�ʷ�����*/
	CASELACK, IDLACK, INTLACK, ASGLACK, CHARLACK, ILTYPE, ARRAYIDX, SEMILACK, PARENLACK, BRACKLACK, BRACELACK, COLONLACK, DFTLACK, ILPRINT, MAINLACK, PROGEND, ILFACTOR, ILRETYPE, ILSTAT,/*�﷨����*/
	PARACONT, UNDEF, CONSASG, REDEF, RETVAL, SCANFPAR, PRINTFPAR/*�������*/
};
int errnum;

//�ṹ����
struct TOKEN
{
	enum SYMBOL sym;
	char value[STRMAX + 1];
};

//�����ⲿ��
int line;
int GLOBAL;//ȫ�ֱ�־
int retflag;
int DEBUG;
int paranum;
int paragot;

//�ʷ��������
char CHAR;
struct TOKEN token;
int TOKEN_index;
int varlabx;

//�﷨�������
struct TOKEN next[3];//��ǰ��ɨ��2������
int NEXT_index;
int FIRSTCASE;

//��Ԫʽ
struct QUAT
{
	enum SYMBOL op;
	int result;
	int operand_1;
	int operand_2;
	int labx;//��Ԫʽ�ڱ�ű��е��±�
} quat[QUATMAX];
int QUAT_index;

//���ű�
struct TAB
{
	char name[IDMAX + 1];
	enum KIND kind;
	enum SYMBOL type;
	int value;
	int arrdim;
} tab[TABMAX];
int TAB_index;

//�����
int ATAB_index;

//�ֳ���������
int btabx[LEVELMAX];
int BTABX_index;

//��ű�
char labtab[LABELMAX][IDMAX + 1];
int LABTAB_index;

//�ַ�����
char stab[STRMAX][STRMAX + 1];
char strlab[STRMAX][IDMAX + 1];
int STAB_index;

//�ļ�
FILE *in, *out, *data, *code, *quats;
char* FILEIN;

#endif
