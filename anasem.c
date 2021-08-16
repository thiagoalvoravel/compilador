#include "analex.h"
#include "anasin.h"
#include "gerenciador.h"

int indice=0;

int variavelDeclaraAtrib(){
    int aux,troca;
    aux = topo;
    troca = 0;

    if (tk.cat == ID){
        if (escopo == 1){
            while (aux > 0){

                    if (troca == 1){
                        if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                            if ( gT[aux].escopo == 0){
                               return gT[aux].tipo;
                            }
                        }
                    }
                    else{
                        if ( (gT[aux].classe == FUNC) ){
                           if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                              return gT[aux].tipo;
                           }
                           troca = 1;
                        }
                        if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                            if ( gT[aux].escopo == escopo){
                                if ((gT[aux].classe == LOCAL)|| (gT[aux].classe == PARAM)){
                                    return gT[aux].tipo;
                                }
                            }
                        }
                    }
                aux -= 1;
            }
        }
        else{
            while (aux > 0){
                   if ( (gT[aux].escopo == escopo) ){
                      if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                          return gT[aux].tipo;
                      }
                   }
                   aux -= 1;
            }
        }
        printf("Variavel nao declarada na linha %d\n",linha);
        system("PAUSE");
        exit(1);
    }
    return tk.cat;
}
/*
void verificaProcedimento(){
     int aux;

     aux = topo;
     while (aux > 0){
            if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                if ( gT[aux].classe == PROC){
                    indice = aux;
                    return;
                }
                else{
                    printf("Apenas procedimentos podem ser chamados por CALL na linha %d\n",linha);
                    system("PAUSE");
                    exit(1);
                }
            }
            aux--;
     }
}
*/

void verificaTipoExp(){
           int aux;

           if (tk.cat == SN){
               return;
           }

           if (tk.cat == ID){
               aux = variavelDeclaraAtrib();
           }
           if ( (aux == INT) || (tk.cat == CTI) || (aux == BOOL) );
           else{
                printf("Inconsistencia de tipos na linha %d\n",linha);
                system("PAUSE");
                exit(1);
           }
}

int retornaClasse(){
     int aux;
     aux = topo;

     while (aux>0){
            if (escopo == 0){
                if ( ((strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0) && (gT[aux].escopo == 0) ){
                    if ( (gT[aux].classe == FUNC)){
                        indice = aux;
                    }
                    return gT[aux].classe;
                }

            }
            else{
                if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                    if ( (gT[aux].classe == FUNC)){
                        indice = aux;
                    }
                    return gT[aux].classe;
                }
            }
          aux -=1;
     }
     return 0;
}

int checaReturn(){
    int aux;
     aux = topo;

     while (aux>0){
            if ( (gT[aux].classe == FUNC) ){
                break;
            }
          aux -=1;
     }
     return gT[aux].classe;
}

void checaChamada(int aux){
      indice +=1;
      if (gT[indice].classe == PARAM){
         if (gT[indice].tipo == aux);
         else{
            printf("Inconsistencia na chamada de funcao na linha %d\n",linha);
            system("PAUSE");
            exit(1);
         }
      }
      else{
         if (indice != 0){
            printf("Parametros a mais na funcao da linha %d\n",linha);
            system("PAUSE");
            exit(1);
         }
      }
}

void paramMenos(){
	if (gT[indice+1].classe == PARAM){
		printf("Faltam parametros na chamada da funcao linha %d\n",linha);
		system("PAUSE");
		exit(1);
	}
}

void verificaTipo(int tipo){
	int aux,classe;
	
	classe = retornaClasse();
	
	if (tk.cat == ID){
	   aux = variavelDeclaraAtrib();
	   if (indice != 0){
	        if ( (classe == GLOBAL) || (classe == LOCAL) ){
	            checaChamada(aux);
	        }
	   }
	}
	/*
	if (classe == PROC){
		printf("Procedimento so pode ser chamado por CALL, na linha %d\n",linha);
	   	system("PAUSE");
	   	exit(1);
	}
	*/
	
	if (tipo == FLOAT){
	    if ( (aux == FLOAT) || (tk.cat == CTR) );
	    else{
	        printf("Inconsistencia de tipos na linha %d\n",linha);
	        system("PAUSE");
	        exit(1);
	    }
	}
	
	if (tipo == INT){
	   if ( (aux == INT) || (tk.cat == CTI) || (aux == CHAR) || (tk.cat == CTC) || (aux == BOOL) );
	   else{
	      printf("Inconsistencia de tipos na linha %d\n",linha);
	      system("PAUSE");
	      exit(1);
	   }
	}
	
	if (tipo == CHAR){
	   if ( (aux == CHAR) || (aux == INT) || (tk.cat == CTC) || (tk.cat == CTI) );
	   else{
	      printf("Inconsistencia de tipos na linha %d\n",linha);
	      system("PAUSE");
	      exit(1);
	   }
	}
}

void variavelDeclara(){
    int aux,troca;
    aux = topo;
    troca = 0;

    if (tk.cat == ID){
        if (escopo == 1){
            while (aux > 0){

                    if (troca == 1){
                        if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                            if ( gT[aux].escopo == 0){
                               return;
                            }
                        }
                    }
                    else{
                        if ( (gT[aux].classe == FUNC) ){
                           troca = 1;
                        }
                        if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                            if ( gT[aux].escopo == escopo){
                                if ((gT[aux].classe == LOCAL)|| (gT[aux].classe == PARAM)){
                                    return;
                                }
                            }
                        }
                    }
                aux -= 1;
            }
        }
        else{
            while (aux > 0){
                   if ( (gT[aux].escopo == escopo) ){
                      if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                          return;
                      }
                   }
                   aux -= 1;
            }
        }
        printf("Variavel nao declarada na linha %d\n",linha);
        system("PAUSE");
        exit(1);
    }
}

void adicionaTipoParam(int cod,int aux){
     int cont;
     cont = topo;

     while (1){
            if ( (gT[cont].classe == FUNC) ){
                //printf("Aqui %s\n",gT[cont].lexema);
                gT[cont].param.quantidade = aux;
                gT[cont].param.tipo[aux-1] = cod;
                break;
            }
            cont -=1;
     }
}

void checaTipoParam(int cod,int aux,int pos){

    if (cod == VOID){
        if ( gT[pos].param.tipo[0] == VOID ){
            adicionaTipoParam(cod,aux);
            return;
        }
        else{
            printf("Tipos de parametros inconsistentes na linha %d\n",linha);
            system("PAUSE");
            exit(1);
        }
    }

    if ( gT[pos].param.quantidade < aux ){
        printf("Tipos de parametros inconsistentes na linha %d\n",linha);
        system("PAUSE");
        exit(1);
    }
    else{
        if ( gT[pos].param.tipo[aux-1] == cod );
        else{
            printf("Tipos de parametros inconsistentes na linha %d\n",linha);
            system("PAUSE");
            exit(1);
        }
    }
    adicionaTipoParam(cod,aux);
}

void checaTipoRetorno(int cod){
    int aux;
    aux = topo;

     while ( aux > 0 ){
            if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                if (gT[aux].tipo == cod){
                    break;
                }
                else{
                    printf("Funcao com valor de retorno incompativel com a assinatura na linha %d\n",linha);
                    system("PAUSE");
                    exit(1);
                }
            }
            aux -= 1;
    }
}

void redeclaracaoFWD(int classe,int aux){
      while ( aux > 0 ){
            if ( (strcmp(gT[aux].lexema,tk.tipo.lexema)) == 0 ){
                if (gT[aux].classe == FWD){
                    printf("Assinatura redeclarada na linha %d\n",linha);
                    system("PAUSE");
                    exit(1);
                }
                if ( (gT[aux].classe == FUNC) ){
                    printf("Assinatura deve vir acima da funcao na linha %d\n",linha);
                    system("PAUSE");
                    exit(1);
                }
            }
            aux -= 1;
     }
}

int verificaFWD(){
    int topoAux;
    char lexemaAux[TAM];
    topoAux = topo-1;


    strcpy(lexemaAux,gT[topo].lexema);
    while ( topoAux > 0 ){
        if ( (strcmp(gT[topoAux].lexema,lexemaAux)) == 0 ){
            return topoAux;
        }
        topoAux -= 1;
    }
    return 0;
}

void adicionaTipoParamFWD(int cod,int aux){

     if (cod == VOID){
        gT[topo].param.quantidade = 0;
        gT[topo].param.tipo[0] = VOID;
        return;
     }

     if (aux == 0){
        gT[topo].param.quantidade = 0;
     }
     
     gT[topo].param.quantidade = aux+1;
     gT[topo].param.tipo[aux] = cod;
}
