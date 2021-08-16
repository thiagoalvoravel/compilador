#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED

int indice;

int variavelDeclaraAtrib();
void verificaTipoExp();
void verificaTipo(int tipo);
int retornaUtilizando();
void checaChamada(int aux);
int retornaClasse();
int checaReturn();
void paramMenos();
void variavelDeclara();
void adicionaTipoParam(int cod,int aux);
void checaTipoParam(int cod,int aux,int pos);
void adicionaTipoParamFWD(int cod,int aux);
int verificaFWD();
void checaTipoRetorno(int cod);
void redeclaracaoFWD(int classe,int aux);

//void verificaProcedimento();

#endif // SEMANTICO_H_INCLUDED
