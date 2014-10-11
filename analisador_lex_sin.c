#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TKFim -1
#define TKErro -2
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
#define TKConstanteInteira 27
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
#define TKConstanteReal 38
#define TKFunction 39
#define TKBreak 40

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
	{ "function", TKFunction },
	{ "break", TKBreak },
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


int rec_equ(char st[], char lex[], int * linha, int * coluna)
{
	int estado = 0,
		fim = 0,
		posl = 0,
		palavra;

	while (!fim)
	{
		char c = st[pos];
		(*coluna) += 1;
		lex[posl++] = c;
		switch (estado)
		{
		case 0:
			if (c == '\0')
			{
				return TKFim;
			}
			pos++;
			if (c == ' '){ 
				posl--;	
				break; 
			}
			if(c == '\n'){
				posl--;	
				(*linha) += 1;
				(*coluna) = 0;
				break; 
			}
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
			{
				estado = 1;
				break;
			}
			if (c >= '0' && c <= '9') { estado = 7; break; }
			if (c == '.') { estado = 14; break; }
			if (c == '\'') { estado = 2; break; }
			if (c == '%') { estado = 3; break; }
			if (c == '=') { estado = 8; break; }
			if (c == '~') { estado = 9; break; }
			if (c == '>') { estado = 10; break; }
			if (c == '<') { estado = 11; break; }
			if (c == '&') { estado = 12; break; }
			if (c == '|') { estado = 13; break; }

			lex[posl] = '\0';
			if (c == '+') { return TKSoma; }
			if (c == '-') { return TKSubtracao; }
			if (c == '*') { return TKMultiplicacao; }
			if (c == '^') { return TKPotencia; }
			if (c == '/') { return TKDivisao; }
			if (c == '(') { return TKAbrePar; }
			if (c == ')') { return TKFechaPar; }
			if (c == '{') { return TKAbreChave; }
			if (c == '}') { return TKFechaChave; }
			if (c == '[') { return TKAbreColchete; }
			if (c == ']') { return TKFechaColchete; }
			if (c == ',') { return TKVirgula; }
			if (c == ';') { return TKPontoeVirg; }
			if (c == '_') { return TKErro; }
			break;
		case 1:
			if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_')
			{
				pos++;
				break;
			}
			lex[--posl] = '\0';
			palavra = palavra_reservada(lex);
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
			else if (c == '\n')
			{
				lex[--posl] = '\0';
				(*linha) += 1;
				(*coluna) = 0;
				return TKComentario;
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
			(*linha) += 1;
			(*coluna) = 0;
			lex[--posl] = '\0';
			return TKComentario;
		case 7:
			if (c >= '0' && c <= '9')
			{
				pos++;
				break;
			}
			else if (c == '.')
			{
				pos++;
				estado = 14;
				break;
			}
			else if (c == 'e')
			{
				pos++;
				estado = 15;
				break;
			}
			lex[--posl] = '\0';
			return TKConstanteInteira;
		case 14:
			if (c >= '0' && c <= '9')
			{
				pos++;
				break;
			}
			if (c == 'e')
			{
				pos++;
				estado = 15;
				break;
			}
			if (c == '.')
			{
				pos++;
				return TKErro;
			}
			lex[--posl] = '\0';
			return TKConstanteReal;
		case 15:
			if (c >= '0' && c <= '9')
			{
				pos++;
				break;
			}
			if (c == '.' || c == 'e')
			{
				pos++;
				return TKErro;
			}
			lex[--posl] = '\0';
			return TKConstanteReal;
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
		}
	}
}

int main()
{
	int tk;
	char lex[200];
	int i = 0;
	char ch;
	size_t space = 1;
	char* characters = (char *)malloc(space);

	FILE * fp = fopen("Untitled.m", "r");

	if (fp == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	while ((ch = fgetc(fp)) != EOF)
	{
		characters[i] = ch;
		i++;
		space++;
		characters = (char *)realloc(characters, space);
	}

	characters[i] = '\0';

	FILE * newFile = fopen("resultado.txt", "w");

	if (newFile == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	int linha = 1, coluna = 0, colunaX = 1;
	while ((tk = rec_equ(characters, lex, &linha, &coluna)) != TKFim)
	{
		if (tk == TKErro)
		{
			printf("Ocorreu um erro lexico!\n");
			break;
		}
		colunaX = coluna - strlen(lex);
		printf("Token: %d Lex: %s Linha: %d Coluna: %d\n", tk, lex, linha, colunaX);
		fprintf(newFile, "%d %s\n", tk, lex);
	}

	//printf("%s\n", lex);
	fclose(newFile);

	//getchar();
	system("pause");
	return 0;
}
