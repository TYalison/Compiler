/* 14231006_田宇_测试编译器 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "preDef.h"
#include "preDecl.h"

//词法分析部分
void errorSym(int errx)
{
	printf("ERROR_SYMBOL_%d_", line);
	switch (errx)
	{
	case LONGID: printf("TOO LONG IDENTIFIER"); break;
	case KEYSAME: printf("IDENTIFIER NAMED AS RESERVER"); break;
	case ZEROBEG: printf(" POSITIVE INTEGER FOLLOWED ZERO"); break;
	case LONGINT: printf("TOO LONG INTEGER"); break;
	case CHARCONS: printf("CHAR CONST SUPPOSED"); break;
	case SQLACK: printf("SINGLE QUOTE LOST"); break;
	case ILSTR: printf("ILLEGAL CHAR IN STRING"); break;
	case LONGSTR: printf("TOO LONG STRING"); break;
	default: printf("OTHER"); break;
	}
	printf("\n");
	errnum++;
	//exit(1);
}
void getChar()//读字符过程，每调用一次读进一个字符放在CHAR中，并把读字符指针指向下一个字符
{
	CHAR = fgetc(in);
}
int isAscii()//32,33,35-126
{
	if (CHAR < 32 || CHAR == 34 || CHAR>126)
	{
		return FALSE;
	}
	return TRUE;
}
int isSpace()
{
	return isspace(CHAR);
}
int isNull()
{
	return CHAR == '\0' ? TRUE : FALSE;
}
int isLetter()
{
	if (isalpha(CHAR) || CHAR == '_')
	{
		return TRUE;
	}
	return FALSE;
}
int isDigit()
{
	return isdigit(CHAR);
}
int isComma()
{
	return CHAR == ',' ? TRUE : FALSE;
}
int isSemicolon()
{
	return CHAR == ';' ? TRUE : FALSE;
}
int isSquote()
{
	return CHAR == '\'' ? TRUE : FALSE;
}
int isDquote()
{
	return CHAR == '"' ? TRUE : FALSE;
}
int isAssign()
{
	return CHAR == '=' ? TRUE : FALSE;
}
int isBang()
{
	return CHAR == '!' ? TRUE : FALSE;
}
int isPlus()
{
	return CHAR == '+' ? TRUE : FALSE;
}
int isMinus()
{
	return CHAR == '-' ? TRUE : FALSE;
}
int isTimes()
{
	return CHAR == '*' ? TRUE : FALSE;
}
int isDivi()
{
	return CHAR == '/' ? TRUE : FALSE;
}
int isLparen()
{
	return CHAR == '(' ? TRUE : FALSE;
}
int isRparen()
{
	return CHAR == ')' ? TRUE : FALSE;
}
int isLbrack()
{
	return CHAR == '[' ? TRUE : FALSE;
}
int isRbrack()
{
	return CHAR == ']' ? TRUE : FALSE;
}
int isLbrace()
{
	return CHAR == '{' ? TRUE : FALSE;
}
int isRbrace()
{
	return CHAR == '}' ? TRUE : FALSE;
}
int isGtr()
{
	return CHAR == '>' ? TRUE : FALSE;
}
int isLss()
{
	return CHAR == '<' ? TRUE : FALSE;
}
int isNewline()
{
    return CHAR=='\n'?TRUE:FALSE;
}
int isColon()
{
	return CHAR == ':' ? TRUE : FALSE;
}
void clearToken()//清空TOKEN字符数组
{
	token.sym = null;
	TOKEN_index = 0;
	token.value[0] = '\0';
}
void catToken()
{
	token.value[TOKEN_index++] = CHAR;
}
int reserver()
{
	enum SYMBOL symbol;
	if (strcmp(token.value, "const") == 0)
	{
		symbol = CONSTSY;
	}
	else if (strcmp(token.value, "int") == 0)
	{
		symbol = INTSY;
	}
	else if (strcmp(token.value, "char") == 0)
	{
		symbol = CHARSY;
	}
	else if (strcmp(token.value, "void") == 0)
	{
		symbol = VOIDSY;
	}
	else if (strcmp(token.value, "if") == 0)
	{
		symbol = IFSY;
	}
	else if (strcmp(token.value, "else") == 0)
	{
		symbol = ELSESY;
	}
	else if (strcmp(token.value, "switch") == 0)
	{
		symbol = SWITCHSY;
	}
	else if (strcmp(token.value, "case") == 0)
	{
		symbol = CASESY;
	}
	else if (strcmp(token.value, "default") == 0)
	{
		symbol = DEFAULTSY;
	}
	else if (strcmp(token.value, "while") == 0)
	{
		symbol = WHILESY;
	}
	else if (strcmp(token.value, "return") == 0)
	{
		symbol = RETURNSY;
	}
	else if (strcmp(token.value, "scanf") == 0)
	{
		symbol = SCANFSY;
	}
	else if (strcmp(token.value, "printf") == 0)
	{
		symbol = PRINTFSY;
	}
	else if (strcmp(token.value, "main") == 0)
	{
		symbol = MAIN;
	}
	else
	{
		symbol = IDENT;
	}
	return symbol;
}
void Symbol()//词法分析子程序
{
	int i, sym_temp;
	clearToken();
	while (isSpace() || isNull())
	{
		if (CHAR == '\n')
		{
			line++;
		}
		getChar();
	}
	if (isLetter())
	{
		while (isLetter() || isDigit())
		{
			if (TOKEN_index < IDMAX)
			{
				catToken();
				getChar();
			}
			else
			{
				//clearToken();
				token.sym=IDENT;
				errorSym(LONGID);//标识符过长
				while(isLetter())
                {
                    getChar();
                }
				return;
			}
		}
		token.value[TOKEN_index] = '\0';
		sym_temp = reserver();
		if (sym_temp == IDENT)
		{
			for (i = 0; i < TOKEN_index; i++)
			{
				if (isalpha(token.value[i]))
				{
					token.value[i] = tolower(token.value[i]);
				}
			}
			sym_temp = reserver();
			if (sym_temp != IDENT)
			{
				//clearToken();
				token.sym = IDENT;
				errorSym(KEYSAME);//与保留字重名
				return;
			}
		}
		token.sym = sym_temp;
	}
	else if (isDigit())
	{
		if (CHAR == '0')
		{
			catToken();
			getChar();
			if (isDigit())
			{
				//clearToken();
				token.sym = INTNUM;
				errorSym(ZEROBEG);//非零整数不能以0开头
				while(isDigit())
                {
                    getChar();
                }
				return;
			}
		}
		else
		{
			while (isDigit())
			{
				if (TOKEN_index<INTMAXB)
				{
					catToken();
					getChar();
				}
				else
				{
					//clearToken();
					token.sym = INTNUM;
					errorSym(LONGINT);//整数过长
					while(isDigit())
                    {
                        getChar();
                    }
					return;
				}
			}
		}
		token.sym = INTNUM;
		token.value[TOKEN_index] = '\0';
	}
	else if (isSquote())
	{
		getChar();
		if (!isPlus() && !isMinus() && !isTimes() && !isDivi() && !isLetter() && !isDigit())
		{
		    token.value[TOKEN_index] = '\0';
		    token.sym = SCHAR;
			errorSym(CHARCONS);//不是字符常量
			return;
		}
		catToken();
		token.value[TOKEN_index] = '\0';
		getChar();
		if (!isSquote())
		{
		    token.sym = SCHAR;
			errorSym(SQLACK);//字符常量缺少右侧单引号
			return;
		}
		getChar();
		token.sym = SCHAR;
	}
	else if (isDquote())
	{
		getChar();
		while (!isDquote())
		{
		    if(isNewline())
            {
                //clearToken();
                token.value[TOKEN_index] = '\0';
                token.sym = STRING;
                errorSym(LONGSTR);
                return;
            }
			if (TOKEN_index<STRMAX)
			{
				if (!isAscii())
				{
					errorSym(ILSTR);//字符串常量中出现非法字符
				}
				catToken();
				getChar();
			}
			else
			{
				//clearToken();
				token.value[TOKEN_index-1] = '\0';
                token.sym = STRING;
				errorSym(LONGSTR);//字符串过长
				while(!isNewline())
                {
                    getChar();
                }
				return;
			}
		}
		getChar();
		token.value[TOKEN_index] = '\0';
		token.sym = STRING;
	}
	else if (isAssign())
	{
		getChar();
		if (isAssign())
		{
			getChar();
			token.sym = EQL;
		}
		else
		{
			token.sym = ASSIGN;
		}
	}
	else if (isGtr())
	{
		getChar();
		if (isAssign())
		{
			getChar();
			token.sym = GEQ;
		}
		else
		{
			token.sym = GTR;
		}
	}
	else if (isLss())
	{
		getChar();
		if (isAssign())
		{
			getChar();
			token.sym = LEQ;
		}
		else
		{
			token.sym = LSS;
		}
	}
	else if (isBang())
	{
		getChar();
		if (isAssign())
		{
			getChar();
			token.sym = NEQ;
		}
		else
		{
		    token.sym = NEQ;
			errorSym(other);//非法字符
		}
	}
	else if (isPlus())
	{
		token.sym = PLUS;
		getChar();
	}
	else if (isMinus())
	{
		token.sym = MINUS;
		getChar();
	}
	else if (isTimes())
	{
		token.sym = TIMES;
		getChar();
	}
	else if (isDivi())
	{
		token.sym = DIVI;
		getChar();
	}
	else if (isLparen())
	{
		token.sym = LPAREN;
		getChar();
	}
	else if (isRparen())
	{
		token.sym = RPAREN;
		getChar();
	}
	else if (isLbrack())
	{
		token.sym = LBRACK;
		getChar();
	}
	else if (isRbrack())
	{
		token.sym = RBRACK;
		getChar();
	}
	else if (isLbrace())
	{
		token.sym = LBRACE;
		getChar();
	}
	else if (isRbrace())
	{
		token.sym = RBRACE;
		getChar();
	}
	else if (isComma())
	{
		token.sym = COMMA;
		getChar();
	}
	else if (isSemicolon())
	{
		token.sym = SEMICOLON;
		getChar();
	}
	else if (isColon())
	{
		token.sym = COLON;
		getChar();
	}
	else if (CHAR == EOF)
	{
		token.sym = null;
		return;
	}
	else
	{
		token.sym = UNDEFSYM;
		errorSym(other);//非法字符
		getChar();
	}
}

//语法分析部分
void errorGram(int errx)
{
	printf("ERROR_GRAMMER_%d_", line);
	switch (errx)
	{
	case CASELACK: printf("CASE LOST"); break;
	case IDLACK: printf("IDENTIFIER LOST"); break;
	case INTLACK: printf("INT CONSTANT LOST"); break;
	case ASGLACK: printf("ASSIGN OPERATOR LOST"); break;
	case CHARLACK: printf("CHAR CONSTANT LOST"); break;
	case ILTYPE: printf("ILLEGAL TYPE"); break;
	case SEMILACK: printf("SEMICOLON LOST"); break;
	case PARENLACK: printf("PAREN LOST"); break;
	case BRACKLACK: printf("BRACK LOST"); break;
	case BRACELACK: printf("BRACE LOST"); break;
	case COLONLACK: printf("COLON LOST"); break;
	case DFTLACK: printf("DEFAULT LOST"); break;
	case ILPRINT: printf("ILLEGAL CHAR IN OUTPUT STRING"); break;
	case MAINLACK: printf("MAIN PROCEDURE LOST"); break;
	case PROGEND: printf("PROGRAM END SUPPOSED"); break;
	case ILFACTOR: printf("ILLEGAL FACTOR KIND"); break;
	case ILRETYPE: printf("ILLEGAL RETURN VALUE"); break;
	case ARRAYIDX: printf("ILLEGAL ARRAY INDEX"); break;
	case ILSTAT: printf("ILLEGAL STATEMENT"); break;
	default: printf("OTHER"); break;
	}
	printf("\n");
	errnum++;
	//exit(1);
}
int Factor()
{
	int factabx;
	int type;
	char name[IDMAX + 1];
	char id[IDMAX + 1];
	int sign = 1;
	int value;
	int exprtabx;
	if (next[NEXT_index].sym == IDENT)
	{
		if (next[(NEXT_index + 1) % 3].sym == LPAREN)
		{
			factabx = callFunct(-1);
		}
		else
		{
			strcpy(name, next[NEXT_index].value);
			strcat(name,"@");
			factabx = locTab(name);
			if (factabx == -1)
			{
				errorMean(UNDEF);//未定义
				factabx=0;
			}
			if(tab[factabx].kind==PROCE||tab[factabx].kind==FUNC)
            {
                errorMean(PRINTFPAR);
            }
			type = tab[factabx].type;
			newNext();
			if (next[NEXT_index].sym == LBRACK)
			{
				newNext();
				exprtabx = Expression();
				genVarlab(id);
				enterTab(id, TMPVAR, type, 0, -1);
				//fprintf(data, "%s\t\tDD\t\t?\n", id);
				genQuat(LDARY, factabx, exprtabx, TAB_index, -1);
				factabx = getTabtop();
				if (next[NEXT_index].sym == RBRACK)
				{
					newNext();
				}
				else
				{
					errorGram(BRACKLACK);
				}
			}
		}
	}
	else if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
		factabx = Expression();
		if (next[NEXT_index].sym == RPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少右括弧
		}
	}
	else if (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS)
	{
		sign = (next[NEXT_index].sym == PLUS) ? 1 : -1;
		newNext();
		if (next[NEXT_index].sym == INTNUM)
		{
			value = transNum(next[NEXT_index].value);
			value = value * sign;
			genVarlab(name);
			enterTab(name, CONSVAR, INTNUM, value, -1);
			factabx = getTabtop();
			newNext();
		}
	}
	else if (next[NEXT_index].sym == INTNUM)
	{
		value = transNum(next[NEXT_index].value);
		genVarlab(name);
		enterTab(name, CONSVAR, INTNUM, value, -1);
		factabx = getTabtop();
		newNext();
	}
	else if (next[NEXT_index].sym == SCHAR)
	{
		value = next[NEXT_index].value[0];
		genVarlab(name);
		enterTab(name, CONSVAR, SCHAR, value, -1);
		factabx = getTabtop();
		newNext();
	}
	else
	{
		errorGram(ILFACTOR);//未定义因子类型
		factabx=0;
		while(next[NEXT_index].sym!=SEMICOLON)
        {
            newNext();
            if(next[NEXT_index].sym==null)
            {
                exit(1);
            }
        }
	}
	return factabx;
}
int Term()
{
	int termtabx;
	int factabx;
	int calop;
	int nfactabx;
	char name[IDMAX + 1];
	int type;
	int kind;
	factabx = Factor();
	termtabx = factabx;
	while (next[NEXT_index].sym == TIMES || next[NEXT_index].sym == DIVI)
	{
		calop = next[NEXT_index].sym;
		newNext();
		nfactabx = Factor();
		genVarlab(name);
		kind = newKind(factabx, nfactabx);
		type = newKind(factabx, nfactabx);
		if (kind != CONSVAR)
		{
			enterTab(name, TMPVAR, type, 0, -1);
			//fprintf(data, "%s\t\tDD\t\t?\n", name);
		}
		else
		{
			if (calop == TIMES)
			{
				enterTab(name, CONSVAR, type, tab[factabx].value * tab[nfactabx].value, -1);
			}
			else
			{
				enterTab(name, CONSVAR, type, tab[factabx].value / tab[nfactabx].value, -1);
			}
		}
		termtabx = getTabtop();
		if (kind != CONSVAR)
		{
			genQuat(calop, factabx, nfactabx, termtabx, -1);
		}
		factabx = termtabx;
	}
	return termtabx;
}
int Expression()
{
	int exprtabx;
	int tmptabx;
	int sign = 1;
	int termtabx;
	int calop;
	int ntermtabx;
	char name[IDMAX + 1];
	int type;
	int kind;
	if (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS)
	{
		sign = (next[NEXT_index].sym == PLUS) ? 1 : -1;
		newNext();
	}
	termtabx = Term();
	type = getType(termtabx);
	kind = tab[termtabx].kind;
	exprtabx = termtabx;
	while (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS)
	{
		calop = next[NEXT_index].sym;
		newNext();
		ntermtabx = Term();
		genVarlab(name);
		kind = newKind(termtabx, ntermtabx);
		type = newType(termtabx, ntermtabx);
		if (kind != CONSVAR)
		{
			enterTab(name, TMPVAR, type, 0, -1);
			//fprintf(data, "%s\t\tDD\t\t?\n", name);
		}
		else
		{
			if (calop == PLUS)
			{
				enterTab(name, CONSVAR, type, tab[termtabx].value + tab[ntermtabx].value, -1);
			}
			else
			{
				enterTab(name, CONSVAR, type, tab[termtabx].value - tab[ntermtabx].value, -1);
			}
		}
		exprtabx = getTabtop();
		if (kind != CONSVAR)
		{
			genQuat(calop, termtabx, ntermtabx, exprtabx, -1);
		}
		termtabx = exprtabx;
	}
	if (sign == -1)
	{
		genVarlab(name);
		enterTab(name, TMPVAR, type, 0, -1);
		//fprintf(data, "%s\t\tDD\t\t?\n", name);
		tmptabx = getTabtop();
		genQuat(NEG, exprtabx, -1, tmptabx, -1);
		exprtabx = tmptabx;
	}
	return exprtabx;
}
void transStr(int num, char str[])
{
	int i = 0;
	int temp;
	char index[BITMAX];
	if(num>=0&&num<10)
    {
        index[i++]=num+'0';
    }
    else if(num>=10&&num<100)
    {
        index[i++] = (num / 10) + '0';
        index[i++] = (num % 10) + '0';
    }
    else if(num>=100&&num<1000)
    {
        index[i++] = (num / 100) + '0';
        temp=num/100;
        temp=num-temp*100;
        index[i++] = (temp / 10) + '0';
        index[i++] = (num % 10) + '0';
    }
    else if(num>=1000&&num<10000)
    {
        index[i++] = (num / 1000) + '0';
        temp=num/1000;
        temp=num-temp*1000;
        index[i++] = (temp / 100) + '0';
        temp=temp/100;
        temp=temp-temp*100;
        index[i++] = (temp / 10) + '0';
        index[i++] = (num % 10) + '0';
    }
	index[i] = '\0';
	strcat(str, index);
}
int transNum(char strnum[])
{
	int i;
	int intnum = 0;
	for (i = 0; strnum[i] != '\0'; i++)
	{
		intnum = intnum * 10 + (strnum[i] - '0');
	}
	return intnum;
}
void initNext()
{
	int i = 0;
	next[0].sym = null;
	next[1].sym = null;
	next[2].sym = null;
	do
	{
		Symbol();
		if (token.sym == null)
		{
			return;
		}
		next[i].sym = token.sym;
		strcpy(next[i].value, token.value);
		i++;
	} while (i < 3);
}
void newNext()
{
	if (token.sym != null)
	{
		Symbol();
	}
	next[NEXT_index].sym = token.sym;
	strcpy(next[NEXT_index++].value, token.value);
	if (NEXT_index == 3)
	{
		NEXT_index = 0;
	}
}
void constDef()
{
	int type;
	char name[IDMAX + 1];
	int value;
	int sign = 1;//符号位
	if (next[NEXT_index].sym == INTSY)
	{
		type = INTNUM;
		newNext();
		if (next[NEXT_index].sym == IDENT)
		{
			strcpy(name, next[NEXT_index].value);
			strcat(name,"@");
			newNext();
		}
		else
		{
			errorGram(IDLACK);//缺少常量名
		}
		if (next[NEXT_index].sym == ASSIGN)
		{
			newNext();
		}
		else
		{
			errorGram(ASGLACK);//缺少赋值符号
		}
		if (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS)
		{
			sign = (next[NEXT_index].sym == PLUS) ? 1 : -1;
			newNext();
		}
		if (next[NEXT_index].sym == INTNUM)
		{
			value = transNum(next[NEXT_index].value);
			value = value * sign;
			newNext();
		}
		else
		{
			errorGram(INTLACK);//缺少整型常量
		}
		enterTab(name, CONSVAR, type, value, -1);
		sign = 1;
		while (next[NEXT_index].sym == COMMA)
		{
			newNext();
			if (next[NEXT_index].sym == IDENT)
			{
				strcpy(name, next[NEXT_index].value);
				strcat(name,"@");
				newNext();
			}
			else
			{
				errorGram(IDLACK);//缺少标识符
			}
			if (next[NEXT_index].sym == ASSIGN)
			{
				newNext();
			}
			else
			{
				errorGram(ASGLACK);//缺少赋值符号
			}
			if (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS)
			{
				sign = (next[NEXT_index].sym == PLUS) ? 1 : -1;
				newNext();
			}
			if (next[NEXT_index].sym == INTNUM)
			{
				value = transNum(next[NEXT_index].value);
				value = value * sign;
				newNext();
			}
			else
			{
				errorGram(INTLACK);//缺少整型常量
			}
			enterTab(name, CONSVAR, type, value, -1);
			sign = 1;
		}
	}
	else if (next[NEXT_index].sym == CHARSY)
	{
		type = SCHAR;
		newNext();
		if (next[NEXT_index].sym == IDENT)
		{
			strcpy(name, next[NEXT_index].value);
			strcat(name,"@");
			newNext();
		}
		else
		{
			errorGram(IDLACK);//缺少标识符
		}
		if (next[NEXT_index].sym == ASSIGN)
		{
			newNext();
		}
		else
		{
			errorGram(ASGLACK);//缺少赋值符号
		}
		if (next[NEXT_index].sym == SCHAR)
		{
			value = next[NEXT_index].value[0];
			newNext();
		}
		else
		{
			errorGram(CHARLACK);//缺少字符型常量
		}
		enterTab(name, CONSVAR, type, value, -1);
		while (next[NEXT_index].sym == COMMA)
		{
			newNext();
			if (next[NEXT_index].sym == IDENT)
			{
				strcpy(name, next[NEXT_index].value);
				strcat(name,"@");
				newNext();
			}
			else
			{
				errorGram(IDLACK);//缺少标识符
			}
			if (next[NEXT_index].sym == ASSIGN)
			{
				newNext();
			}
			else
			{
				errorGram(ASGLACK);//缺少赋值符号
			}
			if (next[NEXT_index].sym == SCHAR)
			{
				value = next[NEXT_index].value[0];
				newNext();
			}
			else
			{
				errorGram(INTLACK);//缺少整型常量
			}
			enterTab(name, CONSVAR, type, value, -1);
		}
	}
	else
	{
		errorGram(ILTYPE);//非法类型标识符
		while(next[NEXT_index].sym!=SEMICOLON)
        {
            newNext();
            if(next[NEXT_index].sym==null)
            {
                exit(1);
            }
        }
	}
}
void constDecl()
{
	while (next[NEXT_index].sym == CONSTSY)
	{
		newNext();
		constDef();
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//缺分号
		}
	}
}
void varDef()
{
	int dim;
	int type;
	char name[IDMAX + 1];
	if (next[NEXT_index].sym == INTSY)
	{
		type = INTNUM;
		newNext();
	}
	else if (next[NEXT_index].sym == CHARSY)
	{
		type = SCHAR;
		newNext();
	}
	else
	{
		errorGram(ILTYPE);//非法类型标识符
	}
	if (next[NEXT_index].sym == IDENT)
	{
		strcpy(name, next[NEXT_index].value);
		newNext();
	}
	else
	{
		errorGram(IDLACK);//缺少变量名
		while(next[NEXT_index].sym!=SEMICOLON)
        {
            newNext();
            if(next[NEXT_index].sym==null)
            {
                exit(1);
            }
        }
	}
	if (next[NEXT_index].sym == LBRACK)
	{
		newNext();
		if (next[NEXT_index].sym == INTNUM)
		{
			if (next[NEXT_index].value[0] > '0')
			{
				dim = transNum(next[NEXT_index].value);
				if (GLOBAL)
				{
				    strcat(name, "@");
					enterTab(name, ARRAY, type, 0, dim);
					fprintf(data, "%s\t\tDD\t\t%d\t\tDUP(?)\n", name, dim);
				}
				else
				{
					strcat(name, "@@");
					enterTab(name, ARRAY, type, 0, dim);
					genQuat(LOCARRAY, TAB_index, -1, -1, -1);
				}
			}
			else
			{
				errorGram(ARRAYIDX);
			}
		}
		else
		{
			errorGram(ARRAYIDX);
		}
		newNext();
		if (next[NEXT_index].sym == RBRACK)
		{
			newNext();
		}
		else
		{
			errorGram(BRACKLACK);
		}
	}
	else
	{
		if (GLOBAL)
		{
		    strcat(name, "@");
			enterTab(name, VAR, type, 0, -1);
			fprintf(data, "%s\t\tDD\t\t?\n", name);
		}
		else
		{
			strcat(name, "@@");
			enterTab(name, VAR, type, 0, -1);
			genQuat(LOCVAR, TAB_index, -1, -1, -1);
		}
	}
	while (next[NEXT_index].sym == COMMA)
	{
		newNext();
		if (next[NEXT_index].sym == IDENT)
		{
			strcpy(name, next[NEXT_index].value);
			newNext();
		}
		else
		{
			errorGram(IDLACK);//缺少变量名
		}
		if (next[NEXT_index].sym == LBRACK)
		{
			newNext();
			if (next[NEXT_index].sym == INTNUM)
			{
			    dim = transNum(next[NEXT_index].value);
				if (dim > 0)
				{

					if (GLOBAL)
					{
					    strcat(name, "@");
						enterTab(name, ARRAY, type, 0, ++ATAB_index);
						fprintf(data, "%s\t\tDD\t\t%d\t\tDUP(?)\n", name, dim);
					}
					else
					{
						strcat(name, "@@");
						enterTab(name, ARRAY, type, 0, ++ATAB_index);
						genQuat(LOCARRAY, TAB_index, -1, -1, -1);
					}
				}
				else
				{
					errorGram(ARRAYIDX);
				}
			}
			else
			{
				errorGram(ARRAYIDX);
			}
			newNext();
			if (next[NEXT_index].sym == RBRACK)
			{
				newNext();
			}
			else
			{
				errorGram(BRACKLACK);
			}
		}
		else
		{
			if (GLOBAL)
			{
			    strcat(name, "@");
				enterTab(name, VAR, type, 0, -1);
				fprintf(data, "%s\t\tDD\t\t?\n", name);
			}
			else
			{
				strcat(name, "@@");
				enterTab(name, VAR, type, 0, -1);
				genQuat(LOCVAR, TAB_index, -1, -1, -1);
			}
		}
	}
}
void varDecl()
{
	while (next[(NEXT_index + 2) % 3].sym == SEMICOLON || next[(NEXT_index + 2) % 3].sym == COMMA || next[(NEXT_index + 2) % 3].sym == LBRACK)
	{
		varDef();
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//应有分号
		}
	}
}
void Parameter()
{
	char name[IDMAX + 1];
	int type;
	if (next[NEXT_index].sym == RPAREN)
	{
		return;
	}
	if (next[NEXT_index].sym == INTSY)
	{
		type = INTNUM;
		newNext();
	}
	else if (next[NEXT_index].sym == CHARSY)
	{
		type = SCHAR;
		newNext();
	}
	else
	{
		errorGram(ILTYPE);//非法类型标识符
	}
	if (next[NEXT_index].sym == IDENT)
	{
		strcpy(name, next[NEXT_index].value);
		strcat(name, "@@");
		newNext();
	}
	else
	{
		errorGram(IDLACK);//缺少参数名
		while(next[NEXT_index].sym!=RPAREN)
        {
            newNext();
            if(next[NEXT_index].sym==null)
            {
                exit(1);
            }
        }
		return;
	}
	paranum++;
	enterTab(name, PARAM, type, 0, -1);
	while (next[NEXT_index].sym == COMMA)
	{
		newNext();
		if (next[NEXT_index].sym == INTSY)
		{
			type = INTNUM;
			newNext();
		}
		else if (next[NEXT_index].sym == CHARSY)
		{
			type = SCHAR;
			newNext();
		}
		else
		{
			errorGram(ILTYPE);//非法类型标识符
		}
		if (next[NEXT_index].sym == IDENT)
		{
			strcpy(name, next[NEXT_index].value);
			strcat(name, "@@");
			newNext();
		}
		else
		{
			errorGram(IDLACK);//缺少参数名
			while(next[NEXT_index].sym!=RPAREN)
            {
                newNext();
                if(next[NEXT_index].sym==null)
                {
                    exit(1);
                }
            }
            return;
		}
		paranum++;
		enterTab(name, PARAM, type, 0, -1);
	}
}
int Condition(int lab, int nextlab)
{
	int exprtabx;
	int relop;
	int ntabx;
	char name[IDMAX + 1];
	exprtabx = Expression();
	if (next[NEXT_index].sym == EQL || next[NEXT_index].sym == NEQ || next[NEXT_index].sym == GTR || next[NEXT_index].sym == GEQ || next[NEXT_index].sym == LSS || next[NEXT_index].sym == LEQ)
	{
		relop = next[NEXT_index].sym;
		newNext();
		ntabx = Expression();
		genQuat(CMP, exprtabx, ntabx, -1, -1);
		lab = genNewlab();
		genQuat(relop, lab, -1, -1, -1);
	}
	else
	{
		genVarlab(name);
		enterTab(name, CONSVAR, INTNUM, 0, -1);
		ntabx = getTabtop();
		genQuat(CMP, exprtabx, ntabx, -1, -1);
		lab = genNewlab();
		genQuat(NEQ, lab, -1, -1, -1);
	}
	return lab;
}
void Compound()
{
	if (next[NEXT_index].sym == CONSTSY)
	{
		constDecl();
	}
	if (next[NEXT_index].sym == INTSY || next[NEXT_index].sym == CHARSY)
	{
		varDecl();
	}
	Statlist(-1);
}
int preCase(int lab, int nextlab)
{
	int labx;//缺省标号在标号表的下标
	int exprtabx;
	if (next[NEXT_index].sym == SWITCHSY)
	{
		newNext();
	}
	FIRSTCASE=TRUE;
	genQuat(NOP,-1,-1,-1,lab);
	if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少左括弧
	}
	exprtabx = Expression();
	if (nextlab == -1)
	{
		nextlab = genNewlab();
	}
	if (next[NEXT_index].sym == RPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少右括弧
	}
	if (next[NEXT_index].sym == LBRACE)
	{
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少左花括号
	}
	labx = Case(lab, nextlab, exprtabx);
	Default(labx, nextlab);
	if (next[NEXT_index].sym == RBRACE)
	{
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少右花括号
	}
	lab = nextlab;
	return lab;
}
int Case(int lab, int nextlab, int tabx)//情况表
{
	int labx;
	labx = singleCase(lab, nextlab, tabx);
	FIRSTCASE=FALSE;
	while (next[NEXT_index].sym == CASESY)
	{
		labx = singleCase(labx, nextlab, tabx);
	}
	return labx;
}
int singleCase(int labx, int nextlab, int tabx)
{
	int constabx;
	if (next[NEXT_index].sym == CASESY)
	{
		newNext();
	}
	else
	{
		errorGram(CASELACK);
	}
	constabx = Constant();
	labx=(FIRSTCASE)?-1:labx;
	genQuat(CMP, tabx, constabx, -1, labx);
	labx = genNewlab();
	genQuat(EQL, labx, -1, -1, -1);
	if (next[NEXT_index].sym == COLON)
	{
		newNext();
	}
	else
	{
		errorGram(COLONLACK);//缺少冒号
	}
	Statement(-1, nextlab);
	genQuat(JMP, nextlab, -1, -1, -1);
	return labx;
}
void Default(int labx, int nextlab)
{
	if (next[NEXT_index].sym == RBRACE)
	{
		genQuat(NOP, -1, -1, -1, labx);
		return;
	}
	if (next[NEXT_index].sym == DEFAULTSY)
	{
		newNext();
	}
	else
	{
		errorGram(DFTLACK);//缺少default
	}
	if (next[NEXT_index].sym == COLON)
	{
		newNext();
	}
	else
	{
		errorGram(COLONLACK);//缺少冒号
	}
	Statement(labx, nextlab);
}
int preStat()
{
	switch (next[NEXT_index].sym)
	{
	case IFSY:
	case SWITCHSY:
	case WHILESY:
	case LBRACE:
	case IDENT:
	case SCANFSY:
	case PRINTFSY:
	case SEMICOLON:
	case RETURNSY: return TRUE;
	default: return FALSE;
	}
}
void Statlist(int lab)
{
	int labx;//labx表示下一条语句或语句列结束的标号在标号表的下标
	labx = Statement(lab, -1);
	while (preStat())
	{
		labx = Statement(labx, -1);
	}
	genQuat(NOP, -1, -1, -1, labx);
	if(next[NEXT_index].sym!=RBRACE)
    {
        errorGram(ILSTAT);
        while(next[NEXT_index].sym!=RBRACE)
        {
            newNext();
            if(next[NEXT_index].sym==null)
            {
                exit(1);
            }
        }
    }
}
int Constant()
{
	int tabx;
	char name[IDMAX + 1];
	int value = 0;
	int sign = 1;
	if (next[NEXT_index].sym == SCHAR)
	{
		value = next[NEXT_index].value[0];
		genVarlab(name);
		enterTab(name, CONSVAR, SCHAR, value, -1);
		tabx = getTabtop();
		newNext();
	}
	else if (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS)
	{
		sign = (next[NEXT_index].sym == PLUS) ? 1 : -1;
		newNext();
		if (next[NEXT_index].sym == INTNUM)
		{
			value = transNum(next[NEXT_index].value);
			value = value * sign;
			genVarlab(name);
			enterTab(name, CONSVAR, SCHAR, value, -1);
			tabx = getTabtop();
			newNext();
		}
		else
		{
			errorGram(ILTYPE);//非法类型
		}
	}
	else if (next[NEXT_index].sym == INTNUM)
	{
		value = transNum(next[NEXT_index].value);
		value = value * sign;
		genVarlab(name);
		enterTab(name, CONSVAR, SCHAR, value, -1);
		tabx = getTabtop();
		newNext();
	}
	else
	{
		errorGram(ILTYPE);//非法类型
	}
	return tabx;
}
int Statement(int lab, int nextlab)
{
    int i;
    int strlength;
	int beglabx;//while语句开始标号在标号表中索引
	int endlabx;//while语句结束标号在标号表中索引
	int exprtabx;
	int strtabx;
	char name[IDMAX + 1];
	int tabx;
	if (next[NEXT_index].sym == IFSY)//条件语句
	{
	    genQuat(NOP,-1,-1,-1,lab);
		newNext();
		if (next[NEXT_index].sym == LPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少左括弧
		}
		lab = Condition(lab, nextlab);
		if (next[NEXT_index].sym == RPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少右括弧
		}
		Statement(-1, lab);
		if (next[NEXT_index].sym == ELSESY)
		{
		    if(nextlab==-1)
            {
                nextlab=genNewlab();
            }
            genQuat(JMP,nextlab,-1,-1,-1);
			newNext();
			lab=Statement(lab, nextlab);
			if(lab!=nextlab)
            {
                genQuat(NOP,-1,-1,-1,lab);
            }
			lab=nextlab;
		}
	}
	else if (next[NEXT_index].sym == WHILESY)
	{
		beglabx = (lab == -1) ? genNewlab() : lab;
		genQuat(NOP,-1,-1,-1,beglabx);
		newNext();
		if (next[NEXT_index].sym == LPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少左括弧
		}
		lab = Condition(beglabx, nextlab);
		if (next[NEXT_index].sym == RPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少右括弧
		}
		endlabx = Statement(-1, -1);
		genQuat(JMP, beglabx, -1, -1, endlabx);
	}
	else if (next[NEXT_index].sym == SWITCHSY)
	{
		lab = preCase(lab, nextlab);
	}
	else if (next[NEXT_index].sym == LBRACE)
	{
		newNext();
		Statlist(lab);
		lab = nextlab;
		if (next[NEXT_index].sym == RBRACE)
		{
			newNext();
		}
		else
		{
			errorGram(BRACELACK);//缺右花括号
		}
	}
	else if (next[NEXT_index].sym == SCANFSY)
	{
		newNext();
		if (next[NEXT_index].sym == LPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少左括弧
		}
		if (next[NEXT_index].sym == IDENT)
		{
			strcpy(name, next[NEXT_index].value);
			strcat(name,"@");
			tabx = locTab(name);
			if (tabx == -1)
            {
                errorMean(UNDEF);//未定义标识符
            }
			else if(tab[tabx].kind==VAR||tab[tabx].kind==TMPVAR||tab[tabx].kind==PARAM)
            {
                genQuat(SCANF, tabx, -1, -1, lab);
            }
			else
			{
			    errorMean(SCANFPAR);
			}
			newNext();
		}
		else
		{
			errorGram(IDLACK);//缺少标识符
		}
		while (next[NEXT_index].sym == COMMA)
		{
			newNext();
			if (next[NEXT_index].sym == IDENT)
			{
				strcpy(name, next[NEXT_index].value);
				strcat(name,"@");
				tabx = locTab(name);
				if (tabx == -1)
                {
                    errorMean(UNDEF);//未定义标识符
                }
				else if(tab[tabx].kind==VAR||tab[tabx].kind==TMPVAR||tab[tabx].kind==PARAM)
                {
                    genQuat(SCANF, tabx, -1, -1, lab);
                }
                else
                {
                    errorMean(SCANFPAR);
                }
                newNext();
			}
			else
			{
				errorGram(IDLACK);//缺少标识符
			}
		}
		if (next[NEXT_index].sym == RPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少右括弧
		}
		lab = nextlab;
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//缺分号
		}
	}
	else if (next[NEXT_index].sym == PRINTFSY)
	{
	    genQuat(NOP,-1,-1,-1,lab);
		newNext();
		if (next[NEXT_index].sym == LPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少左括弧
		}
		if (next[NEXT_index].sym == STRING)
		{
			strtabx = genStrlabx();
			strcpy(stab[strtabx], next[NEXT_index].value);
			fprintf(data, "%s\t\tDB\t\t", strlab[strtabx]);
			strlength=strlen(stab[strtabx]);
			if(strlength)
            {
                fprintf(data, "%d,", stab[strtabx][0]);
            }
			for(i=1;i<strlength;i++)
            {
                if(i%20 == 0)
                {
                    fprintf(data, "\t\tDB\t\t%d,", stab[strtabx][i]);
                }
                else if(i%20 < 19)
                {
                    fprintf(data, "%d,", stab[strtabx][i]);
                }
                else
                {
                    fprintf(data, "%d", stab[strtabx][i]);
                    if(i!=(strlength-1))
                    {
                        fprintf(data, "\n");
                    }
                    else
                    {
                        fprintf(data, ",");
                    }
                }
            }
            fprintf(data, "0\n");
			genQuat(PRINTFS, strtabx, -1, -1, -1);
			newNext();
			if (next[NEXT_index].sym == COMMA)
			{
				newNext();
				exprtabx = Expression();
				genQuat(PRINTFE, exprtabx, -1, -1, -1);
			}
		}
		else if (next[NEXT_index].sym == PLUS || next[NEXT_index].sym == MINUS || next[NEXT_index].sym == IDENT || next[NEXT_index].sym == LPAREN || next[NEXT_index].sym == SCHAR || next[NEXT_index].sym == INTNUM)
		{
			exprtabx = Expression();
			genQuat(PRINTFE, exprtabx, -1, -1, -1);
		}
		if (next[NEXT_index].sym == RPAREN)
		{
			newNext();
		}
		else
		{
			errorGram(PARENLACK);//缺少右括弧
		}
		lab = nextlab;
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//缺分号
		}
	}
	else if (next[NEXT_index].sym == RETURNSY)
	{
		newNext();
		exprtabx = -1;
		genQuat(NOP, -1, -1, -1, lab);
		if (next[NEXT_index].sym == LPAREN)
		{
			retflag = TRUE;
			newNext();
			exprtabx = Expression();
			if (next[NEXT_index].sym == RPAREN)
			{
				newNext();
			}
			else
			{
				errorGram(PARENLACK);//缺少右括弧
			}
		}
		genQuat(RET, exprtabx, -1, -1, -1);
		lab=nextlab;
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//缺分号
		}
	}
	else if (next[NEXT_index].sym == IDENT && (next[(NEXT_index + 1) % 3].sym == ASSIGN || next[(NEXT_index + 1) % 3].sym == LBRACK))
	{
		exprtabx = -1;
		strcpy(name, next[NEXT_index].value);
		strcat(name,"@");
		tabx = locTab(name);
		if (tabx == -1)
        {
            errorMean(UNDEF);//未定义标识符
            tabx=0;
        }
		genQuat(NOP, -1, -1, -1, lab);
		newNext();
		if (next[NEXT_index].sym == LBRACK)
		{
			newNext();
			exprtabx = Expression();
			tab[tabx].value = exprtabx;
			if (next[NEXT_index].sym == RBRACK)
			{
				newNext();
			}
			else
			{
				errorGram(BRACKLACK);
			}
		}
		if (next[NEXT_index].sym == ASSIGN)
		{
			newNext();
		}
		exprtabx = -1;
		exprtabx = Expression();
		genQuat(ASSIGN, tabx, exprtabx, tab[tabx].value, -1);
		if (tab[tabx].kind == CONSVAR)
		{
			errorMean(CONSASG);//不能给静态量赋值
		}
		lab = nextlab;
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//缺分号
		}
	}
	else if (next[NEXT_index].sym == IDENT&&next[(NEXT_index + 1) % 3].sym == LPAREN)
	{
	    strcpy(name, next[NEXT_index].value);
		strcat(name,"@");
		tabx = locTab(name);
		if (tabx == -1)
		{
			errorMean(UNDEF);//未定义标识符
			tabx=0;
		}
		else if (tab[tabx].kind == FUNC)
		{
			callFunct(lab);
			lab = nextlab;
		}
		else if (tab[tabx].kind == PROCE)
		{
			callProc(lab);
			lab = nextlab;
		}
		if (next[NEXT_index].sym == SEMICOLON)
		{
			newNext();
		}
		else
		{
			errorGram(SEMILACK);//缺分号
		}
	}
	else if (next[NEXT_index].sym == SEMICOLON)
	{
		lab = nextlab;
		newNext();
	}
	else
	{
		errorGram(ILSTAT);//未定义类型语句
		while(!preStat()&&next[NEXT_index].sym!=RBRACE)
        {
            newNext();
        }
	}
	return lab;
}
int callFunct(int lab)
{
	int retabx;
	char name[IDMAX + 1];
	int tabx;
	char id[IDMAX + 1];
	int type;
	int paramcont;//值参数表和函数的匹配标志
	strcpy(name, next[NEXT_index].value);
	strcat(name,"@");
	tabx = locTab(name);
	if(tabx==-1)
    {
        errorMean(UNDEF);
        tabx=0;
    }
	type = getType(tabx);
	newNext();
	if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
	}
	genQuat(NOP,-1,-1,-1,lab);
	paramcont = valParam(tabx);
	if (next[NEXT_index].sym == RPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺右括弧
	}
	genVarlab(id);
	enterTab(id, TMPVAR, type, 0, -1);
	//fprintf(data, "%s\t\tDD\t\t?\n", id);
	retabx = getTabtop();
	if (paramcont)
	{
		genQuat(RFUNC, tabx, -1, retabx, -1);
	}
	else
	{
		errorMean(PARACONT);//参数
	}
	return retabx;
}
int valParam(int tabx)
{
	int exprtabx;
	int paramcont;
	if (next[NEXT_index].sym == RPAREN)
	{
		paramcont = noParam(tabx);
		return paramcont;
	}
	exprtabx = Expression();
	paramcont = fewParams(tabx, exprtabx);
	tabx++;
	if (paramcont)
	{
		genQuat(LDPAR, exprtabx, -1, -1, -1);
	}
	else
	{
		errorMean(PARACONT);//参数
	}
	while (next[NEXT_index].sym == COMMA)
	{
		newNext();
		exprtabx = Expression();
		paramcont = fewParams(tabx, exprtabx);
		tabx++;
		if (paramcont)
		{
			genQuat(LDPAR, exprtabx, -1, -1, -1);
		}
		else
		{
			errorMean(PARACONT);//参数
		}
	}
	if (tab[tabx + 1].kind == PARAM)
	{
		errorMean(PARACONT);//参数
	}
	return paramcont;
}
int fewParams(int ftabx, int exprtabx)
{
	if (tab[ftabx + 1].kind != PARAM)
	{
		errorMean(PARACONT);//参数太少
		return FALSE;
	}
	return TRUE;
}
int noParam(int tabx)
{
	if (tab[tabx + 1].kind == PARAM)
	{
		errorMean(PARACONT);//参数数量太多
		return FALSE;
	}
	return TRUE;
}
void callProc(int lab)
{
	char name[IDMAX + 1];
	int tabx;
	int paramcont;
	strcpy(name, next[NEXT_index].value);
	strcat(name,"@");
	tabx = locTab(name);
	if (tabx == -1)
    {
        errorMean(UNDEF);//未定义标识符
        tabx=0;
    }
	newNext();
	if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
	}
	genQuat(NOP,-1,-1,-1,lab);
	paramcont = valParam(tabx);
	if (next[NEXT_index].sym == RPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺右括弧
	}
	if (paramcont)
	{
		genQuat(NFUNC, tabx, -1, -1, -1);
	}
	else
	{
		errorMean(PARACONT);//参数
	}
}
void valFunct()//有返回值函数定义分析子程序
{
	int i;
	int type;//函数类型
	char name[IDMAX + 1];//函数名
	int tabx;//函数名在符号表中的下标
	QUAT_index = -1;
	GLOBAL = FALSE;
	paranum = 0;
	if (next[NEXT_index].sym == INTSY)
	{
		type = INTNUM;
		newNext();
	}
	else if (next[NEXT_index].sym == CHARSY)
	{
		type = SCHAR;
		newNext();
	}
	else
	{
		errorGram(ILRETYPE);//无函数返回值类型
	}
	if (next[NEXT_index].sym == IDENT)
	{
		strcpy(name, next[NEXT_index].value);
		strcat(name,"@");
		newNext();
	}
	else
	{
		errorGram(IDLACK);//缺少函数名
	}
	enterTab(name, FUNC, type, 0, -1);
	if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少左括弧
	}
	Parameter();
	if (next[NEXT_index].sym == RPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少右括弧
	}
	tabx = locTab(name);
	tab[tabx].arrdim = paranum;
	genQuat(PROC, tabx, -1, -1, -1);
	if (next[NEXT_index].sym == LBRACE)
	{
		BTABX_index++;
		btabx[BTABX_index] = TAB_index + 1;
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少左花括号
	}
	Compound();
	if (next[NEXT_index].sym == RBRACE)
	{
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少右花括号
	}
	genQuat(END, tabx, -1, -1, -1);
	GLOBAL = TRUE;
	for (i = 0; i <= QUAT_index; i++)
	{
		genAsm(i);
	}
	TAB_index = btabx[BTABX_index] - 1;
	BTABX_index--;
}
void novalFunct()
{
	int i;
	char name[IDMAX + 1];
	int tabx;
	QUAT_index = -1;
	GLOBAL = FALSE;
	retflag = FALSE;
	paranum = 0;
	newNext();
	if (next[NEXT_index].sym == IDENT)
	{
		strcpy(name, next[NEXT_index].value);
		strcat(name,"@");
		newNext();
	}
	else
	{
		errorGram(IDLACK);//缺少函数名
	}
	enterTab(name, PROCE, -1, 0, -1);
	if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少左括弧
	}
	Parameter();
	if (next[NEXT_index].sym == RPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少右括弧
	}
	tabx = locTab(name);
	tab[tabx].arrdim = paranum;
	genQuat(PROC, tabx, -1, -1, -1);
	if (next[NEXT_index].sym == LBRACE)
	{
		BTABX_index++;
		btabx[BTABX_index] = TAB_index + 1;
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少左花括号
	}
	Compound();
	if (next[NEXT_index].sym == RBRACE)
	{
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少右花括号
	}
	genQuat(END, tabx, -1, -1, -1);
	GLOBAL = TRUE;
	for (i = 0; i <= QUAT_index; i++)
	{
		genAsm(i);
	}
	TAB_index = btabx[BTABX_index] - 1;	//分程序索引表赋值
	BTABX_index--;
	if(retflag)
    {
        errorMean(RETVAL);
    }
}
void mainFunct()
{
	int i;
	QUAT_index = -1;
	GLOBAL=FALSE;
	retflag = FALSE;
	newNext();
	if (next[NEXT_index].sym == MAIN)
	{
		genQuat(MPROC, TAB_index, -1, -1, -1);
		newNext();
	}
	if (next[NEXT_index].sym == LPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少左括弧
	}
	if (next[NEXT_index].sym == RPAREN)
	{
		newNext();
	}
	else
	{
		errorGram(PARENLACK);//缺少右括弧
	}
	if (next[NEXT_index].sym == LBRACE)
	{
		btabx[++BTABX_index] = TAB_index + 1;
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少左花括号
	}
	Compound();
	if (next[NEXT_index].sym == RBRACE)
	{
		newNext();
	}
	else
	{
		errorGram(BRACELACK);//缺少右花括号
	}
	if(retflag)
    {
        errorMean(RETVAL);
    }
	genQuat(MEND, -1, -1, -1, -1);
	for (i = 0; i <= QUAT_index; i++)
	{
		genAsm(i);
	}
}
void Program()
{
	printHead();
	btabx[0] = 1;
	BTABX_index = 0;
	if (next[NEXT_index].sym == CONSTSY)
	{
		constDecl();
	}
	if (next[(NEXT_index + 2) % 3].sym == SEMICOLON || next[(NEXT_index + 2) % 3].sym == COMMA || next[(NEXT_index + 2) % 3].sym == LBRACK)
	{
		varDecl();
	}
	while (next[(NEXT_index + 1) % 3].sym == IDENT)
	{
		if (next[NEXT_index].sym == INTSY || next[NEXT_index].sym == CHARSY)
		{
			valFunct();
		}
		else if (next[NEXT_index].sym == VOIDSY)
		{
			novalFunct();
		}
		else
		{
			errorGram(ILTYPE);//非法类型标识符
			newNext();
            if(next[NEXT_index].sym==null)
            {
                exit(1);
            }
		}
	}
	if (next[NEXT_index].sym == VOIDSY&&next[(NEXT_index + 1) % 3].sym == MAIN)
	{
		mainFunct();
	}
	else
	{
		errorGram(MAINLACK);//缺少主函数
	}
	if (next[NEXT_index].sym != null)
	{
		errorGram(PROGEND);//程序应结束
	}
}

//语义分析及代码生成部分
void errorMean(int errx)
{
	printf("ERROR_MEANING_%d_", line);
	switch (errx)
	{
    case PARACONT: printf("NOT CONTENT PARAMETERS"); break;
	case UNDEF: printf("UNDEFINED IDENTIFIER"); break;
	case CONSASG: printf("CONST VALUE CHANGE"); break;
	case REDEF: printf("REDEFINED IDENTIFIER"); break;
	case RETVAL: printf("PROCEDURE RETURN VALUE"); break;
	case SCANFPAR: printf("WRONG SCANF PARAMETER"); break;
	case PRINTFPAR: printf("WRONG PRINTF PARAMETER"); break;
	default: printf("OTHER"); break;
	}
	printf("\n");
	errnum++;
	//exit(1);
}
void enterTab(char name[], int kind, int type, int value, int arrdim)
{
	int i;
	if (TAB_index != 0)
	{
		for (i = btabx[BTABX_index]; i <= TAB_index; i++)
		{
			if (strcmp(name, tab[i].name) == 0 && tab[i].kind != PARAM)
			{
				errorMean(REDEF);//重复定义
			}
		}
	}
	TAB_index++;
	strcpy(tab[TAB_index].name, name);
	tab[TAB_index].kind = kind;
	tab[TAB_index].type = type;
	tab[TAB_index].value = value;
	tab[TAB_index].arrdim = arrdim;
}
int getType(int tabx)
{
	return tab[tabx].type;
}
int getTabtop()
{
	return TAB_index;
}
int genStrlabx()
{
	STAB_index++;
	strcpy(strlab[STAB_index], "@str");
	transStr(STAB_index, strlab[STAB_index]);
	return STAB_index;
}
int genNewlab()
{
	LABTAB_index++;
	strcpy(labtab[LABTAB_index], "@label");
	transStr(LABTAB_index, labtab[LABTAB_index]);
	return LABTAB_index;
}
void genVarlab(char name[])
{
	strcpy(name, "@var");
	varlabx++;
	transStr(varlabx, name);
}
void genQuat(int op, int operand_1, int operand_2, int result, int labx)
{
	quat[++QUAT_index].op = op;
	quat[QUAT_index].operand_1 = operand_1;
	quat[QUAT_index].operand_2 = operand_2;
	quat[QUAT_index].result = result;
	quat[QUAT_index].labx = labx;
	if (DEBUG == 1)
	{
		printQuat(QUAT_index);
	}
}
int locTab(char name[])
{
	int i;
	int j;
	char name_temp[IDMAX + 1];
	strcpy(name_temp, name);
	strcat(name_temp, "@");
	for (i = TAB_index; i >= 0; i--)
	{
		if (!strcmp(name_temp, tab[i].name))
		{
			break;
		}
	}
	for (j = TAB_index; j >= 0; j--)
	{
		if (!strcmp(name, tab[j].name))
		{
			break;
		}
	}
	if (i == -1)
	{
		return j;
	}
	else if (j == -1)
	{
		return i;
	}
	else
	{
		return (i > j) ? i : j;
	}
}
int newKind(int tabx1, int tabx2)
{
	return (tab[tabx1].kind == CONSVAR&&tab[tabx2].kind == CONSVAR) ? CONSVAR : TMPVAR;
}
int newType()
{
	return INTNUM;
}
void printHead()
{
	fprintf(out, ".386\n");
	fprintf(out, ".model flat, stdcall\n");
	fprintf(out, "\n");
	fprintf(out, "include F:\\masm32\\include\\msvcrt.inc\n");
	fprintf(out, "includelib F:\\masm32\\lib\\msvcrt.lib\n");
}
void printQuat(int index)
{
	if (quat[QUAT_index].labx != -1)
	{
		fprintf(quats, "%s:\n", labtab[quat[index].labx]);
	}
	switch (quat[index].op)
	{
	case PLUS: fprintf(quats, "\tADD"); break;
	case MINUS: fprintf(quats, "\tSUB"); break;
	case TIMES: fprintf(quats, "\tMUL"); break;
	case DIVI: fprintf(quats, "\tDIV"); break;
	case LSS: fprintf(quats, "\tJGE"); break;
	case LEQ: fprintf(quats, "\tJG"); break;
	case GTR: fprintf(quats, "\tJLE"); break;
	case GEQ: fprintf(quats, "\tJL"); break;
	case NEQ: fprintf(quats, "\tJZ"); break;
	case EQL: fprintf(quats, "\tJNZ"); break;
	case ASSIGN: fprintf(quats, "\tASSIGN"); break;
	case NEG: fprintf(quats, "\tNEG"); break;
	case CMP: fprintf(quats, "\tCMP"); break;
	case JMP: fprintf(quats, "\tJMP"); break;
	case RFUNC: fprintf(quats, "\tRFUNC"); break;
	case NFUNC: fprintf(quats, "\tNFUNC"); break;
	case LDPAR: fprintf(quats, "\tLDPAR"); break;
	case NOP: fprintf(quats, "\tNOP"); break;
	case SCANF: fprintf(quats, "\tSCANF"); break;
	case PRINTFE: fprintf(quats, "\tPRINTFE"); break;
	case PRINTFS: fprintf(quats, "\tPRINTFS"); break;
	case RET: fprintf(quats, "\tRET"); break;
	case PROC: fprintf(quats, "\tPROC"); break;
	case END: fprintf(quats, "\tEND"); break;
	case MPROC: fprintf(quats, "\tMPROC"); break;
	case MEND: fprintf(quats, "\tMEND"); break;
	case LOCARRAY: fprintf(quats, "\tLOCARRAY"); break;
	case LOCVAR: fprintf(quats, "\tLOCVAR"); break;
	case LDARY: fprintf(quats, "\tLDARY"); break;
	default: break;
	}
	if (quat[index].op == PRINTFS)
	{
		fprintf(quats, "\t%s", strlab[quat[index].operand_1]);
	}
	else if (quat[index].operand_1 == -1)
	{
		fprintf(quats, "\t\t");
	}
	else if (quat[index].op == LSS || quat[index].op == LEQ || quat[index].op == GTR || quat[index].op == GEQ || quat[index].op == NEQ || quat[index].op == EQL || quat[index].op == JMP)
	{
		fprintf(quats, "\t%s,", labtab[quat[index].operand_1]);
	}
	else
	{
		fprintf(quats, "\t%s,", tab[quat[index].operand_1].name);
	}
	if (quat[index].operand_2 == -1)
	{
		fprintf(quats, "\t\t");
	}
	else
	{
		fprintf(quats, "\t%s,", tab[quat[index].operand_2].name);
	}
	if (quat[index].result == -1)
	{
		fprintf(quats, "\t\t");
	}
	else
	{
		fprintf(quats, "\t%s,", tab[quat[index].result].name);
	}
	fprintf(quats, "\n");
}
void finishBuild()
{
	char chtmp;
	fprintf(out, "\n");
	fprintf(out, ".data\n");
	while ((chtmp = fgetc(data)) != EOF)
	{
		fputc(chtmp, out);
	}
	fprintf(out, "buffer\t\tDD\t\t?\n");
	fprintf(out, "_CHAR\t\tDB\t\t\'%%c\',\t0\n");
	fprintf(out, "_INT\t\tDB\t\t\'%%d\',\t0\n");
	fprintf(out, "\n");
	fprintf(out, ".code\n");
	while ((chtmp = fgetc(code)) != EOF)
	{
		fputc(chtmp, out);
	}
}
void genAsm(int qx)
{
	int i;
	switch (quat[qx].op)
	{
	case PLUS://ADD
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_2].name);
			fprintf(code, "\t\tadd\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
		}
		else if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tadd\t\teax,\t\t%d\n", tab[quat[qx].operand_2].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tadd\t\teax,\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case MINUS://SUB
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_2].name);
			fprintf(code, "\t\tsub\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
			fprintf(code, "\t\tneg\t\teax\n");
		}
		else if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tsub\t\teax,\t\t%d\n", tab[quat[qx].operand_2].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tsub\t\teax,\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case TIMES://MUL
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
			fprintf(code, "\t\tmul\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		else if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_2].value);
			fprintf(code, "\t\tmul\t\t%s\n", tab[quat[qx].operand_1].name);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tmul\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case DIVI://DIV
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
			fprintf(code, "\t\tcdq\n");
			fprintf(code, "\t\tmov\t\tecx,\t\t%s\n", tab[quat[qx].operand_2].name);
			fprintf(code, "\t\tidiv\t\tecx\n");
		}
		else if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tcdq\n");
			fprintf(code, "\t\tmov\t\tecx,\t\t%d\n", tab[quat[qx].operand_2].value);
			fprintf(code, "\t\tidiv\t\tecx\n");
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			fprintf(code, "\t\tcdq\n");
			fprintf(code, "\t\tmov\t\tecx,\t\t%s\n", tab[quat[qx].operand_2].name);
			fprintf(code, "\t\tidiv\t\tecx\n");
		}
		fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case LSS: fprintf(code, "\t\tjge\t\t%s\n", labtab[quat[qx].operand_1]); break;//JGE
	case LEQ: fprintf(code, "\t\tjg\t\t%s\n", labtab[quat[qx].operand_1]); break;//JG
	case GTR: fprintf(code, "\t\tjle\t\t%s\n", labtab[quat[qx].operand_1]); break;//JLE
	case GEQ: fprintf(code, "\t\tjl\t\t%s\n", labtab[quat[qx].operand_1]); break;//JL
	case NEQ: fprintf(code, "\t\tjz\t\t%s\n", labtab[quat[qx].operand_1]); break;//JZ
	case EQL: fprintf(code, "\t\tjnz\t\t%s\n", labtab[quat[qx].operand_1]); break;//JNZ
	case ASSIGN:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_2].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		if (tab[quat[qx].operand_1].kind == ARRAY)
		{
			if (tab[quat[qx].result].kind == CONSVAR)
			{
				fprintf(code, "\t\tmov\t\tecx,\t\t%d\n", tab[quat[qx].result].value);
			}
			else
			{
				fprintf(code, "\t\tmov\t\tecx,\t\t%s\n", tab[quat[qx].result].name);
			}
			fprintf(code, "\t\tadd\t\tecx,\t\tecx\n");
			fprintf(code, "\t\tadd\t\tecx,\t\tecx\n");
			fprintf(code, "\t\tmov\t\t%s[ecx],\t\teax\n", tab[quat[qx].operand_1].name);
		}
		else
		{
			fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].operand_1].name);
		}
	}
	break;
	case NEG:
	{
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
		}
		fprintf(code, "\t\tneg\t\teax\n");
		fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case CMP:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
		}
		if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\tecx,\t\t%d\n", tab[quat[qx].operand_2].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\tecx,\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		fprintf(code, "\t\tcmp\t\teax,\t\tecx\n");
	}
	break;
	case JMP:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		fprintf(code, "\t\tjmp\t\t%s\n", labtab[quat[qx].operand_1]);
	}
	break;
	case RFUNC:
	{
		paragot = 0;
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		fprintf(code, "\t\tinvoke\t\t%s", tab[quat[qx].operand_1].name);
		for (i = qx - 1; i >= 0; i--)
		{
			if (paragot >= tab[quat[qx].operand_1].arrdim)
			{
				break;
			}
			if (quat[i].op == LDPAR)
			{
				paragot++;
			}
		}
		for (i = i + 1; i < qx; i++)
		{
			if (quat[i].op == LDPAR)
			{
				if (tab[quat[i].operand_1].kind == CONSVAR)
				{
					fprintf(code, ",\t%d", tab[quat[i].operand_1].value);
				}
				else
				{
					fprintf(code, ",\t%s", tab[quat[i].operand_1].name);
				}
			}
		}
		fprintf(code, "\n\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case NFUNC:
	{
		paragot = 0;
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		fprintf(code, "\t\tinvoke\t\t%s", tab[quat[qx].operand_1].name);
		for (i = qx - 1; i >= 0; i--)
		{
			if (paragot >= tab[quat[qx].operand_1].arrdim)
			{
				break;
			}
			if (quat[i].op == LDPAR)
			{
				paragot++;
			}
		}
		for (i = i + 1; i < qx; i++)
		{
			if (quat[i].op == LDPAR)
			{
				if (tab[quat[i].operand_1].kind == CONSVAR)
				{
					fprintf(code, ",\t%d", tab[quat[i].operand_1].value);
				}
				else
				{
					fprintf(code, ",\t%s", tab[quat[i].operand_1].name);
				}
			}
		}
		fprintf(code, "\n");
	}
	break;
	case NOP:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
	}
	break;
	case SCANF:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].type == INTNUM)
		{
			fprintf(code, "\t\tinvoke\t\tcrt_scanf,\taddr\t_INT,\taddr\t%s\n", tab[quat[qx].operand_1].name);
		}
		else
		{
			fprintf(code, "\t\tinvoke\t\tcrt_scanf,\taddr\t_CHAR,\taddr\t%s\n", tab[quat[qx].operand_1].name);
		}
	}
	break;
	case PRINTFE:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (tab[quat[qx].operand_1].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
		}
		if (tab[quat[qx].operand_1].type == SCHAR)
		{
			fprintf(code, "\t\tinvoke\t\tcrt_printf,\taddr\t_CHAR,\teax\n");
		}
		else
		{
			fprintf(code, "\t\tinvoke\t\tcrt_printf,\taddr\t_INT,\teax\n");
		}
	}
	break;
	case PRINTFS:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		fprintf(code, "\t\tinvoke\t\tcrt_printf,\taddr\t%s\n", strlab[quat[qx].operand_1]);
	}
	break;
	case RET:
	{
		if (quat[qx].labx != -1)
		{
			fprintf(code, "%s:\n", labtab[quat[qx].labx]);
		}
		if (quat[qx].operand_1 != -1)
		{
			if (tab[quat[qx].operand_1].kind == CONSVAR)
			{
				fprintf(code, "\t\tmov\t\teax,\t\t%d\n", tab[quat[qx].operand_1].value);
			}
			else
			{
				fprintf(code, "\t\tmov\t\teax,\t\t%s\n", tab[quat[qx].operand_1].name);
			}
		}
		fprintf(code, "\t\tret\n");
	}
	break;
	case PROC:
	{
		fprintf(code, "%s\t\tproc", tab[quat[qx].operand_1].name);
		for (i = quat[qx].operand_1 + 1; i <= TAB_index; i++)
		{
			if (tab[i].kind != PARAM)
			{
				break;
			}
			fprintf(code, "\t%s: dword", tab[i].name);
			if (tab[i + 1].kind == PARAM)
			{
				fprintf(code, ",");
			}
		}
		fprintf(code, "\n");
		for (i = quat[qx].operand_1 + 1; tab[i].kind != PROCE&&tab[i].kind != FUNC&&i <= TAB_index; i++)
		{
			if (tab[i].kind == TMPVAR)
			{
				fprintf(code, "\t\tlocal\t\t%s: dword\n", tab[i].name);
			}
		}
	}
	break;
	case END:
	{
		fprintf(code, "\t\tret\n");
		fprintf(code, "%s\t\tendp\n", tab[quat[qx].operand_1].name);
	}
	break;
	case LDARY:
	{
		if (tab[quat[qx].operand_2].kind == CONSVAR)
		{
			fprintf(code, "\t\tmov\t\tecx,\t\t%d\n", tab[quat[qx].operand_2].value);
		}
		else
		{
			fprintf(code, "\t\tmov\t\tecx,\t\t%s\n", tab[quat[qx].operand_2].name);
		}
		fprintf(code, "\t\tadd\t\tecx,\t\tecx\n");
		fprintf(code, "\t\tadd\t\tecx,\t\tecx\n");
		fprintf(code, "\t\tmov\t\teax,\t\t%s[ecx]\n", tab[quat[qx].operand_1].name);
		fprintf(code, "\t\tmov\t\t%s,\t\teax\n", tab[quat[qx].result].name);
	}
	break;
	case MPROC:
	{
		fprintf(code, "main\t\tproc\n");
		for (i = quat[qx].operand_1 + 1; tab[i].kind != PROCE&&tab[i].kind != FUNC&&i <= TAB_index; i++)
		{
			if (tab[i].kind == TMPVAR)
			{
				fprintf(code, "\t\tlocal\t\t%s: dword\n", tab[i].name);
			}
		}
	}
	break;
	case MEND:
	{
		fprintf(code, "\t\tret\n");
		fprintf(code, "main\t\tendp\n");
		fprintf(code, "end\t\tmain\n");
	}
	break;
	case LOCARRAY: fprintf(code, "\t\tlocal\t\t%s[%d]: dword\n", tab[quat[qx].operand_1].name, tab[quat[qx].operand_1].arrdim); break;
	case LOCVAR: fprintf(code, "\t\tlocal\t\t%s: dword\n", tab[quat[qx].operand_1].name); break;
	default: break;
	}
}

//主程序部分
void init()
{
	DEBUG = TRUE;
	GLOBAL = TRUE;
	FIRSTCASE=TRUE;
	line = 1;
	NEXT_index = 0;
	TAB_index = 0;
	BTABX_index = -1;
	QUAT_index = -1;
	STAB_index = -1;
	LABTAB_index = -1;
	ATAB_index = -1;
	varlabx = -1;
	paranum = 0;
	paragot = 0;
	errnum = 0;
}
int main()
{
	init();
	FILEIN = (char*)malloc(20 * sizeof(char));
	printf("Please input your filename for test: ");
	scanf("%s", FILEIN);
	if ((in = fopen(FILEIN, "r")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	if ((out = fopen("out.asm", "w")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	if ((data = fopen("data.txt", "w")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	if ((code = fopen("code.txt", "w")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	if ((quats = fopen("quats.txt", "w")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	initNext();
	Program();
	fclose(in);
	free(FILEIN);
	fclose(data);
	fclose(code);
	if ((data = fopen("data.txt", "r")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	if ((code = fopen("code.txt", "r")) == NULL)
	{
		printf("Fail to open the file!\n");
		exit(1);
	}
	if(errnum == 0)
    {
        finishBuild();
        printf("Compiled.\n");
    }
	fclose(out);
	fclose(data);
	fclose(code);
	fclose(quats);
	return 0;
}
