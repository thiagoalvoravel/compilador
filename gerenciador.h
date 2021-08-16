#ifndef GERENCIADOR_H_INCLUDED
#define GERENCIADOR_H_INCLUDED

typedef struct p{
        int quantidade;
        int tipo[TAM];
}PARAMETRO;

typedef struct g{
        char lexema[TAM];
        int zombie;
        int tipo;
        int escopo;
        int classe;
        int linha;
        PARAMETRO param;
}G_TABELA;

int escopo,topo;
G_TABELA gT[TAM];

void gerenciador_tab(int cod,int zombie,int classe);
void inserir(int cod,int zombie,int classe);
int consultar(int cod,int zombie,int classe);
void exclusao();
void adicionaTipoParamFWD(int cod,int aux);
void checaTipoParam(int cod,int aux,int pos);
int verificaFWD();
void checaTipoRetorno(int cod);
void redeclaracaoFWD(int classe,int aux);

#endif // GERENCIADOR_H_INCLUDED
