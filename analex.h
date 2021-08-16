#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 1001

//Categorias de tokens
typedef enum{ID,PR,SN,CTI,CTR,CTC,CTL}categoria;
//Sinais aceitos
typedef enum{OR,ENDERECO,AND,NOT,MULTIPLICACAO,DIVISAO,SOMA,SUBTRACAO,MENOR,MENORIGUAL,MAIOR,MAIORIGUAL,IGUAL,ATRIBUICAO,DIFERENTE,VIRGULA,PONTO_VIRGULA,ABRIRPARENTESE,FECHARPARENTESE,ABRIRCHAVE,FECHARCHAVE,ABRIRCOCHETE,FECHARCOCHETE}sinais;
char listaSinais[100][100];

typedef struct t{
    categoria cat;
    union {
        char lexema[1000];
        int codigo;
        int valor_int;
        float valor_real;
    }tipo;
}TOKEN;

FILE *fp;
int linha;
TOKEN tk;

//Palavras reservadas
char pReservada[100][10];
char constLiteral [1000][1000];

FILE * abrirArquivo(char nomeArquivo[]);
TOKEN montaToken(int cat,char token[],char ch,int pos);
int searchPR(char token[]);
int adicionaLiteral(char literal[]);
TOKEN analexico();
