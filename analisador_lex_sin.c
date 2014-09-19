#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TKId 1
#define TKWhile 2
#define TKFor 3
#define TKSwitch 4
#define TKCase 5
#define TKOtherwise 6
#define TKEnd 7
#define TKIf 8
#define TKElse 9
#define TKElseIf 10
#define TKAtrib 11
#define TKSoma 12
#define TKAbrePar 13
#define TKFechaPar 14
#define TKAbreChave 15
#define TKFechaChave 16
#define TKVirgula 17
#define TKPontoeVirg 18
#define TKString 19
#define TKAbreColchete 20
#define TKFechaColchete 21
#define TKSubtracao 22
#define TKMultiplicacao 23
#define TKPotencia 24
#define TKDivisao 25

int pos = 0;

struct pal_res{
	char palavra[20];
	int tk;
};

struct pal_res lista_pal[] =
{
	{ "while", TKWhile },
	{ "for", TKFor },
	{ "switch", TKSwitch },
	{ "case", TKCase },
	{ "otherwise", TKOtherwise },
	{ "end", TKEnd },
	{ "if", TKIf },
	{ "else", TKElse },
	{ "elseif", TKElseIf },
	{ "fimtabela", TKId }
};

int palavra_reservada(char lex[])
{
	int postab = 0;
	while (strcmp("fimtabela", lista_pal[postab].palavra) != 0)
	{
		if (strcmp(lex, lista_pal[postab].palavra) == 0)
		{
			return lista_pal[postab].tk;
		}
		postab++;
	}
	return TKId;
}


int rec_equ(char st[], char lex[])
{
	int estado = 0,
		fim = 0,
		posl = 0;

	while (!fim)
	{
		char c = st[pos];
		lex[posl++] = c;
		switch (estado)
		{
		case 0:
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
			{
				pos++;
				estado = 1;
				break;
			}
			if (c == '\'')
			{
				pos++;
				estado = 2;
				break;
			}
			if (c == '=')
			{
				lex[posl] = '\0';
				pos++;
				return TKAtrib;
			}
			if (c == '+')
			{
				lex[posl] = '\0';
				pos++;
				return TKSoma;
			}
			if (c == '-')
			{
				lex[posl] = '\0';
				pos++;
				return TKSubtracao;
			}
			if (c == '*')
			{
				lex[posl] = '\0';
				pos++;
				return TKMultiplicacao;
			}
			if (c == '^')
			{
				lex[posl] = '\0';
				pos++;
				return TKPotencia;
			}
			if (c == '/')
			{
				lex[posl] = '\0';
				pos++;
				return TKDivisao;
			}
			if (c == '(')
			{
				lex[posl] = '\0';
				pos++;
				return TKAbrePar;
			}
			if (c == ')')
			{
				lex[posl] = '\0';
				pos++;
				return TKFechaPar;
			}
			if (c == '{')
			{
				lex[posl] = '\0';
				pos++;
				return TKAbreChave;
			}
			if (c == '}')
			{
				lex[posl] = '\0';
				pos++;
				return TKFechaChave;
			}
			if (c == '[')
			{
				lex[posl] = '\0';
				pos++;
				return TKAbreColchete;
			}
			if (c == ']')
			{
				lex[posl] = '\0';
				pos++;
				return TKFechaColchete;
			}
			if (c == ',')
			{
				lex[posl] = '\0';
				pos++;
				return TKVirgula;
			}
			if (c == ';')
			{
				lex[posl] = '\0';
				pos++;
				return TKPontoeVirg;
			}
			if (c == ' ' || c == '\n')
			{
				pos++;
				posl--;
			}
			if (c == '\0')
			{
				return -1;
			}
			break;
		case 1:
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
			{
				pos++;
				break;
			}
			lex[--posl] = '\0';
			return palavra_reservada(lex);
		case 2:
			if (c == '\'')
			{
				lex[posl] = '\0';
				pos++;
				return TKString;
			}
			pos++;
			break;
		}
	}
}

int main()
{
	int tk;
	char exp1[200], lex[20];
	printf("Digite o programa a ser analisado (ex: void main(){int a,b,c;a=b+c;}\n");
	gets(exp1);
	while ((tk = rec_equ(exp1, lex)) != -1)
	{
		printf("%d %s\n", tk, lex);
	}
	system("pause");
}
