#include "analex.h"
#include "anasin.h"
#include "gerenciador.h"
#include "anasem.h"

G_TABELA gT[TAM];
int topo;

void gerenciador_tab(int cod,int zombie,int classe){
    if (cod == EXCLUIR){
        exclusao();
        return;
    }
    if (cod == NADA){
        return;
    }
    if ( cod == PRIMEIRO ){
        topo = 0;
        memset(gT,0,TAM);
        strcpy(gT[topo].lexema,tk.tipo.lexema);
        gT[topo].escopo = escopo;
        gT[topo].zombie = 0;
        return;
    }
    if ( consultar(cod,zombie,classe)){
        inserir(cod,zombie,classe);
    }
    else{
        printf("Redeclaracao de variavel na linha %d\n",linha);
        exit(1);
    }
}

void inserir(int cod,int zombie,int classe){
    topo += 1;
    strcpy( gT[topo].lexema ,tk.tipo.lexema);
    gT[topo].escopo = escopo;
    gT[topo].zombie = zombie;
    gT[topo].tipo = cod;
    gT[topo].classe = classe;
    gT[topo].linha = linha;
}

int consultar(int cod,int zombie,int classe){
        int aux;
        aux = topo;

        if ( (strcmp(tk.tipo.lexema,gT[0].lexema)) == 0 ){
            return 0;
        }
        
        if ( classe == FUNC ){
            checaTipoRetorno(cod);
        }

        if (classe == FWD){
            redeclaracaoFWD(classe,aux);
            return 1;
        }

        aux = topo;
        while ( aux > 0 ){
            if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                if ( gT[aux].escopo == escopo){
                        if ( gT[aux].zombie == 0 ){
                            if ( (classe == FUNC) ){
                                return 1;
                            }
                            else{
                                if ( (classe == LOCAL) && (gT[aux].linha != linha) ){
                                    return 1;
                                }
                                return 0;
                            }
                        }
                        else{
                            if ( (classe == PARAM)){
                                if (  (strcmp(gT[aux].lexema,tk.tipo.lexema)) < 0 ){
                                    return 1;
                                }
                                else{
                                    if (gT[aux].linha != linha){
                                        return 1;
                                    }
                                    else{
                                        return 0;
                                    }

                                }
                            }
                            else{
                                if ( (classe == LOCAL) && (gT[aux].linha != linha) ){
                                    return 1;
                                }
                                return 0;
                            }
                        }
                }
                return 1;
            }
            aux -= 1;
        }
        return 1;
}

void exclusao(){
    while (1){
        if ( (gT[topo].zombie == 0) && ((gT[topo].escopo == 1)) ){
            topo = topo - 1;
        }
        else{
            break;
        }
    }
}
