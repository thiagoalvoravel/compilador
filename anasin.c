#include "anasin.h"
#include "analex.h"
#include "gerenciador.h"
#include "anasem.h"

int aux;
int escopo = 0;
int flag;

void sintatico (){
    proxToken();
    prog();
}

void error_sintatico(){
    printf("Erro sintatico na linha %d\n",linha);
    system("PAUSE");
    exit(1);
}

void prog(){
    func();
    cmd();
    while( cmd());
}

void var(int classe){
    int cod;
    if ( (cod = tipo()) ){
        decl_var(cod,classe);
    }
}

void decl_var(int cod,int classe){
    match_ID(cod,0,classe);
    if (match_SN_cond(ABRIRCOCHETE) ){
    	match_CTI();
    	match_SN(FECHARCOCHETE);
        decl_var(cod,classe);
    }
    else{
        var(classe);
    }
}

void decl(){
	int cod;
    if ( ( cod = (tipo())) ){
    	if ( (match_ID_cond(NADA)) ){
    		match_SN(ABRIRPARENTESE);
    		tipos_param(0);
    		if(match_SN_cond(VIRGULA)){
    			match_ID(cod,0,0);
    			match_SN(ABRIRPARENTESE);
    			tipos_param(0);
    			match_SN(FECHARPARENTESE);
			}
		}else{
			decl_var(cod, GLOBAL);
			if(match_SN_cond(VIRGULA)){
				decl_var(cod, GLOBAL);	
			}
		}
		match_SN(PONTO_VIRGULA);
    }else{
    	match_PR(VOID);
    	match_ID(cod,0,-15);
    	match_SN(ABRIRPARENTESE);
		tipos_param(0);
		if(match_SN_cond(VIRGULA)){
			match_ID(cod,0,-15);
			match_SN(ABRIRPARENTESE);
			tipos_param(0);
			match_SN(FECHARPARENTESE);
		}
		match_SN(PONTO_VIRGULA);
	}
}

int tipo(){

     if ( (match_PR_cond(CHAR)) ){
        return CHAR;
     }
     if ( (match_PR_cond(INT)) ){
        return INT;
     }
     if ( (match_PR_cond(FLOAT)) ){
        return FLOAT;
     }
     if ( (match_PR_cond(BOOL)) ){
        return BOOL;
     }
     return 0;
}

void tipos_param(int pos){
    int cod;
    if ( ( cod = (tipo())) ){
    	if (pos != 0){
            aux += 1;
            checaTipoParam(cod,aux,pos);
        }
        
        if(match_SN_cond(ENDERECO)){
        	match_ID(cod,1,PARAM);
		}else{
			match_ID(cod,1,PARAM);
		}
		
        if ( (match_SN_cond(VIRGULA)) ){
            tipos_param(pos);
        }
    }
    else {
        match_PR(VOID);
        if (pos !=0 ){
            checaTipoParam(VOID,aux,pos);
        }
    }
}

void funcOrDecl(){
     decl();
	 func();     
}
/*
int fwd_decl(){
      int cod;
      if ( (cod = (tipo())) ){
         adicionaTipoParamFWD(cod,aux);
         aux +=1;
         if ( (match_SN_cond(VIRGULA)) ){
            fwd_decl();
         }
         return 1;
      }
      return 0;
}
*/

void func(){
    int cod,pos;
    aux = 0;
    flag = 0;
    if ( (cod = (tipo())) ){
        match_ID(cod,0,FUNC);
        match_SN(ABRIRPARENTESE);
        escopo = 1;
        pos = verificaFWD();
        tipos_param(pos);
        match_SN(FECHARPARENTESE);
        match_SN(ABRIRCHAVE);
        var(LOCAL);
        if(cod = tipo()){
        	decl_var(cod, PARAM);
			if(match_SN_cond(VIRGULA)){
				decl_var(cod, PARAM);
				match_SN(PONTO_VIRGULA);
			}        
    	}
        while ( cmd() );
        if (flag == 0){
            printf("Funcao sem return na linha %d\n",linha);
            system("PAUSE");
            exit(1);
        }
        match_SN(FECHARCHAVE);
        escopo = 0;
        gerenciador_tab(EXCLUIR,0,0);//código excluir para identificar no gerenciador que as variáveis com escopo 1 devem "sumir" da tabela
        funcOrDecl();
    }
    else{
    	cod = 0;
    	aux = 0;
        match_PR(VOID);
        match_ID(cod,0,FUNC);
        match_SN(ABRIRPARENTESE);
        escopo = 1;
        pos = verificaFWD();
        tipos_param(pos);
        match_SN(FECHARPARENTESE);
        match_SN(ABRIRCHAVE);
        var(LOCAL);
        if(cod = tipo()){
        	decl_var(cod, PARAM);
			if(match_SN_cond(VIRGULA)){
				decl_var(cod, PARAM);
				match_SN(PONTO_VIRGULA);
			}        
    	}
        while ( cmd() );
        match_SN(FECHARCHAVE);
        escopo = 0;
        gerenciador_tab(EXCLUIR,0,0);//código excluir para identificar no gerenciador que as variáveis com escopo 1 devem "sumir" da tabela
        funcOrDecl();
    }
}

int cmd(){
    int tipo,classe;
    aux = 0;
    if ( (match_PR_cond(IF)) ){
        match_SN(ABRIRPARENTESE);
        expr();
        match_SN(FECHARPARENTESE);
        cmd();
        if ( (match_PR_cond(ELSE)) ){
            cmd();
        }
        cmd();
        return 1;
    }

    if ( (match_PR_cond(WHILE)) ){
        match_SN(ABRIRPARENTESE);
        expr();
        match_SN(FECHARPARENTESE);
        cmd();
        return 1;
    }

    if ( (match_PR_cond(FOR)) ){
        match_SN(ABRIRPARENTESE);
        if ( (atrib()));
        aux = 0;
        match_SN(PONTO_VIRGULA);
        expr();
        match_SN(PONTO_VIRGULA);
        if ( (atrib()) );
        match_SN(FECHARPARENTESE);
        cmd();
        return 1;
    }

    if ( (match_PR_cond(RETURN)) ){
    	flag = 1;
        expr();
        match_SN(PONTO_VIRGULA);
        cmd();
        return 1;
    }

    if ( (atrib()) ){
        cmd();
        proxToken();
        match_SN(PONTO_VIRGULA);
        return 1;
    }

    if ( (match_ID_cond(NADA)) ){
        match_SN(ABRIRPARENTESE);
        classe = retornaClasse();
        match_SN(FECHARPARENTESE);
        match_SN(PONTO_VIRGULA);
        indice = 0;
        cmd();
        return 1;
    }

    if ( (match_PR_cond(PONTO_VIRGULA)) ){
        cmd();
        return 1;
    }
    
    if ( (match_PR_cond(ABRIRCHAVE)) ){
        cmd();
        match_PR(FECHARCHAVE);
        cmd();
        return 1;
    }
    return 0;
}

int atrib(){
	aux = variavelDeclaraAtrib();
    if ( (match_ID_cond(NADA)) ){
    	/*if ( (match_PR_cond(ABRIRCOCHETE)) ){
    		expr();
    		match_PR(FECHARCOCHETE);
    	}*/
        match_SN(ATRIBUICAO);
        expr();
        return 1;
    }
    else{
        return 0;
    }
}

void expr(){
     expr_simp();
     if ( (op_rel()) ){
        expr_simp();
     }
}

void exprSimpRepete(){
    if ( (match_SN_cond(SOMA)) ){
        termo();
        exprSimpRepete();
    }
    if ( (match_SN_cond(SUBTRACAO)) ){
        termo();
        exprSimpRepete();
    }
    if ( (match_SN_cond(OR)) ){
        termo();
        exprSimpRepete();
    }
}

void expr_simp(){
    if ( (match_SN_cond(SOMA)) || (match_SN_cond(SUBTRACAO)) ){
        termo();
        exprSimpRepete();
    }
    else{
        termo();
        exprSimpRepete();
    }
}

void termo(){
     fator();
     termoRepete();
}

void termoRepete(){
    if ( (match_SN_cond(MULTIPLICACAO)) ){
        fator();
        termoRepete();
    }
    if ( (match_SN_cond(DIVISAO)) ){
        fator();
        termoRepete();
    }
    if ( (match_SN_cond(AND)) ){
        fator();
        termoRepete();
    }
}

void fator(){
	if (aux == 0){
        verificaTipoExp();
    }
    else{
        verificaTipo(aux);
    }
    
    if ( (match_ID_cond(NADA)) ){
    	if ( (match_SN_cond(ABRIRCOCHETE)) ){
    		expr();
    		match_SN(FECHARCOCHETE);
    		paramMenos();
            indice = 0;
            return;
    	}
        if ( (match_SN_cond(ABRIRPARENTESE)) ){
            if ( (match_SN_cond(FECHARPARENTESE)) ){
            	paramMenos();
                indice = 0;
                return;
            }
            else{
                fatorRepete();
                match_SN(FECHARPARENTESE);
                paramMenos();
                indice = 0;
                return;
            }
            return;
        }
        return;
    }

    if ( (match_CTI()) )
        return;

    if ( (match_CTR()) )
        return;

    if ( (match_CTC()) )
        return;

    if ( (match_SN_cond(ABRIRPARENTESE)) ){
        expr();
        match_SN(FECHARPARENTESE);
        indice = 0;
        return;
    }

    if ( (match_SN_cond(NOT)) ){
        fator();
        return;
    }
    else{
         error_sintatico();
    }

}

int op_rel(){
    if ( (match_SN_cond(IGUAL)) ){
        return 1;
    }
    if ( (match_SN_cond(DIFERENTE)) ){
        return 1;
    }
    if ( (match_SN_cond(MENORIGUAL))){
        return 1;
    }
    if ( (match_SN_cond(MENOR))){
        return 1;
    }
    if ( (match_SN_cond(MAIORIGUAL)) ){
        return 1;
    }
    if ( (match_SN_cond(MAIOR)) ){
        return 1;
    }
    return 0;
}

void proxToken(){
    tk = analexico();
}

void fatorRepete(){
    expr();
    if ( (match_SN_cond(VIRGULA)) ){
        fatorRepete();
    }
}

void match_SN(int cod){
    if ( (tk.cat == SN) && (tk.tipo.codigo == cod) ){
        proxToken();
    }
    else{
        printf("Sinal %s esperado na linha %d\n",listaSinais[cod], linha);
        exit(1);
    }
}

int match_SN_cond(int cod){
    if ( (tk.cat == SN) && (tk.tipo.codigo == cod) ){
        proxToken();
        return 1;
    }
    else{
        return 0;
    }
}

void match_PR(int cod){
     if ( (tk.cat == PR) && (tk.tipo.codigo == (cod+1)) ){
        proxToken();
     }
     else{
         printf("PR esperado na linha %d\n",linha);
         exit(1);
     }
}

int match_PR_cond (int cod){
    if ( (tk.cat == PR) && (tk.tipo.codigo == (cod+1)) ){
        proxToken();
        return 1;
     }
     else{
         return 0;
     }
}

void match_ID(int cod,int zombie,int classe){// A variável cod serve para saber em qual if irá entrar no gerenciador, se -3 irá entrar no de exclusão, se -5 aquele ID não deve ser armazenado a tabela, -1 quando é a primeira vez q ele entrou no gerenciador e qualquer outro valor para adicionar um ID
    if ( (tk.cat == ID) ){
        gerenciador_tab(cod,zombie,classe);//segundo parametro é para identificar um campo zombie
        proxToken();
    }
    else{
        printf("Identificador esperado na linha %d\n",linha);
        exit(1);
    }
}

int match_CTI(){
    if ( (tk.cat == CTI) ){
        proxToken();
        return 1;
    }
    else{
        return 0;
    }
}

int match_CTR(){
    if ( (tk.cat == CTR) ){
        proxToken();
        return 1;
    }
    else{
        return 0;
    }
}

int match_CTC(){
    if ( (tk.cat == CTC) ){
        proxToken();
        return 1;
    }
    else{
       return 0;
    }
}

int match_CTL(){
    if ( (tk.cat == CTL) ){
        proxToken();
        return 1;
    }
    else{
        return 0;
    }
}

int match_ID_cond(int cod){
    if ( (tk.cat == ID) ){// A variável cod serve para saber em qual if irá entrar no gerenciador, se -3 irá entrar no de exclusão, se -5 aquele ID não deve ser armazenado a tabela, -1 quando é a primeira vez q ele entrou no gerenciador e qualquer outro valor para adicionar um ID
        gerenciador_tab(cod,0,0);
        proxToken();
        return 1;
    }
    else{
        return 0;
    }
}

