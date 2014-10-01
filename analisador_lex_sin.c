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
#define TKComentario 26
#define TKConstante 27
#define TKIgual 28
#define TKDiferente 29
#define TKMaior 30
#define TKMaiorIgual 31
#define TKMenor 32
#define TKMenorIgual 33
#define TKEBinario 34
#define TKELogico 35
#define TKOuLogico 36
#define TKOuBinario 37
#define TKFuncao 38

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
		posl = 0,
		palavra;

	while (!fim)
	{
		char c = st[pos];
		lex[posl++] = c;
		switch (estado)
		{
		case 0:
			if (c == '\0')
			{
				return -1;
			}
			pos++;
			if (c == ' ' || c == '\n')
			{
				posl--;
				break;
			}
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
			{
				estado = 1;
				break;
			}
			else if (c >= '0' && c <= '9' || c == '.')
			{
				estado = 7;
				break;
			}
			else if (c == '\'')
			{
				estado = 2;
				break;
			}
			else if (c == '%')
			{
				estado = 3;
				break;
			}
			else if (c == '=') {
				estado = 8;
				break;
			}
			else if (c == '~') {
				estado = 9;
				break;
			}
			else if (c == '>') {
				estado = 10;
				break;
			}
			else if (c == '<')
			{
				estado = 11;
				break;
			}
			else if (c == '&')
			{
				estado = 12;
				break;
			}
			else if (c == '|')
			{
				estado = 13;
				break;
			}
			else if (c == '+')
			{
				lex[posl] = '\0';
				return TKSoma;
			}
			else if (c == '-')
			{
				lex[posl] = '\0';
				return TKSubtracao;
			}
			else if (c == '*')
			{
				lex[posl] = '\0';
				return TKMultiplicacao;
			}
			else if (c == '^')
			{
				lex[posl] = '\0';
				return TKPotencia;
			}
			else if (c == '/')
			{
				lex[posl] = '\0';
				return TKDivisao;
			}
			else if (c == '(')
			{
				lex[posl] = '\0';
				return TKAbrePar;
			}
			else if (c == ')')
			{
				lex[posl] = '\0';
				return TKFechaPar;
			}
			else if (c == '{')
			{
				lex[posl] = '\0';
				return TKAbreChave;
			}
			else if (c == '}')
			{
				lex[posl] = '\0';
				return TKFechaChave;
			}
			else if (c == '[')
			{
				lex[posl] = '\0';
				return TKAbreColchete;
			}
			else if (c == ']')
			{
				lex[posl] = '\0';
				return TKFechaColchete;
			}
			else if (c == ',')
			{
				lex[posl] = '\0';
				return TKVirgula;
			}
			else if (c == ';')
			{
				lex[posl] = '\0';
				return TKPontoeVirg;
			}
			break;
		case 1:
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_')
			{
				pos++;
				break;
			}
			palavra = palavra_reservada(lex);
			if (palavra == TKId)
			{
				estado = 14;
				break;
			}
			lex[--posl] = '\0';
			return palavra;
		case 2:
			pos++;
			if (c != '\'')
			{
				break;
			}
			lex[posl] = '\0';
			return TKString;
		case 3:
			if (c == '{')
			{
				estado = 4;
			}
			else
			{
				estado = 6;
			}
			pos++;
			break;
		case 4:
			if (c == '%')
			{
				estado = 5;
			}
			pos++;
			break;
		case 5:
			pos++;
			if (c != '}')
			{
				estado = 4;
				break;
			}
			lex[posl] = '\0';
			return TKComentario;
		case 6:
			if (c != '\n')
			{
				pos++;
				break;
			}
			lex[posl] = '\0';
			return TKComentario;
		case 7:
			if (c >= '0' && c <= '9' || c == '.')
			{
				pos++;
				break;
			}
			lex[--posl] = '\0';
			return TKConstante;
		case 8:
			pos++;
			lex[posl] = '\0';
			if (c == '=')
			{
				return TKIgual;
			}
			else
			{
				return TKAtrib;
			}
			break;
		case 9:
			if (c == '=')
			{
				pos++;
				lex[posl] = '\0';
				return TKDiferente;
			}
			break;
		case 10:
			pos++;
			lex[posl] = '\0';
			if (c == '=')
			{
				return TKMaiorIgual;
			}
			else
			{
				return TKMaior;
			}
			break;
		case 11:
			pos++;
			lex[posl] = '\0';
			if (c == '=')
			{
				return TKMenorIgual;
			}
			else
			{
				return TKMenor;
			}
			break;
		case 12:
			pos++;
			lex[posl] = '\0';
			if (c == '&')
			{
				return TKELogico;
			}
			else
			{
				return TKEBinario;
			}
			break;
		case 13:
			pos++;
			lex[posl] = '\0';
			if (c == '|')
			{
				return TKOuLogico;
			}
			else
			{
				return TKOuBinario;
			}
			break;
		case 14:
			posl--;
			if (c == ' ')
			{
				pos++;
				break;
			}
			lex[--posl] = '\0';
			if (c == '(')
			{
				return TKFuncao;
			}
			return TKId;
		}

	}
}

int main()
{
	int tk;
	char lex[20];
	/*
	char exp1[200];
	printf("Digite o programa a ser analisado (ex: void main(){int a,b,c;a=b+c;}\n");
	gets(exp1);
	while ((tk = rec_equ(exp1, lex)) != -1)
	{
	printf("%d %s\n", tk, lex);
	}
	*/

	FILE * fp = fopen("C:\\Users\\UCS\\Documents\\MATLAB\\Untitled.m", "r");
	int i = 0;
	char ch;
	size_t space = 1;
	char* characters = (char *)malloc(space);

	if (fp == NULL)
		printf("Erro ao abrir o arquivo.\n");

	while ((ch = fgetc(fp)) != EOF)
	{
		characters[i] = ch;
		i++;
		space++;
		characters = (char *)realloc(characters, space);
	}

	characters[i] = '\0';

	//for (int x = 0; x < i; x++) {
	//	printf("%c\n", characters[x]);
	//}

	while ((tk = rec_equ(characters, lex)) != -1)
	{
		printf("%d %s\n", tk, lex);
	}

	for (int i = 0; i < 20; i++)
	{
		lex[i] = '\0';
	}

	printf("%s\n", lex);

	//getchar();
	system("pause");
	return 0;
}
